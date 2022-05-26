<div id="top"></div>

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![GNU License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/dgtaheno/Imail">
    <img src="https://github.com/dgtaheno/Imail/blob/master/pictures/logo.png?raw=true" alt="Logo" width="200" height="200">
  </a>

  <h3 align="center">I-mail 0.1.0-Alpha</h3>

[Video Demo](https://www.youtube.com)

  <p align="left">
    Got bored of checking the mailbox everyday, so let´s IoT it.
    <br />
  <p align="left">
    Using ESP32CAM hardware and a reed sensor for the mailbox trap door, now I receive notifications in Telegram if I receive mail or if the mailbox trap door is blocked.
    <br />
  
  <a href="https://github.com/dgtaheno/Imail"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/dgtaheno/Imail">View Demo</a>
    ·
    <a href="https://github.com/dgtaheno/Imail/issues">Report Bug</a>
    ·
    <a href="https://github.com/dgtaheno/Imail/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## About The Project

[![Product Name Screen Shot][product-screenshot]](https://github.com/dgtaheno/Imail)

I´m requested by [CS50](https://cs50.harvard.edu/college/2022/spring/project/) to provide the final course project, hence was thinking during a couple of days and nothing was coming to my mind.

But one day, doing my daily housework, I went and check my empty mailbox, this brought to my mind the idea that if something would notify me when receiving mail, I would save some minutes/hours by the end of the year, so it seems like an interesting project to invest some time and present it as my [CS50](https://cs50.harvard.edu/college/2022/spring/project/) final project.

Why should you create your own I-mail?

- It is a cool way to invest your time.
- You will hopefully increase your knowledge on C programming, ESP32, VS Code and so many other tools.
- You will save time receiving notifications from your mailbox directly on your phone.(that´s cool!)
- It´s cheap, and try to make it as easy as possible.

In order to upload I-mail the following files were generated for this project:

<li><a href="https://github.com/dgtaheno/Imail/blob/a6a089b052d4ea0516b42fa168947979fec48a59/.vscode/extensions.json">vscode/extensions.json</a></li>
<li><a href="https://github.com/dgtaheno/Imail/blob/a6a089b052d4ea0516b42fa168947979fec48a59/src/Imail-0.1.0-Alpha.cpp">src/Imail-0.1.0-Alpha.cpp</a></li>
<li><a href="https://github.com/dgtaheno/Imail/blob/a6a089b052d4ea0516b42fa168947979fec48a59/platformio.ini">platformio.ini</a></li>

<p align="right">(<a href="#top">back to top</a>)</p>

### Built With

This is the software used to create this project:

- [Visual Studio Core](https://code.visualstudio.com/)
- [Platform.io](https://platformio.org/install/ide?install=vscode)(VS Code extension)
- [Bot father](https://core.telegram.org/bots#1-what-can-i-do-with-bots)(Telegram bot)
- [Universal Telegram Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)(Telegram ESP32 bot API)
- [ArduinoJson](https://arduinojson.org/)(ESP32 serialization)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- GETTING STARTED -->

## Getting Started

You will need some basic electronic and programming knowledge, but I will try to keep it easy.

### Prerequisites

Hardware:

[![Hardware Name Screen Shot][hardware-screenshot]](https://github.com/dgtaheno/Imail/blob/f141852d8f7f2de7912e0b6193a638d107ab5735/pictures/circuit.png)

- [ESP32CAM board](https://www.amazon.de/-/en/Bluetooth-Development-4-75V-5-25V-Nodemcu-Raspberry/dp/B097Y93P8D/ref=sr_1_7?crid=7IEVZD93IYB4&keywords=esp32+cam&qid=1652453797&s=ce-de&sprefix=esp32cam%2Celectronics%2C103&sr=1-7)
  (or any similar ESP32cam board)
- [REED sensor](https://www.amazon.de/-/en/sensor-surface-mounting-magnetic-normally/dp/B09QFWPHS9/ref=sr_1_22?keywords=schilfsensor&qid=1652454096&sr=8-22&th=1) (Installed on Mailbox trap door)
- [Arduino UNO](https://www.amazon.de/-/en/8541585410-Arduino-UNO-Rev3-SMD/dp/B007R9TUJE/ref=sr_1_4?crid=2YE81LX2UPPKP&keywords=arduino+uno&qid=1652511606&sprefix=arduino+uno%2Caps%2C386&sr=8-4) or any other serial interface to program the board.

See related [link](https://community.platformio.org/t/how-can-i-use-arduino-as-uart-to-usb-converter-while-uploading-code-to-esp32cam/26464) for serial programming with Arduino UNO.

Software:

I programmed ESP32CAM using VSCODE + PlatformIO extension but it is also possible to do it with Arduino IDE.

In VS Code it is necessary to install the Espressif 32 platform v 4.3.0(4.2.0 did not work).

Please note that the following libraries should be installed in the project:

- [Universal Telegram Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
- [Arduinojson](https://arduinojson.org)

It is also a requirement to create a Telegram Bot, see this [link](https://core.telegram.org/bots#3-how-do-i-create-a-bot) where the entire process is described with the aim of getting the bot TOKEN, which will be required later.

### Installation

Prior to flash the board with the program it is necessary to adjust Imail-0.1.0-Alpha in src.

The required part to adjust is the following:

- // Wifi network station credentials

  #define WIFI_SSID "**\*\***\***\*\***"

  #define WIFI_PASSWORD "**\*\*\*\***\*\***\*\*\*\***"

- // Telegram BOT Token (Get from Botfather)

  #define BOT_TOKEN "**\*\***\*\*\*\***\*\***"

- // Use @myidbot (IDBot) to find out the chat ID of an individual or a group
  // Also note that you need to click "start" on a bot before it can
  // message you

  #define CHAT_ID "**\*\***\*\*\***\*\***"

With your own parameters, please note that Wifi credential must be filled with your WIFI data.

Bot token is obtained when creating the bot(mentioned before).

To get the Chat_ID, please follow the instructions mentioned [here](https://www.alphr.com/find-chat-id-telegram/).

Please revise Platformio.ini and adjust your USB port if required:

- monitor_port = COM7
- upload_port = COM7

Once you have adapted the code and connected, click on ESP32CAM "rst" button which will put the board in upload mode.

Click on upload in platformio and once it is uploaded it is ready to go.

ESP32CAM will reboot when finished.

You can now make disconnect arduino if you don not need to serial monitor anymore and just connect as per connection diagram in hardware section.

Now I-mail is ready to work.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->

## Usage

Once ESP32CAM is powered with 5 V, the program will automatically start.

The program works as follows:

[![Software block diagram][software-diagram]](https://github.com/dgtaheno/Imail/blob/f141852d8f7f2de7912e0b6193a638d107ab5735/pictures/block%20diagram.png)

Additionally, in all the steps, the following commands can we executed from Telegram:

/check : Check if Imail is online.

/getid : Check Telegram chat ID for configuration purpose.

/status : Check if mailbox trap door is open or closed.

/help : Shows available commands.

Please note that this commands are valid only if CHAT_ID configured, if not only /getid command will work for configuration purpose.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ROADMAP -->

## Roadmap

- [x] Create Imail-0.1.0-Alpha.cpp & Platformio.ini
- [x] Include all libraries dependencies
  - [x] Universal Telegram Bot
  - [x] Arduinojson
- [x] Design and build all hardware configuration.
- [x] Upload program to ESP32CAM.
- [x] Test
- [x] Create README.md

- [ ] Upgrade with new features:
  - Pictures when receiving mail & also when receiving /photo Telegram command implementation.
  - Battery monitoring notifications and Telegram battery check command.
  - Add a second reed sensor so when opening the mailbox to collect the mail sends a notification that the mail has been collected.
  - Add WiFi manager function for initial configuration via an Access Point instead of hard coding.
  - Introduce OTA features, so not necessary serial interface to program it.

See the [open issues](https://github.com/dgtaheno/Imail/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTRIBUTING -->

## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- LICENSE -->

## License

Distributed under the GNU License. See `LICENSE` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

David García-Taheno Fernández - dgtaheno@hotmail.com

Project Link: [https://github.com/dgtaheno/Imail](https://github.com/dgtaheno/Imail)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->

## Acknowledgments

Resources I found helpful and would like to give credit to.

- [Best README.md template](https://github.com/othneildrew/Best-README-Template)
- [Universal Telegram Bot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot/)
- [ArduinoJson.h](https://arduinojson.org/)
- [Rui Santos](https://github.com/RuiSantosdotme/ESP32-Course)
- [CS50](https://cs50.harvard.edu/college/2022/spring/)
- [Bot father](https://core.telegram.org/bots#1-what-can-i-do-with-bots)

<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[contributors-shield]: https://img.shields.io/github/contributors/dgtaheno/Imail.svg?style=for-the-badge
[contributors-url]: https://github.com/dgtaheno/Imail/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/dgtaheno/Imail.svg?style=for-the-badge
[forks-url]: https://github.com/dgtaheno/Imail/network/members
[stars-shield]: https://img.shields.io/github/stars/dgtaheno/Imail.svg?style=for-the-badge
[stars-url]: https://github.com/dgtaheno/Imail/stargazers
[issues-shield]: https://img.shields.io/github/issues/dgtaheno/Imail.svg?style=for-the-badge
[issues-url]: https://github.com/dgtaheno/Imail/issues
[license-shield]: https://img.shields.io/github/license/dgtaheno/Imail.svg?style=for-the-badge
[license-url]: https://github.com/dgtaheno/Imail/blob/88ad9d26f0a27b99d039913ee49984c01356c6fc/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/dgtaheno/?locale=en_US
[product-screenshot]: /pictures/Imail.jpg
[hardware-screenshot]: /pictures/circuit.png
[software-diagram]: /pictures/block_diagram.png
