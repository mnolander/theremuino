#define BUTTON_PIN 2
#define BUZZER_PIN 8
#define ULTRASONIC_TRIGGER_PIN 9
#define ULTRASONIC_ECHO_PIN 10

// float volume = 0.0;
float pitch = 0.0;
int rangeLow[] = {262, 294, 330, 349, 392, 440, 494, 523};  // C4, D4, E4, F4, G4, A4, B4, C5
int rangeHigh[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};  // C6, D6, E6, F6, G6, A6, B6, C7
int* currentRange = rangeLow;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Check if the button is pressed to toggle between low and high notes
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Debounce the button to avoid rapid changes
    delay(50);
    if (digitalRead(BUTTON_PIN) == LOW) {
      // Toggle between low and high notes
      if (currentRange == rangeLow) {
        currentRange = rangeHigh;
      } else {
        currentRange = rangeLow;
      }
      delay(500);  // Delay to prevent multiple button presses in quick succession
    }
  }

  pitch = getUltrasonicDistance(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);

  // Map pitch to output ranges
  int mappedPitch = map(static_cast<int>(pitch), 0, 50, 0, 7);
  int note = currentRange[mappedPitch];

  // Play tone based on calculated pitch
  tone(BUZZER_PIN, note, 700);

  delay(50);
}

float getUltrasonicDistance(int triggerPin, int echoPin) {
  // Pulse
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  // Calculate distance in cm (speed of sound = 343m/s and divide by 2 for round trip)
  float distance = duration * 0.034 / 2;
  // Limit the distance to a reasonable range (0 to 50 cm)
  distance = constrain(distance, 0, 50);

  return distance;
}
