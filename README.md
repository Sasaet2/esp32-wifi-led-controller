# ESP32 WiFi LED Controller

Control an LED from any phone or computer browser through your ESP32.
The board connects to your home WiFi and hosts a small web page with
ON / OFF buttons - no app install and no cloud service needed.

## Features

- Web page served directly by the ESP32 (port 80)
- Clean, mobile-friendly interface
- Uses the built-in LED, so zero extra components are required
- Only ~80 lines of commented Arduino code - easy to read and extend

## Hardware

| Part | Notes |
|---|---|
| ESP32 dev board | any model (ESP32 DevKit, WROOM, ...) |
| USB cable | for flashing and power |

The sketch drives the built-in LED on GPIO 2. To control an external
LED instead, connect it through a 220 ohm resistor to any GPIO and
change `LED_PIN` at the top of the sketch.

## Setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Add the ESP32 board package (File > Preferences > Additional board
   manager URLs > `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`,
   then install "esp32" from the Boards Manager).
3. Open `esp32-wifi-led-controller.ino`.
4. Fill in your WiFi name and password:
   ```cpp
   const char* WIFI_SSID     = "YOUR_WIFI_NAME";
   const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
   ```
5. Select your board and port, then upload.

## Usage

Open the Serial Monitor at 115200 baud. After connecting, the ESP32
prints its IP address, for example:

```
Connected! Open this in your browser: http://192.168.1.42
```

Open that address in any browser on the same network and use the buttons.

## Testing status

The code was carefully written and reviewed but has **not been run on
real hardware yet**. If you flash it and something misbehaves, please
open an issue with the Serial Monitor output.
