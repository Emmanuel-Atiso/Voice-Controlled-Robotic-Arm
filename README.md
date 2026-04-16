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

## Legal, Safety, and Ethical Considerations

This project involves a robotic arm system with **object tracking (computer vision)** and **manual/voice control**, which introduces important legal, safety, and ethical considerations. The following frameworks are relevant to the responsible design and operation of this system.

---

### Robot Safety Standards (ISO)

The system design is informed by standards from the International Organization for Standardization (ISO), including:

- ISO 10218 – Industrial robot safety  
- ISO/TS 15066 – Collaborative robot (cobot) safety  

**Why this is relevant:**  
These standards ensure that robots operating in proximity to humans do so safely, reducing risks such as collision, sudden movement, or mechanical injury.

**Application in this project:**  
- Movements are controlled using **small incremental steps**  
- The system avoids sudden or high-speed motion  
- The user can **stop tracking at any time**, maintaining full control  

---

### ⚖️ UK Health and Safety Legislation

This project aligns with guidance from the UK Health and Safety Executive (HSE), including:

- Health and Safety at Work etc. Act 1974  
- General machinery safety principles  

**Why this is relevant:**  
Robotic systems involve moving mechanical components that may pose safety risks if not properly controlled.

**Application in this project:**  
- The robot operates at **low speed and within a limited range**  
- The system is designed for **supervised use only**  
- Commands are executed in a controlled and predictable manner  

---

### 📷 Data Protection 

The system uses a camera for object tracking, which falls under the scope of the UK General Data Protection Regulation (UK GDPR).

**Why this is relevant:**  
If the system captures identifiable individuals, it may involve the processing of personal data.

**Application in this project:**  
- The system is designed to track **objects only, not individuals**  
- No images or video data are stored  
- All processing is carried out **locally in real time**, ensuring privacy  

---

###  International AI Regulation 

Although the United Kingdom is no longer part of the European Union, the EU AI Act (developed by the European Commission) is recognised as a leading global framework for regulating AI systems.

**Why this is relevant:**  
It provides a benchmark for classifying AI systems based on risk, particularly those interacting with real-world environments.

**Application in this project:**  
- The system maintains **human oversight at all times**  
- It does not operate autonomously without user input  
- System behaviour is transparent and predictable  

---

### Ethical Considerations

This project follows general ethical principles outlined by organisations such as the IEEE and the British Standards Institution (BSI).

**Key principles:**  
- Safety  
- Transparency  
- Human control  
- Accountability  

**Application in this project:**  
- The user remains in full control of the system  
- The robot does not make independent decisions  
- All actions are based on visible inputs and user commands  

---

### Risk Assessment

**Identified risks:**  
- Unexpected movement of the robotic arm  
- Collision with objects or users  
- Errors in object tracking  

**Mitigation strategies:**  
- Use of **dead zones** to prevent jitter  
- Controlled command timing to avoid overload  
- Incremental movement rather than large positional changes  
- Clear separation between manual and tracking modes  

---

###  Conclusion

In this project we aimed to demonstrate responsible robotics development by considering safety, legal compliance, and ethical design. Whilst it is a prototype, it reflects real-world requirements for systems that interact with physical environments and users.

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
* BSI (2020) BS EN ISO 12100: Safety of machinery – General principles for design. London: British Standards Institution. Available at: https://www.bsigroup.com (Accessed: 16 April 2026).

European Commission (2024) Artificial Intelligence Act. Brussels: European Union. Available at: https://digital-strategy.ec.europa.eu/en/policies/european-approach-artificial-intelligence (Accessed: 16 April 2026).

Health and Safety at Work etc. Act 1974. London: HMSO. Available at: https://www.legislation.gov.uk/ukpga/1974/37 (Accessed: 16 April 2026).

IEEE (2019) Ethically Aligned Design: A Vision for Prioritizing Human Well-being with Autonomous and Intelligent Systems. New York: Institute of Electrical and Electronics Engineers. Available at: https://standards.ieee.org/industry-connections/ec/autonomous-systems.html (Accessed: 16 April 2026).

ISO (2011) ISO 10218-1:2011 Robots and robotic devices – Safety requirements for industrial robots. Geneva: International Organization for Standardization. Available at: https://www.iso.org/standard/51330.html (Accessed: 16 April 2026).

ISO (2016) ISO/TS 15066:2016 Robots and robotic devices – Collaborative robots. Geneva: International Organization for Standardization. Available at: https://www.iso.org/standard/62996.html (Accessed: 16 April 2026).

UK Government (2018) Data Protection Act 2018. London: HMSO. Available at: https://www.legislation.gov.uk/ukpga/2018/12/contents (Accessed: 16 April 2026).
