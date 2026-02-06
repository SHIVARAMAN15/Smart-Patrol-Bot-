# 🤖 Smart Patrol Bot

An autonomous mobile surveillance robot designed for indoor security applications.  
The Smart Patrol Bot combines motion detection, real-time video streaming, and intelligent navigation using low-cost embedded hardware.

---

## 📌 Project Overview

The **Smart Patrol Bot** is a smart security robot developed as part of **Project Exhibition–II** for the B.Tech program in **Electronics and Communication Engineering (AI & Cybernetics)** at **VIT Bhopal University**.

It is capable of:
- Detecting human motion
- Patrolling an indoor area autonomously
- Streaming live video
- Capturing images during suspicious activity
- Sending alerts via Telegram

---

## 🎯 Key Features

- 🔍 **Motion Detection** using PIR sensors  
- 📷 **Live Video Streaming & Image Capture** using ESP32-CAM  
- 🤖 **Autonomous Navigation** with DC motors and L298N motor driver  
- 📲 **Remote Monitoring** via Wi-Fi and Bluetooth  
- 🚨 **Alert System** through Telegram bot  
- 🧠 **Basic Object/Person Detection** using Python Flask  

---

## 🛠️ Hardware Components

| Component | Description |
|---------|-------------|
| ESP32-CAM | Camera module with Wi-Fi & Bluetooth |
| Arduino UNO | Motor and sensor control |
| L298N | Dual H-Bridge motor driver |
| PIR Sensor | Motion detection |
| HC-05 | Bluetooth communication |
| DC Gear Motors | Movement & navigation |
| FTDI Module | ESP32 programming |
| Battery | Power supply |

---

## 🧩 System Architecture

- PIR sensors detect motion
- ESP32-CAM streams video and captures images
- Arduino UNO controls motors via L298N
- Images and alerts are sent to the user through Telegram
- Python Flask is used for object/person detection

---

## 🧪 Working Methodology

1. Bot patrols a predefined indoor area
2. PIR sensor detects motion
3. Bot changes direction towards detected movement
4. ESP32-CAM captures images and streams video
5. Alerts/images are sent to the user
6. Bot returns to patrol mode if no motion is detected

---

## 📊 Results

- Accurate motion detection
- Smooth motor response
- Real-time video streaming with minimal delay
- Reliable alert delivery
- Low-cost and energy-efficient operation

---

## 🚀 Future Enhancements

- GPS-based outdoor navigation
- Obstacle avoidance using ultrasonic/LiDAR sensors
- Rechargeable battery with solar charging
- Face recognition using TensorFlow Lite
- Cloud storage and IoT dashboard integration
- Smart home integration (MQTT, Alexa, Google Home)

---

## 👨‍🎓 Team Members

- **K. Sarala Florence**  
- **Shivaraman T**  
- **Ankita Soni**

---

## 👨‍🏫 Project Guide

**Dr. Anirban Bhowmick**  
Assistant Professor  
School of Electrical & Electronics Engineering  
VIT Bhopal University

---

## 📜 License

This project is intended for **academic and educational use**.  
You may use and modify the code with proper credit to the authors.

---

## ⭐ Acknowledgement

We thank VIT Bhopal University and the School of Electrical & Electronics Engineering for providing the resources and guidance to complete this project.
