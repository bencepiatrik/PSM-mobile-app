# ESP32 Servo Controller

This project runs on an **ESP32** and allows you to control up to **6 servo motors** over Wi-Fi.  
It includes a simple **REST API** that can be called from a browser, mobile app (e.g. Flutter), or cURL.

---

## 📦 Features
- Control up to 6 servo motors (pins 2–7 by default).
- REST API endpoints to:
  - Check device status
  - Start testing a servo (oscillates ±20° around base position)
  - Stop all servos
- Debug output over Serial Monitor.
- Works with Arduino IDE and PlatformIO.

---

## ⚡ Requirements
- ESP32 board
- Arduino IDE or PlatformIO
- Servo motors (powered externally if needed)
- Common ground between ESP32 and servo power source

---

## 🔌 Wiring
- Servos connected to pins **2, 3, 4, 5, 6, 7**  
- Servo power (VCC) → **5V external power supply**  
- Servo ground (GND) → **ESP32 GND** (common ground required)  
- Servo signal → ESP32 pins 2–7  

⚠️ Do **not** power multiple servos directly from ESP32 5V pin.

---

## ⚙️ Setup
1. Clone this repo.
2. Open the `.ino` file in Arduino IDE.
3. Install required libraries:
   - **Servo.h** (built-in with Arduino IDE for ESP32).
4. Update Wi-Fi credentials in the sketch:
   ```cpp
   const char* ssid     = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
  `
  
