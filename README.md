# Robotics Assignment

## Project Title

Voice-Controlled-Robotic-Arm

## Team Members

* Emmanuel Atiso
* Derrikson Apenteng

---

## Project Overview

This project presents a voice and command-controlled robotic arm system developed using an Arduino Uno, Python, and a 5-DOF robotic arm. The system allows users to control the arm through typed commands and Windows voice dictation, enabling interaction through both manual and voice-based inputs.

The robotic arm performs movements such as left, right, up, and down, as well as object interaction through gripping, picking, and placing actions. An OLED display provides real-time feedback, showing the current command being executed.

---

## System Functionality

The robot supports:

* Incremental movement control (LEFT, RIGHT, UP, DOWN)
* LEFT_SMALL → +10°
* LEFT → +20°
* LEFT_MORE → +35°
* RIGHT_SMALL → -10°
* RIGHT → -20°
* RIGHT_MORE → -35°
* Multi-step commands (PICK, DROP)
* Reset to default position (RESET)
* Precision control using repeat commands (e.g. RIGHT 3)
* OLED feedback display

The system is controlled through a Python interface, which sends commands to the Arduino via serial communication.

<div align="center">
  <img src="images/Screenshot%202026-04-15%20at%2014.01.10.png" width="400">
</div>

---

## Setup and Usage Instructions

### Hardware Setup

* Servo 1 (Base) → Pin 9
* Servo 2 (Shoulder) → Pin 6
* Servo 3 (Elbow) → Pin 5
* Servo 4 (Wrist) → Pin 3
* Servo 5 (Gripper) → Pin 11
* OLED display via I2C
* Arduino connected via USB

---

### Arduino Setup

1. Open Arduino IDE
2. Install libraries:

   * Adafruit SSD1306
   * Adafruit GFX
   * Servo
3. Open `robot.ino`
4. Select correct board arduino uno + COM port
5. Upload code

---

### Python Setup

1. Install Python
2. Install pyserial:

```bash
pip install pyserial
```

3. Set COM port in code:

```python
PORT = "COM3"
```

4. Run:

```bash
py robot_audio.py
```

---

### How to Use

#### Movement Commands

* LEFT_SMALL / LEFT / LEFT_MORE
* RIGHT_SMALL / RIGHT / RIGHT_MORE
* UP_SMALL / UP / UP_MORE
* DOWN_SMALL / DOWN / DOWN_MORE

#### Control Commands

* OPEN
* CLOSE
* RESET
* PICK
* DROP

#### Repeat Commands

```text
RIGHT 3
UP 2
LEFT_SMALL 4
```

---

### Feedback Features

* OLED shows active command
* Buzzer:

  * short beep = limit reached
  * success beep = pick complete

---

## Project Structure

```text
arduino/
  robot.ino
python/
  robot_audio.py
images/
  Screenshot 2026-04-15 at 13.39.52.png
  Screenshot 2026-04-15 at 13.52.53.png
  Screenshot 2026-04-15 at 14.01.10.png
README.md
```

---

## Voice Control (Windows Dictation)

Windows voice dictation was integrated as an input method to allow hands-free control. Users can speak commands such as “left”, “right”, or “pick”, which are interpreted and sent through the Python interface.

This improves accessibility and allows interaction without a keyboard.

---

## Accessibility Applications

This system can assist users with limited mobility by enabling control through voice input.

Possible uses:

* picking and moving objects
* assisting simple tasks
* acting as an assistive robotic interface

---

## Software and Technologies Used

* Arduino IDE (C++)
* Python (pyserial)
* Windows Voice Dictation
* OLED (Adafruit SSD1306)
* Servo control

---

## Initial Project Planning and Changes

The original idea was to create a robotic arm capable of writing/drawing.

This was not completed due to:

* time constraints
* hardware limitations
* precision challenges

The project shifted to a command-controlled system focusing on reliability and usability.

---

## Object Tracking (Partial Implementation)

Object tracking was implemented separately using computer vision.

Due to time constraints, it was not integrated with the robotic arm. However, it successfully detected and tracked objects.

This can be extended in future work.

---

## 3D Design and Manufacturing

3D printing was used to create custom components.

* Software: Bambu Studio

This allowed rapid prototyping and improved system adaptability.

<div align="center">
  <img src="images/Screenshot%202026-04-15%20at%2013.39.52.png" width="400">
</div>

<div align="center">
  <img src="images/Screenshot%202026-04-15%20at%2013.52.53.png" width="400">
</div>

---

## Future Improvements

* integrate object detection with robot
* improve servo power
* add text-to-speech
* improve voice recognition
* automated sorting system

---

## Video Presentation

https://youtu.be/H1ilLcpVcLE

---

## AI Transparency Statement

This project aligns with **AITS Level 2 – AI for Shaping**.

Artificial Intelligence was used as a supporting tool during development. It assisted with code structuring, debugging, and documentation.

All system implementation, testing, and hardware integration were carried out independently. The robotic arm required manual calibration and iterative refinement to achieve correct behaviour.

AI outputs were critically reviewed and adapted before use. The final system reflects independent understanding, with AI used to support—not lead—the development process.

---

## References

* Adeept.com. (2026). Adeept 5-DOF Robotic Arm Assembly Tutorial | Step-by-Step Guide | ADA031 Tutorial - Adeept Video. [online] Available at: https://www.adeept.com/video/detail-164.html [Accessed 11 Apr. 2026].
* Tech, S. (2021). How To Build Adeept Robotic Arm. [online] Youtu.be. Available at: https://youtu.be/mtzavQi6j6U?si=N2nn8bZ3sRPsuEnv [Accessed 21 Mar. 2026].
