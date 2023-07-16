# two-talking-circuits
Two Esp32 communicate via ChatGPT-generated responses. (With optional oled display monitor)

## Purpose
The purpose of this project is to leverage artificial intelligence in the context of the Internet of Things, making things easier by providing a ready-made template for specific needs.

## Required components

* 2x - [Esp32 board](http://esp32.net/)

  
Optional:
* 2x - Oled i2c ssd1306
* 2x - Breadboard
* Jump wires

[Esp32 with oled display](https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/)

## Description
The code consists of two receiver and sender sources that are mirrored. It will be necessary to set wifi, api key of chatGPT, MAC Address for both of them. 

## Setup
We’ll program the ESP32 board using Arduino IDE, so before proceeding with this tutorial you should have the ESP32 add-on installed in your Arduino IDE. 

Follow the next guide:


[Installing the ESP32 Board in Arduino IDE (Windows, Mac OS X, and Linux instructions)](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

**ESP-NOW supports the following features:**

Encrypted and unencrypted unicast communication;
Mixed encrypted and unencrypted peer devices;
Up to 250-byte payload can be carried;
Sending callback function that can be set to inform the application layer of transmission success or failure.

**ESP-NOW technology limitation:**

Payload is limited to 250 bytes.

---

**ChatGPT Api Key:**

[How to get your own ChatGPT Api key](https://tfthacker.medium.com/how-to-get-your-own-api-key-for-using-openai-chatgpt-in-obsidian-41b7dd71f8d3)

> :warning: **[Keep an eye on the costs of using the chatGPT api.](https://platform.openai.com/account/usage)**

### Usage

(both sender and receiver)

```ino
// API Key
const char* apiKey = "<YOUR_API_KEY>";
```
---

Get the MAC Address of the two Esp32 boards:

[Get Esp32 MAC Address](https://randomnerdtutorials.com/get-change-esp32-esp8266-mac-address-arduino/)

### Usage
```ino
// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0xD2, 0xED, 0x54, 0xC3, 0xD1, 0x12};
```
```ino
// REPLACE WITH THE MAC Address of your sender
uint8_t broadcastAddress[] = {0xD2, 0xED, 0x54, 0xC3, 0xD1, 0x12};
```

Set-up your Wi-fi connection (both sender and receiver):

```ino
// Wi-Fi Settings
const char* ssid = "<YOUR_WIFI_NAME>";
const char* password = "<YOUR_WIFI_PASSWORD>";
```

## Improve this project
This project is always seeking ways to improve and welcomes feedback and contributions from its users. If you have any suggestions or ideas, please feel free to create an issue or submit a pull request on the GitHub repository.

## Sponsor me!
[Buy me a coffee!](https://bmc.link/robibl95)

![bmc_qr_redo](https://github.com/RobertoBellarosa95/two-talking-circuits/assets/37309982/e417df40-fb40-42a4-9d27-6785f42f5416)

