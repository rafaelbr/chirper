# Devices Support

This folder contains the code for the devices supported by the project.

Currently, the following devices are supported:

- [x] Heltec LoRa WiFi 32 (V2)
- [x] LilyGo T-Deck

This is a PlatformIO project, so you can use the PlatformIO extension for Visual Studio Code or Jetbrains CLion to build and upload the code to the devices.

## Folder Structure

The folder structure is as follows:

```.
|-- README.md
|-- platformio.ini // PlatformIO configuration file
|-- boards // Boards configuration files
|   `-- T-Deck.json // T-Deck board configuration
|-- include
|   `-- devices.h // Devices LoRaWAN configuration
|-- lib       
|-- src
|   `-- boards
|       |-- T-Deck-915M // source code for T-Deck board
|       `-- heltec_wifi_lora_32_V2 // source code for Heltec LoRa WiFi 32 (V2) board
```
Still in development...

