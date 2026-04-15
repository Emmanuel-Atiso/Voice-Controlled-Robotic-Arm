# Robotics Assignment 

## Project Title
Voice-Controlled-Robotic-Arm

## Team Members
- Emmanuel Atiso
- Derrikson Apenteng

## Project Overview

This project presents a voice and command-controlled robotic arm system developed using an Arduino Uno, Python, and a 5-DOF robotic arm. The system allows users to control the arm through typed commands and Windows voice dictation, enabling interaction through both manual and voice-based inputs.

The robotic arm performs movements such as left, right, up, and down, as well as object interaction through gripping, picking, and placing actions. An OLED display provides real-time feedback, showing the current command being executed.

---

## System Functionality

The robot supports:

- Incremental movement control (LEFT, RIGHT, UP, DOWN)
- LEFT_SMALL → +10°
- LEFT → +20°
- LEFT_MORE → +35°
- RIGHT_SMALL → -10°
- RIGHT → -20°
- RIGHT_MORE → -35°
- Multi-step commands (PICK, DROP)
- Reset to default position (RESET)
- Precision control using repeat commands (e.g. RIGHT 3)
- OLED feedback display

The system is controlled through a Python interface, which sends commands to the Arduino via serial communication.
<div align="center">
  <img src="images/Screenshot%202026-04-15%20at%2014.01.10.png" width="400">
</div>

---

## Voice Control (Windows Dictation)

Windows voice dictation was integrated as an input method to allow hands-free control of the system. Users can speak commands such as “left”, “right”, or “pick”, which are interpreted and sent through the Python interface.

This feature demonstrates how the system can be adapted for accessibility, allowing users with limited mobility to control the robotic arm without needing a keyboard.

Additionally, the system can be extended to provide audio feedback (text-to-speech), enabling two-way interaction between the user and the robot.

---

## Accessibility Applications

This system has potential applications in assisting individuals with physical disabilities. Voice control allows users who may have limited hand movement to interact with objects through the robotic arm.

Possible use cases include:
- Picking up and moving objects
- Assisting with simple daily tasks
- Acting as an assistive robotic interface

The combination of voice input and visual feedback makes the system more inclusive and user-friendly.

---

## Software and Technologies Used

- Arduino IDE (C++)
- Python (Serial Communication using pyserial)
- Windows Voice Dictation
- OLED Display (Adafruit SSD1306 library)
- Servo motor control using Arduino Servo library

---

## Initial Project Planning and Changes

Initially, the project aimed to implement a robotic arm capable of writing or drawing using a pen attachment. This would involve precise motion control and path planning.

However, this approach was not fully pursued due to:
- Time constraints
- Hardware limitations of the robotic arm
- Difficulty achieving consistent precision with servo motors

As a result, the focus shifted to building a reliable command-controlled robotic system with improved usability and interaction.

---

## Object Tracking (Partial Implementation)

Object tracking was explored using computer vision techniques. The system was able to detect and track objects successfully.

However, due to time constraints, this feature was not fully integrated with the robotic arm control system. While tracking worked independently, it was not connected to trigger robotic actions.

This remains a potential future improvement, where the robot could automatically detect and pick objects without manual commands.

---
## 3D Design and Manufacturing

Custom components for the robotic arm were designed and prepared using 3D printing. A slicing software (Bambu Studio) was used to convert 3D models into printable layers and generate G-code for the printer.

The parts were printed using PLA filament with a standard 0.4mm nozzle. The slicing process allowed control over print quality, layer height, and structural strength.

3D printing enabled rapid prototyping and customisation of components such as holders and attachments, which improved the functionality and adaptability of the robotic system.

<div align="center">
  <img src="images/Screenshot%202026-04-15%20at%2013.39.52.png" width="400">
</div>

<div align="center">
  <img src="images/Screenshot%202026-04-15%20at%2013.52.53.png" width="400">
</div>


## Future Improvements

- Full integration of object detection with robotic control
- Improved servo strength or power supply for better lifting performance
- Addition of text-to-speech feedback
- Enhanced voice recognition system
- Automated sorting system based on object colour or position

---
## AI Transparency Statement

This project aligns with **AITS Level 2 – AI for Shaping**.

Artificial Intelligence was used to support development, including:
- suggesting and refining code structure
- assisting with debugging and problem-solving
- improving documentation and explanation of concepts

All code was tested, modified, and integrated independently with the hardware system. Key decisions such as movement logic, servo calibration, and system behaviour were made and validated through hands-on implementation.

AI outputs were critically reviewed and adapted before use. The final system reflects independent understanding and development, with AI used as a support tool rather than a primary creator.

---


## References
- Adeept.com. (2026). Adeept 5-DOF Robotic Arm Assembly Tutorial | Step-by-Step Guide | ADA031 Tutorial - Adeept Video. [online] Available at: https://www.adeept.com/video/detail-164.html [Accessed 11 Apr. 2026].
- Tech, S. (2021). How To Build Adeept Robotic Arm. [online] Youtu.be. Available at: https://youtu.be/mtzavQi6j6U?si=N2nn8bZ3sRPsuEnv [Accessed 21 Mar. 2026].


## AI Transparency Statement
State your AITS level and explain how AI was used.
