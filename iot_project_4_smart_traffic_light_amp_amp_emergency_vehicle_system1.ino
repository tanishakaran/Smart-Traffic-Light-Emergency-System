// Traffic Light 1
const int red1 = 2;
const int yellow1 = 3;
const int green1 = 4;

// Traffic Light 2
const int red2 = 5;
const int yellow2 = 6;
const int green2 = 7;

// Emergency Button
const int button = 8;

void setup() {
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1, OUTPUT);

  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);

  pinMode(button, INPUT_PULLUP);
}

void allOff() {
  digitalWrite(red1, LOW);
  digitalWrite(yellow1, LOW);
  digitalWrite(green1, LOW);

  digitalWrite(red2, LOW);
  digitalWrite(yellow2, LOW);
  digitalWrite(green2, LOW);
}

bool emergencyCheck() {

  if (digitalRead(button) == LOW) {

    allOff();
    delay(50);

    // Emergency → ONLY both RED
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);

    return true;
  }

  return false;
}

void waitCheck(int time) {

  for (int i = 0; i < time / 100; i++) {

    if (digitalRead(button) == LOW) {
      emergencyCheck();
      return;
    }

    delay(100);
  }
}

void loop() {

  // 🚑 Emergency button
  if (digitalRead(button) == LOW) {
    emergencyCheck();

    // Keep both RED while button is pressed
    while (digitalRead(button) == LOW) {
      delay(50);
    }

    return;
  }

  // 🚦 Road 1 GREEN | Road 2 RED
  allOff();
  digitalWrite(green1, HIGH);
  digitalWrite(red2, HIGH);

  waitCheck(5000);

  if (digitalRead(button) == LOW) return;


  // 🚦 Road 1 YELLOW | Road 2 RED
  allOff();
  digitalWrite(yellow1, HIGH);
  digitalWrite(red2, HIGH);

  waitCheck(2000);

  if (digitalRead(button) == LOW) return;


  // 🚦 Road 1 RED | Road 2 GREEN
  allOff();
  digitalWrite(red1, HIGH);
  digitalWrite(green2, HIGH);

  waitCheck(5000);

  if (digitalRead(button) == LOW) return;


  // 🚦 Road 1 RED | Road 2 YELLOW
  allOff();
  digitalWrite(red1, HIGH);
  digitalWrite(yellow2, HIGH);

  waitCheck(2000);
}