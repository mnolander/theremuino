#define BUZZER_PIN 8
#define ULTRASONIC_TRIGGER_PIN 9
#define ULTRASONIC_ECHO_PIN 10
#define PHOTOSENSOR_PIN A0

float volume = 0.0;
float pitch = 0.0;

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
}

void loop() {
  volume = getUltrasonicDistance(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN);
  pitch = analogRead(PHOTOSENSOR_PIN);

  // Map volume to the buzzer's range (0 to 255)
  int mappedVolume = map(static_cast<int>(volume), 0, 100, 0, 255);
  // Map pitch control to the buzzer's pitch range
  int mappedPitch = map(static_cast<int>(pitch), 0, 1023, 500, 2000);

  // TEST OUTPUTS
  // Print pitch angle
  Serial.print("Ultrasonic:");
  Serial.println(volume);
  // Print pitch angle
  Serial.print("Pitch:");
  Serial.println(pitch);

  // Play tone based on calculated volume+pitch
  tone(BUZZER_PIN, mappedPitch, mappedVolume);

  delay(50);
}

float getUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  float distance = duration * 0.034 / 2;

  // Limit the distance to a reasonable range (0 to 100 cm)
  distance = constrain(distance, 0, 100);

  return distance;
}
