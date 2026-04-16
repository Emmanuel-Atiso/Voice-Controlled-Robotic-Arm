#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// =========================================================
// DISPLAY CONFIGURATION
// =========================================================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// =========================================================
// SERVO OBJECTS
// =========================================================
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristServo;
Servo gripServo;

// =========================================================
// SERIAL INPUT
// =========================================================
String input = "";

// =========================================================
// CURRENT JOINT POSITIONS
// These track the live position of each servo so that
// movement can be made smoothly and incrementally.
// =========================================================
int basePos = 90;
int shoulderPos = 120;
int elbowPos = 60;
int wristPos = 90;
int gripPos = 70;

// =========================================================
// PRESET POSITIONS / POSES
// =========================================================

// Default reset / upright pose
int baseReset = 90;
int shoulderUp = 120;
int elbowUp = 60;
int wristUp = 90;

// Mid-lift pose used between picking and fully lifting
int shoulderLiftMid = 100;
int elbowLiftMid = 75;
int wristLiftMid = 95;

// Pick pose used to move the claw down to an object
int shoulderPick = 85;
int elbowPick = 95;
int wristPick = 100;

// =========================================================
// GRIPPER POSITIONS
// =========================================================
int gripOpen = 70;
int gripClose = 120;

// =========================================================
// MOVEMENT STEP SIZES
// These determine how much movement happens for SMALL,
// normal, and MORE commands.
// =========================================================

// Base rotation step sizes
int baseStepSmall = 10;
int baseStep = 20;
int baseStepBig = 35;

// Shoulder step sizes
int shoulderStepSmall = 4;
int shoulderStep = 8;
int shoulderStepBig = 14;

// Elbow step sizes
int elbowStepSmall = 4;
int elbowStep = 8;
int elbowStepBig = 14;

// Wrist step sizes
int wristStepSmall = 2;
int wristStep = 4;
int wristStepBig = 8;

// =========================================================
// DISPLAY HELPERS
// =========================================================

/*
  Show the current command on the OLED display.
*/
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

// =========================================================
// ARM MOVEMENT HELPERS
// =========================================================

/*
  Move shoulder, elbow, and wrist smoothly together until
  they reach their target positions.
*/
void moveArmSmooth(int targetShoulder, int targetElbow, int targetWrist) {
  while (shoulderPos != targetShoulder ||
         elbowPos != targetElbow ||
         wristPos != targetWrist) {

    if (shoulderPos < targetShoulder) {
      shoulderPos++;
    } else if (shoulderPos > targetShoulder) {
      shoulderPos--;
    }

    if (elbowPos < targetElbow) {
      elbowPos++;
    } else if (elbowPos > targetElbow) {
      elbowPos--;
    }

    if (wristPos < targetWrist) {
      wristPos++;
    } else if (wristPos > targetWrist) {
      wristPos--;
    }

    shoulderServo.write(shoulderPos);
    elbowServo.write(elbowPos);
    wristServo.write(wristPos);

    delay(15);
  }
}

/*
  Move the arm by relative step values.
  The result is clamped between 0 and 180 degrees.
*/
void moveArm(int shoulderStepAmount, int elbowStepAmount, int wristStepAmount) {
  int targetShoulder = shoulderPos + shoulderStepAmount;
  int targetElbow = elbowPos + elbowStepAmount;
  int targetWrist = wristPos + wristStepAmount;

  // Clamp each servo target to a safe 0–180 range
  targetShoulder = constrain(targetShoulder, 0, 180);
  targetElbow = constrain(targetElbow, 0, 180);
  targetWrist = constrain(targetWrist, 0, 180);

  moveArmSmooth(targetShoulder, targetElbow, targetWrist);
}

// =========================================================
// BASE MOVEMENT HELPERS
// =========================================================

/*
  Move the base servo smoothly to an absolute target position.
*/
void moveBaseTo(int target) {
  target = constrain(target, 0, 180);

  while (basePos != target) {
    if (basePos < target) {
      basePos++;
    } else {
      basePos--;
    }

    baseServo.write(basePos);
    delay(10);
  }
}

/*
  Move the base by a relative amount.
*/
void moveBase(int amount) {
  moveBaseTo(basePos + amount);
}

// =========================================================
// GRIPPER HELPERS
// =========================================================

/*
  Open the gripper smoothly.
*/
void openGrip() {
  while (gripPos != gripOpen) {
    if (gripPos < gripOpen) {
      gripPos++;
    } else {
      gripPos--;
    }

    gripServo.write(gripPos);
    delay(10);
  }
}

/*
  Close the gripper smoothly.
*/
void closeGrip() {
  while (gripPos != gripClose) {
    if (gripPos < gripClose) {
      gripPos++;
    } else {
      gripPos--;
    }

    gripServo.write(gripPos);
    delay(10);
  }
}

// =========================================================
// PRESET POSE FUNCTIONS
// =========================================================

/*
  Move the arm to the fully upright / default working pose.
*/
void goFullyUp() {
  moveArmSmooth(shoulderUp, elbowUp, wristUp);
}

/*
  Move the arm to the middle lift position.
*/
void goLiftMid() {
  moveArmSmooth(shoulderLiftMid, elbowLiftMid, wristLiftMid);
}

/*
  Move the arm to the picking position.
*/
void goPickPose() {
  moveArmSmooth(shoulderPick, elbowPick, wristPick);
}

/*
  Reset the robot to its base reset angle and upright arm pose.
*/
void resetPosition() {
  moveBaseTo(baseReset);
  goFullyUp();
}

// =========================================================
// TASK FUNCTIONS
// =========================================================

/*
  Pick sequence:
  - move to pick pose
  - close gripper
  - lift object
  - reinforce grip
*/
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

/*
  Drop sequence:
  - move down from lifted pose
  - open gripper
  - return upward
*/
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

// =========================================================
// SETUP
// =========================================================

void setup() {
  Serial.begin(9600);

  // Attach servos to Arduino pins
  baseServo.attach(9);
  shoulderServo.attach(6);
  elbowServo.attach(5);
  wristServo.attach(3);
  gripServo.attach(11);

  // Start the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;) {
      // Stop here if display fails to initialise
    }
  }

  // Write starting positions
  baseServo.write(basePos);
  shoulderServo.write(shoulderPos);
  elbowServo.write(elbowPos);
  wristServo.write(wristPos);
  gripServo.write(gripPos);

  delay(500);

  // Move robot into default ready position
  resetPosition();
  openGrip();
  showCommand("READY");
}

// =========================================================
// MAIN LOOP
// =========================================================

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    // Command ends when newline is received
    if (c == '\n') {
      input.trim();
      input.toUpperCase();

      // -------------------------
      // BASE MOVEMENT COMMANDS
      // -------------------------
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

      // -------------------------
      // ARM MOVEMENT COMMANDS
      // -------------------------
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

      // -------------------------
      // GRIPPER COMMANDS
      // -------------------------
      else if (input == "OPEN") {
        openGrip();
        showCommand("OPEN");
      }
      else if (input == "CLOSE") {
        closeGrip();
        showCommand("CLOSE");
      }

      // -------------------------
      // POSITION / TASK COMMANDS
      // -------------------------
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

      // -------------------------
      // UNKNOWN COMMAND
      // -------------------------
      else {
        showCommand("UNKNOWN");
      }

      // Clear input buffer for next command
      input = "";
    } else {
      input += c;
    }
  }
}
