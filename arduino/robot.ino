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

// ---------------- CURRENT POSITIONS ----------------
int basePos = 90;
int shoulderPos = 70;
int elbowPos = 40;
int wristPos = 90;
int gripPos = 55;

// ---------------- BASE POSITIONS ----------------
int baseReset = 90;

int baseLeftSmall = 120;
int baseLeft = 145;
int baseLeftMore = 170;

int baseRightSmall = 60;
int baseRight = 35;
int baseRightMore = 10;

// ---------------- RESET / UPRIGHT POSE ----------------
int shoulderReset = 70;
int elbowReset = 40;
int wristReset = 90;

// ---------------- DOWN POSES ----------------
int shoulderDownSmall = 58;
int elbowDownSmall = 75;
int wristDownSmall = 100;

int shoulderDown = 48;
int elbowDown = 100;
int wristDown = 110;

int shoulderDownMore = 35;
int elbowDownMore = 125;
int wristDownMore = 120;

// ---------------- GRIPPER ----------------
int gripOpen = 55;
int gripClose = 155;

// ---------------- PHOTO POSE ----------------
int photoBase = 110;
int photoShoulder = 55;
int photoElbow = 115;
int photoWrist = 105;

// ---------------- OLED ----------------
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

// ---------------- SMOOTH MOVEMENT ----------------
void moveServoSmooth(Servo &servo, int &currentPos, int targetPos) {
  if (targetPos > 180) targetPos = 180;
  if (targetPos < 0) targetPos = 0;

  if (currentPos < targetPos) {
    for (int i = currentPos; i <= targetPos; i++) {
      servo.write(i);
      delay(10);
    }
  } else {
    for (int i = currentPos; i >= targetPos; i--) {
      servo.write(i);
      delay(10);
    }
  }

  currentPos = targetPos;
}

// ---------------- SEPARATE ARM CONTROL ----------------
void goToPose(int shoulderTarget, int elbowTarget, int wristTarget) {
  moveServoSmooth(shoulderServo, shoulderPos, shoulderTarget);
  moveServoSmooth(elbowServo, elbowPos, elbowTarget);
  moveServoSmooth(wristServo, wristPos, wristTarget);
}

// ---------------- GRIP ----------------
void openGrip() {
  moveServoSmooth(gripServo, gripPos, gripOpen);
}

void closeGrip() {
  moveServoSmooth(gripServo, gripPos, gripClose);
}

// ---------------- BASE MOVEMENT ----------------
void goLeftSmall() {
  moveServoSmooth(baseServo, basePos, baseLeftSmall);
}

void goLeft() {
  moveServoSmooth(baseServo, basePos, baseLeft);
}

void goLeftMore() {
  moveServoSmooth(baseServo, basePos, baseLeftMore);
}

void goRightSmall() {
  moveServoSmooth(baseServo, basePos, baseRightSmall);
}

void goRight() {
  moveServoSmooth(baseServo, basePos, baseRight);
}

void goRightMore() {
  moveServoSmooth(baseServo, basePos, baseRightMore);
}

// ---------------- ARM ----------------
void goUp() {
  goToPose(shoulderReset, elbowReset, wristReset);
}

void goDownSmall() {
  goToPose(shoulderDownSmall, elbowDownSmall, wristDownSmall);
}

void goDown() {
  goToPose(shoulderDown, elbowDown, wristDown);
}

void goDownMore() {
  goToPose(shoulderDownMore, elbowDownMore, wristDownMore);
}

// ---------------- RESET ----------------
void resetPosition() {
  moveServoSmooth(baseServo, basePos, baseReset);
  goToPose(shoulderReset, elbowReset, wristReset);
  openGrip();
}

// ---------------- OTHER POSES ----------------
void photoPose() {
  moveServoSmooth(baseServo, basePos, photoBase);
  goToPose(photoShoulder, photoElbow, photoWrist);
  openGrip();
}

// ---------------- TASKS ----------------
void pickObject() {
  goDownMore();
  delay(300);
  closeGrip();
  delay(300);
  goUp();
}

void dropObject() {
  goDownMore();
  delay(300);
  openGrip();
  delay(300);
  goUp();
}

// ---------------- SETUP ----------------
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

  display.clearDisplay();
  display.display();

  resetPosition();
  showCommand("READY");

  Serial.println("READY");
}

// ---------------- LOOP ----------------
void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      input.trim();
      input.toUpperCase();

      if (input == "LEFT_SMALL") {
        goLeftSmall();
        showCommand("L SMALL");
      }
      else if (input == "LEFT") {
        goLeft();
        showCommand("LEFT");
      }
      else if (input == "LEFT_MORE") {
        goLeftMore();
        showCommand("L MORE");
      }
      else if (input == "RIGHT_SMALL") {
        goRightSmall();
        showCommand("R SMALL");
      }
      else if (input == "RIGHT") {
        goRight();
        showCommand("RIGHT");
      }
      else if (input == "RIGHT_MORE") {
        goRightMore();
        showCommand("R MORE");
      }
      else if (input == "DOWN_SMALL") {
        goDownSmall();
        showCommand("D SMALL");
      }
      else if (input == "DOWN") {
        goDown();
        showCommand("DOWN");
      }
      else if (input == "DOWN_MORE") {
        goDownMore();
        showCommand("D MORE");
      }
      else if (input == "UP") {
        goUp();
        showCommand("UP");
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
      else if (input == "PHOTO_POSE") {
        photoPose();
        showCommand("POSE");
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