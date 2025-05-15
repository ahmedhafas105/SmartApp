# 🚦 ESP32 Smart Monitor: Motion & Gas Detection with Blynk & Wokwi ☁️

[![ESP32](https://img.shields.io/badge/Platform-ESP32-purple.svg)](https://www.espressif.com/en/products/socs/esp32)
[![Framework](https://img.shields.io/badge/Framework-Arduino-00979D.svg)](https://www.arduino.cc/)
[![Simulation](https://img.shields.io/badge/Simulation-Wokwi-brightgreen.svg)](https://wokwi.com/)
[![Dashboard](https://img.shields.io/badge/Dashboard-Blynk-00C78E.svg)](https://blynk.io/)
[![Status](https://img.shields.io/badge/Status-Complete%20&%20Working-success.svg)]()

**Check out the live demo (video/GIF)!**
https://www.linkedin.com/posts/ahmed-hafas-27379722a_iot-esp32-blynk-activity-7326280784640626688-TcJX?utm_source=share&utm_medium=member_desktop&rcm=ACoAADlsvbcBr4ueBVWWbS7adGMp-vx-AOFFmCk

> A hands-on IoT project showcasing real-time motion detection and simulated gas level monitoring using an ESP32, various sensors, and an interactive Blynk dashboard. Fully simulated in Wokwi for easy testing and development!

---

## 📜 Table of Contents

*   [✨ Features](#-features)
*   [🛠️ Hardware Components](#️-hardware-components)
*   [💻 Software & Tools](#-software--tools)
*   [🔧 Circuit Diagram & Connections](#-circuit-diagram--connections)
*   [📱 Blynk Dashboard Setup](#-blynk-dashboard-setup)
*   [🚀 Getting Started (Wokwi Simulation)](#-getting-started-wokwi-simulation)
*   [👨‍💻 Code Overview](#-code-overview)
*   [🧪 How to Test](#-how-to-test)
*   [🔮 Future Enhancements](#-future-enhancements)
*   [🙌 Acknowledgements](#-acknowledgements)

---

## ✨ Features

*   **Motion Detection System:**
    *   Activates an LED 💡 and Buzzer 🔊 upon detecting motion via an IR Sensor.
    *   Real-time status updates on the Blynk dashboard (LED indicator, Buzzer indicator, "Motion Detected!" label).
*   **Gas Level Monitoring (Simulated):**
    *   Gas sensor value can be remotely set from the Blynk app using a slider.
    *   The set value is displayed on a sleek Gauge widget in the Blynk dashboard (percentage %).
*   **Interactive Blynk Dashboard:**
    *   LED & Buzzer ON/OFF indicators.
    *   Label displaying current motion status.
    *   Gauge for visualizing gas sensor levels.
*   **Wokwi Simulation:**
    *   The entire project can be run and tested in the Wokwi online simulator without needing physical hardware.

---

## 🛠️ Hardware Components (Simulated in Wokwi)

*   1x ESP32 DevKit V1
*   1x LED (e.g., Red)
*   1x Resistor (~220-330Ω for LED)
*   1x Buzzer
*   1x PIR Motion Sensor
*   1x Gas Sensor (e.g., MQ-series, visually represented, value driven by Blynk)

---

## 💻 Software & Tools

*   **Wokwi:** Online ESP32 & Arduino simulator.
*   **Blynk Platform (App & Cloud):** For creating the IoT dashboard and communication.
*   **Arduino IDE or PlatformIO:** For writing and (optionally) compiling the ESP32 firmware. (Code provided is Arduino-based).
*   **C/C++:** Programming language for ESP32 firmware.

---

## 🔧 Circuit Diagram & Connections

The project is designed for Wokwi. You can load the complete setup using the `diagram.json` file in this repository.

**To view/use the diagram in Wokwi:**
1.  Go to your Wokwi project or create a new ESP32 project.
2.  Open the `diagram.json` tab.
3.  Paste the contents of the `diagram.json` file from this repository into it.

**Pin Connections Summary:**

| ESP32 Pin | Component           | Connection Detail      |
| :-------- | :------------------ | :--------------------- |
| `GPIO2`   | LED Anode           | (via Resistor)         |
| `GPIO4`   | Buzzer              | Positive/Signal Pin    |
| `GPIO15`  | IR Sensor           | `OUT` Pin              |
| `GPIO34`  | Gas Sensor (Analog) | `AOUT` Pin (for vis.)  |
| `3V3`     | IR Sensor           | `VCC`                  |
| `VIN`     | Gas Sensor (Analog) | `VCC` (if 5V sensor)   |
| `GND`     | LED Cathode, Buzzer, IR Sensor, Gas Sensor | `GND`                  |

*(Refer to the `diagram.json` or Wokwi project for precise visual connections.)*

**Wokwi Project Link:** [Link to your Wokwi Project]

---

## 📱 Blynk Dashboard Setup

1.  **Create a New Project** in the Blynk App or Web Console.
2.  **Hardware:** ESP32, Connection: WiFi.
3.  **Auth Token:** Note down the Auth Token. You'll need this for the `sketch.ino`.
4.  **Add Widgets:**

    | Widget Type       | Name (Example)    | Virtual Pin | Settings (Example)                                   |
    | :---------------- | :---------------- | :---------- | :--------------------------------------------------- |
    | LED               | LED Status        | `V0`        | Color: Red                                           |
    | LED               | Buzzer Status     | `V1`        | Color: Orange                                        |
    | Label             | Motion Info       | `V2`        |                                                      |
    | Slider/Step Ctrl  | Set Gas Level     | `V3`        | Output: 0-100, Send on Release: ON                   |
    | Gauge             | Gas Level %       | `V4`        | Input: 0-100, Label: `/pin.%`, Reading Rate: PUSH    |

---

## 🚀 Getting Started (Wokwi Simulation)

1.  **Open in Wokwi:**
    *   OR: Create a new ESP32 project in Wokwi, copy the `sketch.ino` content into the editor, and set up the `diagram.json` as described above.
2.  **Configure Credentials:**
    *   In `sketch.ino`, update the following:
        ```cpp
        char auth[] = "YOUR_BLYNK_AUTH_TOKEN"; // Replace with your Blynk Auth Token
        // char ssid[] = "Wokwi-GUEST"; // Wokwi's default, usually fine
        // char pass[] = "";            // Wokwi's default, usually fine

        // If using Blynk.Cloud new templates:
        // #define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
        // #define BLYNK_DEVICE_NAME "YOUR_BLYNK_DEVICE_NAME"
        ```
3.  **Run Simulation:** Click the "Start Simulation" (▶️) button in Wokwi.
4.  **Connect Blynk App:** Ensure your Blynk app is open and the project is active. It should show as "Online."

---

## 👨‍💻 Code Overview (`sketch.ino`)

*   **Includes:** `WiFi.h` for connectivity, `BlynkSimpleEsp32.h` for Blynk communication.
*   **Pin Definitions:** Constants for LED, Buzzer, IR Sensor pins.
*   **Blynk Virtual Pin Definitions:** Macros for easy reference to Blynk virtual pins.
*   **`BLYNK_WRITE(V_GAS_INPUT)`:** This function is triggered when the "Set Gas Level" slider (V3) value changes in the Blynk app. It receives the value and updates the Blynk Gauge (V4).
*   **`checkMotion()`:** Reads the IR sensor. If motion state changes:
    *   Controls the physical LED and Buzzer.
    *   Updates Blynk widgets (V0, V1, V2) accordingly.
*   **`setup()`:**
    *   Initializes Serial communication, pin modes.
    *   Connects to WiFi and Blynk.
    *   Sets up a `BlynkTimer` to call `checkMotion()` periodically.
    *   Sends initial states to Blynk.
*   **`loop()`:**
    *   Runs `Blynk.run()` to handle Blynk communication.
    *   Runs `timer.run()` to execute scheduled tasks.

---

## 🧪 How to Test

1.  **Start Wokwi Simulation & Open Blynk App.**
2.  **Motion Detection:**
    *   In Wokwi, click on the PIR Motion Sensor. A small clickable area will appear.
    *   Click inside this area to simulate motion.
    *   **Observe:**
        *   Wokwi: LED and Buzzer should turn ON.
        *   Blynk: "LED Status" & "Buzzer Status" indicators turn ON; "Motion Info" label shows "Motion Detected!".
    *   Click the PIR sensor again (or wait for timeout if simulated) to stop motion.
    *   **Observe:**
        *   Wokwi: LED and Buzzer should turn OFF.
        *   Blynk: Indicators turn OFF; label shows "No Motion".
3.  **Gas Sensor Simulation:**
    *   In the Blynk app, adjust the "Set Gas Level" slider (V3).
    *   **Observe:**
        *   Wokwi Serial Monitor: "Received Gas Value from Blynk: X" should appear.
        *   Blynk: The "Gas Level %" Gauge (V4) should update to the value you set.

---

## 🔮 Future Enhancements

*   Integrate a real analog gas sensor (MQ-2, MQ-135, etc.) and read its actual values.
*   Implement thresholds for gas levels to trigger alerts (e.g., turn on a different LED/Buzzer pattern).
*   Send push notifications to the Blynk app for critical events (high gas, prolonged motion).
*   Log sensor data over time using Blynk's SuperChart or an external database.
*   Add an OLED display to show status locally on the ESP32.

---

## 🙌 Acknowledgements

*   The **Blynk Team** for their versatile IoT platform.
*   The **Wokwi Team** for the amazing online simulation environment.
*   Community tutorials and resources that inspire such projects.

---

Happy Tinkering! 🚀
