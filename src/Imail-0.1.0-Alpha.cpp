
/*******************************************************************
    Imail-0.1.0-Alpha
    Program for ESP32CAM which will send Telegram notifications when receiving mail in your mailbox, also returns Mailbox trap door status.
    Additionally the following Telegram Commands are available:
    -"/help" shows available Telegram commands.
    -"/status" to check if mailbox trap door is opened or closed.
    -"/check" to check if Imail is online.
    -"/getid" to see Telegram chat ID for configuration purpose.

    Parts:
    -->ESP32CAM board* - https://www.amazon.de/-/en/Bluetooth-Development-4-75V-5-25V-Nodemcu-Raspberry/dp/B097Y93P8D/ref=sr_1_7?crid=7IEVZD93IYB4&keywords=esp32+cam&qid=1652453797&s=ce-de&sprefix=esp32cam%2Celectronics%2C103&sr=1-7
    (or any similar ESP32cam board)
    -->REED sensor - https://www.amazon.de/-/en/sensor-surface-mounting-magnetic-normally/dp/B09QFWPHS9/ref=sr_1_22?keywords=schilfsensor&qid=1652454096&sr=8-22&th=1
    -->Arduino UNO or any other serial interface to program the board.

    Written by David García-Taheno Fernandez
    GitHub: https://github.com/dgtaheno

    Resources:

    -Bot father: https://core.telegram.org/bots#1-what-can-i-do-with-bots
    -Universal Telegram Bot: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
    -ArduinoJson: https://arduinojson.org/
    -PlatformIO:  https://platformio.org/
    -Visual studio Code:  https://code.visualstudio.com/

    Notes: Next steps in this program development:
    -Pictures when receiving mail & also when receiving /photo Telegram command implementation.
    -Battery monitoring notifications and Telegram battery check command.
    -Add a second reed sensor so when opening the mailbox to collect the mail sends a notification that the mail has been collected.
    -Add WiFi manager function for initial configuration via an Access Point.
    -Introduce OTA features, so not necessary serial interface to program it.
 *******************************************************************/

#include <Arduino.h>              //Library included to use .ino program with Platform IO in VS Code instead of using .ino in Arduino IDE
#include <WiFi.h>                 //ESP32 wifi management library https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFi.h
#include <WiFiClientSecure.h>     //Client SSL for ESP32 https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFiClientSecure/src/WiFiClientSecure.h
#include <UniversalTelegramBot.h> //Library which allows to interact with Telegram https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/
#include <ArduinoJson.h>          //ESP32 serialization library https://arduinojson.org/

// Wifi network station credentials
#define WIFI_SSID "*********"
#define WIFI_PASSWORD "************"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "**************"

// Use @myidbot (IDBot) to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "*******************"

// Define hardware pins:
#define MAIL 16  // Mailbox reed sensor on pin 16
#define FLASH 4  // Camera Flash on pin 4
#define OBLED 33 // On board led on pin 33

const unsigned long BOT_MTBS = 1000; // mean time between scan messages
// Validate Telegram Client
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

// declare functions:
void handleNewMessages(int numNewMessages); // handle Telegram Messages function.
void checkmessages(void);                   // declare function that checks if any message from Telegram
void bot_setup(void);                       // configure commands in Telegram bot.

void setup()
{

  // initialize hardware pins in ESP32CAM
  pinMode(FLASH, OUTPUT); // Declare Flash as an Output(for future developments)
  pinMode(OBLED, OUTPUT); // Declare onboard LED as an Output(When light Mailbox trap door is open)
  pinMode(MAIL, INPUT);   // Declare reed sensor as an Input
  digitalWrite(FLASH, 0); // Set the Flash light as Off
  digitalWrite(OBLED, 1); // Set the onboard LED light as Off(inverted logic on this LED, see ESP32CAM documentation)

  // initialize Wifi
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
  bot_setup(); // setup bot commands

  bot.sendMessage(CHAT_ID, "Imail started up", ""); // Telegram message once Imail is started.
  Serial.println("Imail started up");               // Serial message once Imail is started.
  if (digitalRead(MAIL) == false)                   // If the Mailbox trap door is closed, notify the user via Telegram and serial.
  {
    bot.sendChatAction(CHAT_ID, "typing");
    delay(500);
    bot.sendMessage(CHAT_ID, "Mailbox trap door is closed!\nInitialization is complete!\n");
    Serial.println("Mailbox trap door is closed!\nInitialization is complete!\n");
  }
  else // If the Mailbox trap door is opened, notify the user via Telegram and serial and wait for the trap door to close to finalize the initialization.
  {
    bot.sendChatAction(CHAT_ID, "typing");
    delay(500);
    digitalWrite(OBLED, 0); // turn on the on board led (opposite logic)
    bot.sendMessage(CHAT_ID, "Mailbox trap door is open, please close it to initialize correctly!\n");
    Serial.println("Mailbox trap door is open, please close it to initialize correctly!\n");

    while (digitalRead(MAIL) == true) // This loops allow to receive Telegram commands while waiting for Mailbox trap door to close
    {
      delay(100);
      checkmessages();
    }
    // once mailbox trap door is closed again sends Telegram and serial notifications informing that the Initialization is completed
    digitalWrite(OBLED, 1); // turn off the on board led (opposite logic)
    bot.sendChatAction(CHAT_ID, "typing");
    delay(500);
    bot.sendMessage(CHAT_ID, "Mailbox trap door is closed!\nInitialization is complete!\n");
    Serial.println("Mailbox trap door is closed!\nInitialization is complete!\n");
  }
}

