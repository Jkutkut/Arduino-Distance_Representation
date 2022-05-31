#define SENSOR 2
#define LED_START 4
#define LEDS 9

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 0; i < LEDS; i++) {
    pinMode(i + LED_START, OUTPUT);
  }
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

long distance() {
  long duration, cm;

  pinMode(SENSOR, OUTPUT);
  
  digitalWrite(SENSOR, LOW);
  delayMicroseconds(2);
  digitalWrite(SENSOR, HIGH);
  delayMicroseconds(5);
  digitalWrite(SENSOR, LOW);
  
  pinMode(SENSOR, INPUT);
  duration = pulseIn(SENSOR, HIGH);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

#define DIST_DELTA (300 / LEDS)

void updateLight(long dist) {
  int i = 0;
  int d = DIST_DELTA;
  for (; d < dist && i < LEDS; d += DIST_DELTA, i++) {
    digitalWrite(i + LED_START, HIGH);
  }
  for (; i < LEDS; i++) {
    digitalWrite(i + LED_START, LOW);
  }
}

long cm;
void loop() {
  cm = distance();

  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println("cm");

  if(cm < 100) {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  updateLight(cm);
  delay(60);
}
