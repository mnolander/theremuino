#include <toneAC.h>
#include <SR04.h>
// toneAC sets pins 11 and 12 for buzzer
#define PHOTORESISTOR_PIN 0
#define BUTTON_PIN 2
#define ULTRASONIC_TRIGGER_PIN 9
#define ULTRASONIC_ECHO_PIN 10

SR04 sr04 = SR04(ULTRASONIC_ECHO_PIN,ULTRASONIC_TRIGGER_PIN);
int volume = 0.0;
float pitch = 0.0;
int rangeLow[] = {262, 294, 330, 349, 392, 440, 494, 523};  // C4, D4, E4, F4, G4, A4, B4, C5
int rangeHigh[] = {1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093};  // C6, D6, E6, F6, G6, A6, B6, C7
int* currentRange = rangeLow;

void setup() {
  Serial.begin(9600);
  pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
  pinMode(ULTRASONIC_ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Get light reading
  int photoresistorValue = analogRead(PHOTORESISTOR_PIN);
  Serial.print("Light level = ");
  Serial.println(photoresistorValue);

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
      delay(250);  // Delay to prevent multiple button presses in quick succession
    }
  }

  // Get ultrasonic reading and limit distance to a reasonable range
  pitch = sr04.Distance();
  pitch = constrain(pitch, 0, 45);

  // Map photoresistor+ultrasonic readings to output ranges for volume+pitch
  // ADJUST SECOND VALUE IN VOLUME MAP DEPENDING ON BASE LIGHT LEVEL OF ROOM
  volume = map(photoresistorValue, 0, 50, 0, 10);
  int mappedPitch = map(static_cast<int>(pitch), 0, 45, 0, 7);
  int note = currentRange[mappedPitch];

  // Play tone based on calculated pitch
  toneAC(note, volume, 200, 1);

  delay(100);
}