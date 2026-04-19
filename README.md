# 📡 ESP32 Radar Detection System

## 🔹 Overview
This project is an advanced radar detection system using ESP32, IR/ultrasonic sensor (HC-SR04), and a servo motor. It performs real-time 180° area scanning and visualizes detected objects on a web-based radar interface.

## 🔹 Features
- 180° area scanning using servo motor  
- Real-time distance measurement using ultrasonic sensor  
- Web-based radar visualization (live data)  
- Buzzer alert on object detection  
- Wireless monitoring via ESP32 WiFi  

## 🔹 Components
- ESP32  
- IR/Ultrasonic Sensor (HC-SR04)  
- Servo Motor  
- Buzzer  
- Power Supply  

## 🔹 Circuit Connections
- TRIG → GPIO 5  
- ECHO → GPIO 18  
- Servo Signal → GPIO 21  
- Buzzer → GPIO 19  
- VCC → 5V / 3.3V  
- GND → GND  

## 🔹 Working Principle
The servo motor rotates from 0° to 180° and scans the surroundings. The ultrasonic sensor measures the distance of objects in its path. This data is sent to a web interface via ESP32 WiFi, where a radar-like display is generated in real time. If an object is detected within a certain range, a buzzer alert is triggered.

## ⚠️ Safety Note
Ensure proper voltage levels for ESP32 (3.3V logic). Avoid directly connecting 5V signals to GPIO pins.

## 🔌 Circuit Diagram
![Circuit Diagram](circuit_diagram.png)

## 📷 Project Model
![Project Model](project_model.jpg)

## 💻 Code
The code is available in: `radar_system.ino`

## 🌐 How to Use
1. Upload code to ESP32  
2. Connect to WiFi: **ESP32-Radar**  
3. Open browser and go to: **192.168.4.1**  
4. View live radar scanning  

## 📄 Project Report
[Download PDF](project_report.pdf)

## 🎥 Demo
[▶️ Watch Demo Video](your_video_link_here)

## 🚀 Future Improvements
- Mobile app integration  
- Cloud-based data logging  
- AI-based object classification  
- Longer range detection system  