void loop()
{
  int mail_status = digitalRead(MAIL); // read mailbox trap door status and store it in variable
  // serial print of Mailbox trap door status
  Serial.print("Mailbox trap door status: ");
  Serial.println(digitalRead(MAIL));
  if (mail_status == 1) // If mailbox trap door is open it means that mail is received
  {
    digitalWrite(OBLED, 0); // turn on the on board led (opposite logic)
    bot.sendChatAction(CHAT_ID, "typing");
    delay(1000);
    // send Telegram & serial message informing about mail reception
    bot.sendMessage(CHAT_ID, "YOU GOT MAIL!\n");
    Serial.println("You got mail!");
    delay(15000);               // wait for 15 seconds to check if mailbox trap is still open
    if (digitalRead(MAIL) == 1) // if open, it means something is blocking the trap and informs via Telegram & serial
    {
      bot.sendChatAction(CHAT_ID, "typing");
      delay(1000);
      bot.sendMessage(CHAT_ID, "Mailbox trap door is not closing!\n");
      Serial.println("Mailbox trap door is not closing!");
      while (digitalRead(MAIL) == 1)
      {
        // loop to wait for the trap to close
        delay(100);
        checkmessages();
        Serial.print("Mailbox trap door status: ");
        Serial.println(digitalRead(MAIL));
      }
    }
    // when mailbox trap is closed turn off the on board led and send a message informing about the trap door closed.
    digitalWrite(OBLED, 1); // turn off on board led(opposite logic)
    bot.sendChatAction(CHAT_ID, "typing");
    delay(1000);
    bot.sendMessage(CHAT_ID, "Mailbox trap door is closed again!\n");
    Serial.println("Mailbox trap door is closed again!");
  }
  // uncomment these 2 lines below for debugging
  // Serial.print("Mailbox trap door status: ");
  // Serial.println(digitalRead(MAIL));
  checkmessages();
}

void handleNewMessages(int numNewMessages) // function for handling Telegram commands
{
  // uncomment these 2 lines below for debugging
  // Serial.println("handleNewMessages");
  // Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (chat_id == CHAT_ID) // If chat ID contacting Telegram Bot is the one given process the following commands
    {

      if (text == "/status")
      {
        if (digitalRead(MAIL) == false)
        {
          bot.sendChatAction(chat_id, "typing");
          delay(500);
          bot.sendMessage(chat_id, "Mail trap door is closed!\n");
        }
        else
        {
          bot.sendChatAction(chat_id, "typing");
          delay(500);
          bot.sendMessage(chat_id, "Mail trap door is opened!\n");
        }
      }

      else if (text == "/check")
      {
        bot.sendChatAction(chat_id, "typing");
        delay(500);
        bot.sendMessage(chat_id, "Imail is online!\n");
      }

      else if (text == "/getid")
      {
        bot.sendChatAction(chat_id, "typing");
        delay(500);
        bot.sendMessage(chat_id, chat_id);
      }

      else if (text == "/help")
      {
        String help = "Welcome to Imail, " + from_name + ".\n";
        help += "This is Commands Imail help:\n\n";
        help += "/check : Check if Imail is online.\n";
        help += "/getid : Check Telegram chat ID for configuration purpose.\n";
        help += "/status : Check if mailbox trap door is open or closed.\n";
        bot.sendChatAction(chat_id, "typing");
        delay(500);
        bot.sendMessage(chat_id, help);
      }

      else
      {
        bot.sendChatAction(chat_id, "typing");
        delay(500);
        bot.sendMessage(chat_id, "Not valid command!, please use /help command to see available commands.");
      }
    }

    else
    {
      bot.sendChatAction(chat_id, "typing");
      delay(500);
      bot.sendMessage(chat_id, "Not valid user!");

      if (text == "/getid")
      {
        bot.sendChatAction(chat_id, "typing");
        delay(500);
        bot.sendMessage(chat_id, chat_id);
      }

      else if (text == "/help")
      {
        bot.sendChatAction(chat_id, "typing");
        delay(500);
        bot.sendMessage(chat_id, "/getid : Check Telegram chat ID for configuration purpose.\n");
      }

      else
      {
        bot.sendChatAction(chat_id, "typing");
        delay(500);
        bot.sendMessage(chat_id, "Not valid command!, please use /help command to see available commands.");
      }
    }
  }
}
void checkmessages(void) // function to check if there are new Telegram commands
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      // uncomment this line below for debugging
      // Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}
void bot_setup(void) // function which defined Imail Telegram bot commands.
{
  const String commands = F("["
                            "{\"command\":\"help\",  \"description\":\"Get Imail usage help.\"},"
                            "{\"command\":\"check\", \"description\":\"Check if Imail is online.\"},"
                            "{\"command\":\"getid\", \"description\":\"Check Telegram chat ID for configuration purpose.\"},"
                            "{\"command\":\"status\",\"description\":\"Check if mailbox trap door is open or closed.\"}" // no comma on last command
                            "]");
  bot.setMyCommands(commands);
}