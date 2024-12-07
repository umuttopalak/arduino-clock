const int segmentPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
const int digitPins[] = { 10, 11, 12, 13, 14, 15 };

const int numbers[10][8] = {
  { 0, 1, 1, 1, 1, 1, 1, 0 },  //0
  { 0, 0, 0, 1, 0, 0, 1, 0 },  //1
  { 1, 0, 1, 1, 1, 1, 0, 0 },  //2
  { 1, 0, 1, 1, 0, 1, 1, 0 },  //3
  { 1, 1, 0, 1, 0, 0, 1, 0 },  //4
  { 1, 1, 1, 0, 0, 1, 1, 0 },  //5
  { 1, 1, 1, 0, 1, 1, 1, 0 },  //6
  { 0, 0, 1, 1, 0, 0, 1, 0 },  //7
  { 1, 1, 1, 1, 1, 1, 1, 0 },  //8
  { 1, 1, 1, 1, 0, 1, 1, 0 }   //9
};

int hour = 12;
int minute = 0;
int second = 0;

unsigned long previousMillis = 0;
const int refreshInterval = 5;
int currentDigit = 0;

unsigned long lastSecondMillis = 0;

void setup() {
  Serial.begin(9600);


  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], HIGH);
  }


  for (int i = 0; i < 6; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW);
  }
}

void loop() {
  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= refreshInterval) {
    previousMillis = currentMillis;
    updateDisplay();
  }


  if (currentMillis - lastSecondMillis >= 1000) {
    lastSecondMillis = currentMillis;
    incrementTime();
    printTime();
  }
}


void incrementTime() {
  second++;
  if (second >= 60) {
    second = 0;
    minute++;
    if (minute >= 60) {
      minute = 0;
      hour++;
      if (hour >= 24) {
        hour = 0;
      }
    }
  }
}

void printTime() {

  if (hour < 10) Serial.print("0");
  Serial.print(hour);
  Serial.print(":");
  if (minute < 10) Serial.print("0");
  Serial.print(minute);
  Serial.print(":");
  if (second < 10) Serial.print("0");
  Serial.println(second);
}

void updateDisplay() {

  for (int i = 0; i < 6; i++) {
    digitalWrite(digitPins[i], LOW);
  }
  delayMicroseconds(100);

  int h1 = hour / 10;
  int h2 = hour % 10;
  int m1 = minute / 10;
  int m2 = minute % 10;
  int s1 = second / 10;
  int s2 = second % 10;

  int digits[6] = { h1, h2, m1, m2, s1, s2 };
  int number = digits[currentDigit];

  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], numbers[number][i] == 1 ? LOW : HIGH);
  }

  digitalWrite(segmentPins[7], HIGH);
  digitalWrite(digitPins[currentDigit], HIGH);

  currentDigit = (currentDigit + 1) % 6;
}
