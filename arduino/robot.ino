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
int shoulderPos = 80;
int elbowPos = 60;
int wristPos = 90;
int gripPos = 70;

// base positions
int baseHome = 90;

int baseLeftSmall = 120;
int baseLeft = 150;
int baseLeftMore = 170;

int baseRightSmall = 60;
int baseRight = 30;
int baseRightMore = 10;

// arm poses
int shoulderUp = 80;
int elbowUp = 60;
int wristUp = 90;

int shoulderDownSmall = 60;
int elbowDownSmall = 100;
int wristDownSmall = 105;

int shoulderDown = 45;
int elbowDown = 120;
int wristDown = 115;

int shoulderDownMore = 30;
int elbowDownMore = 140;
int wristDownMore = 125;

// gripper
int gripOpen = 70;
int gripClose = 110;

// pose based on your photo
int photoBase = 110;
int photoShoulder = 55;
int photoElbow = 115;
int photoWrist = 105;

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

void moveServoSmooth(Servo &servo, int &currentPos, int targetPos) {
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

void goToPose(int s, int e, int w) {
  moveServoSmooth(shoulderServo, shoulderPos, s);
  moveServoSmooth(elbowServo, elbowPos, e);
  moveServoSmooth(wristServo, wristPos, w);
}

void openGrip() {
  moveServoSmooth(gripServo, gripPos, gripOpen);
}

void closeGrip() {
  moveServoSmooth(gripServo, gripPos, gripClose);
}

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

void goUp() {
  goToPose(shoulderUp, elbowUp, wristUp);
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

void homePosition() {
  moveServoSmooth(baseServo, basePos, baseHome);
  goToPose(shoulderUp, elbowUp, wristUp);
}

void photoPose() {
  moveServoSmooth(baseServo, basePos, photoBase);
  goToPose(photoShoulder, photoElbow, photoWrist);
  openGrip();
}

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

void setup() {
  Serial.begin(9600);

  baseServo.attach(9);      // Servo 1 = base
  shoulderServo.attach(6);  // Servo 2 = shoulder
  elbowServo.attach(5);     // Servo 3 = elbow
  wristServo.attach(3);     // Servo 4 = wrist
  gripServo.attach(11);     // Servo 5 = gripper

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for (;;);
  }

  display.clearDisplay();
  display.display();

  homePosition();
  openGrip();
  showCommand("READY");

  Serial.println("READY");
}

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
      else if (input == "HOME") {
        homePosition();
        showCommand("HOME");
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