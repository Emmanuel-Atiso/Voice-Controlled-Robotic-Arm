#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristServo;
Servo gripServo;

String input = "";

// current positions
int basePos = 90;
int shoulderPos = 120;
int elbowPos = 60;
int wristPos = 90;
int gripPos = 70;

// calibrated full-up / straight pose
int baseReset = 90;
int shoulderUp = 120;
int elbowUp = 60;
int wristUp = 90;

// mid-lift pose
int shoulderLiftMid = 100;
int elbowLiftMid = 75;
int wristLiftMid = 95;

// pick pose
int shoulderPick = 85;
int elbowPick = 95;
int wristPick = 100;

// grip
int gripOpen = 70;
int gripClose = 120;

// base step sizes
int baseStepSmall = 10;
int baseStep = 20;
int baseStepBig = 35;

// arm step sizes
int shoulderStepSmall = 4;
int shoulderStep = 8;
int shoulderStepBig = 14;

int elbowStepSmall = 4;
int elbowStep = 8;
int elbowStepBig = 14;

int wristStepSmall = 2;
int wristStep = 4;
int wristStepBig = 8;

void showCommand(String cmd) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Robot Arm");

  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println(cmd);

  display.display();
}

void moveArmSmooth(int targetShoulder, int targetElbow, int targetWrist) {
  while (shoulderPos != targetShoulder ||
         elbowPos != targetElbow ||
         wristPos != targetWrist) {

    if (shoulderPos < targetShoulder) shoulderPos++;
    else if (shoulderPos > targetShoulder) shoulderPos--;

    if (elbowPos < targetElbow) elbowPos++;
    else if (elbowPos > targetElbow) elbowPos--;

    if (wristPos < targetWrist) wristPos++;
    else if (wristPos > targetWrist) wristPos--;

    shoulderServo.write(shoulderPos);
    elbowServo.write(elbowPos);
    wristServo.write(wristPos);

    delay(15);
  }
}

void moveArm(int sStep, int eStep, int wStep) {
  int targetShoulder = shoulderPos + sStep;
  int targetElbow = elbowPos + eStep;
  int targetWrist = wristPos + wStep;

  if (targetShoulder > 180) targetShoulder = 180;
  if (targetShoulder < 0) targetShoulder = 0;

  if (targetElbow > 180) targetElbow = 180;
  if (targetElbow < 0) targetElbow = 0;

  if (targetWrist > 180) targetWrist = 180;
  if (targetWrist < 0) targetWrist = 0;

  moveArmSmooth(targetShoulder, targetElbow, targetWrist);
}

void moveBaseTo(int target) {
  if (target > 180) target = 180;
  if (target < 0) target = 0;

  while (basePos != target) {
    if (basePos < target) basePos++;
    else basePos--;

    baseServo.write(basePos);
    delay(10);
  }
}

void moveBase(int amount) {
  moveBaseTo(basePos + amount);
}

void openGrip() {
  while (gripPos != gripOpen) {
    if (gripPos < gripOpen) gripPos++;
    else gripPos--;

    gripServo.write(gripPos);
    delay(10);
  }
}

void closeGrip() {
  while (gripPos != gripClose) {
    if (gripPos < gripClose) gripPos++;
    else gripPos--;

    gripServo.write(gripPos);
    delay(10);
  }
}

void goFullyUp() {
  moveArmSmooth(shoulderUp, elbowUp, wristUp);
}

void goLiftMid() {
  moveArmSmooth(shoulderLiftMid, elbowLiftMid, wristLiftMid);
}

void goPickPose() {
  moveArmSmooth(shoulderPick, elbowPick, wristPick);
}

void resetPosition() {
  moveBaseTo(baseReset);
  goFullyUp();
}

void pickObject() {
  goPickPose();
  delay(500);

  closeGrip();
  delay(800);

  goLiftMid();
  delay(500);

  goFullyUp();
  delay(500);

  goFullyUp();
  delay(300);

  closeGrip();
}

void dropObject() {
  goLiftMid();
  delay(300);

  goPickPose();
  delay(500);

  openGrip();
  delay(500);

  goLiftMid();
  delay(300);

  goFullyUp();
  delay(500);

  goFullyUp();
}

void setup() {
  Serial.begin(9600);

  baseServo.attach(9);
  shoulderServo.attach(6);
  elbowServo.attach(5);
  wristServo.attach(3);
  gripServo.attach(11);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }

  baseServo.write(basePos);
  shoulderServo.write(shoulderPos);
  elbowServo.write(elbowPos);
  wristServo.write(wristPos);
  gripServo.write(gripPos);

  delay(500);

  resetPosition();
  openGrip();
  showCommand("READY");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      input.trim();
      input.toUpperCase();

      if (input == "LEFT_SMALL") {
        moveBase(baseStepSmall);
        showCommand("L SMALL");
      }
      else if (input == "LEFT") {
        moveBase(baseStep);
        showCommand("LEFT");
      }
      else if (input == "LEFT_MORE") {
        moveBase(baseStepBig);
        showCommand("L MORE");
      }
      else if (input == "RIGHT_SMALL") {
        moveBase(-baseStepSmall);
        showCommand("R SMALL");
      }
      else if (input == "RIGHT") {
        moveBase(-baseStep);
        showCommand("RIGHT");
      }
      else if (input == "RIGHT_MORE") {
        moveBase(-baseStepBig);
        showCommand("R MORE");
      }
      else if (input == "DOWN_SMALL") {
        moveArm(-shoulderStepSmall, elbowStepSmall, wristStepSmall);
        showCommand("D SMALL");
      }
      else if (input == "DOWN") {
        moveArm(-shoulderStep, elbowStep, wristStep);
        showCommand("DOWN");
      }
      else if (input == "DOWN_MORE") {
        moveArm(-shoulderStepBig, elbowStepBig, wristStepBig);
        showCommand("D MORE");
      }
      else if (input == "UP_SMALL") {
        moveArm(shoulderStepSmall, -elbowStepSmall, -wristStepSmall);
        showCommand("U SMALL");
      }
      else if (input == "UP") {
        moveArm(shoulderStep, -elbowStep, -wristStep);
        showCommand("UP");
      }
      else if (input == "UP_MORE") {
        moveArm(shoulderStepBig, -elbowStepBig, -wristStepBig);
        showCommand("U MORE");
      }
      else if (input == "OPEN") {
        openGrip();
        showCommand("OPEN");
      }
      else if (input == "CLOSE") {
        closeGrip();
        showCommand("CLOSE");
      }
      else if (input == "RESET") {
        resetPosition();
        showCommand("RESET");
      }
      else if (input == "PICK") {
        pickObject();
        showCommand("PICK");
      }
      else if (input == "DROP") {
        dropObject();
        showCommand("DROP");
      }
      else {
        showCommand("UNKNOWN");
      }

      input = "";
    } else {
      input += c;
    }
  }
}