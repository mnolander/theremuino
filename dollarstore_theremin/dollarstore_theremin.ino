#define BUZZER_PIN 8
#define ULTRASONIC_TRIGGER_PIN 9
#define ULTRASONIC_ECHO_PIN 10
#define PHOTOSENSOR_PIN A0

float volume = 0.0;
float pitchControl = 0.0;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);

  // No need to initialize the photoresistor pin as it's an analog input
}

void loop() {
  // Read button state
  buttonState = digitalRead(BUTTON_PIN);

  // Read ultrasonic sensor for volume control
  volume = getUltrasonicDistance(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);

  // Read photoresistor for pitch/tone control
  pitchControl = analogRead(PHOTOSENSOR_PIN);

  // Map volume to the buzzer's range (0 to 255)
  int mappedVolume = map(static_cast<int>(volume), 0, 100, 0, 255);

  // Map pitch control to the buzzer's pitch range
  int mappedPitch = map(static_cast<int>(pitchControl), 0, 1023, 500, 2000);

  // Print pitch angle
  Serial.print("Ultrasonic:");
  Serial.println(volume);

  // Print pitch angle
  Serial.print("Pitch:");
  Serial.println(pitchControl);

  // Play sound with the calculated pitch and volume if the button is not pressed
  if (digitalRead(BUTTON_PIN) == HIGH) {
    tone(BUZZER_PIN, mappedPitch, mappedVolume);
  } else {
    Serial.println("Muted!");
    noTone(BUZZER_PIN);
  }

  // Add a delay to prevent excessive readings
  delay(50);
}

float getUltrasonicDistance(int triggerPin, int echoPin) {
  // Trigger ultrasonic sensor
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read the echo pulse duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  float distance = duration * 0.034 / 2;

  // Limit the distance to a reasonable range (0 to 100 cm)
  distance = constrain(distance, 0, 100);

  return distance;
}
