# ESP32 WiFi Control System

A smart control system built with ESP32 that provides web-based control interface and visual feedback through an LCD display.

## Features

- WiFi connectivity with status indication
- Web server interface for remote control
- Visual feedback through ST7789 LCD display
- Dual LED status indicators
- Built-in LED for WiFi connection status

## Hardware Requirements

- ESP32 Development Board
- ST7789 LCD Display (240x320)
- 2 LEDs (for system status)
- Jumper wires
- Breadboard (optional)

## Pin Connections

### LCD Display

- CS: GPIO 14
- RST: GPIO 19
- DC: GPIO 15
- MOSI: GPIO 23
- SCLK: GPIO 18

### LEDs

- Built-in LED: GPIO 2
- System LED 1: GPIO 4
- System LED 2: GPIO 21

## Dependencies

- WiFi.h
- WebServer.h
- SPI.h
- Adafruit_GFX.h
- Adafruit_ST7789.h

## Setup Instructions

1. Install the required libraries in your Arduino IDE:

   - Adafruit GFX Library
   - Adafruit ST7789 Library

2. Configure WiFi credentials:

   - Open `src/main.cpp`
   - Update the `ssid` and `password` variables with your WiFi credentials

3. Upload the code to your ESP32

4. After successful upload:
   - The ESP32 will attempt to connect to WiFi
   - The LCD will display "Connecting..."
   - Once connected, the built-in LED will turn on
   - The system will be OFF by default

## Web Interface

The system provides two endpoints:

- `/on` - Turns the system ON
- `/off` - Turns the system OFF

To control the system:

1. Find the ESP32's IP address in the Serial Monitor
2. Open a web browser
3. Navigate to `http://<ESP32_IP>/on` or `http://<ESP32_IP>/off`

## Display Information

The LCD display shows:

- WiFi connection status
- IP address
- System status (ON/OFF)

## Troubleshooting

1. If the ESP32 fails to connect to WiFi:

   - Check your WiFi credentials
   - Ensure the WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)
   - Verify the WiFi signal strength

2. If the display isn't working:
   - Verify all pin connections
   - Check if the correct display model is selected in the code
   - Ensure the SPI pins are correctly configured

## License

This project is open source and available under the MIT License.

## Contributing

Feel free to submit issues and enhancement requests!
# ESP32WifiConnect
