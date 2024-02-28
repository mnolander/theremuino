# Theremin-like instrument using an Arduino with a photoresistor and ultrasonic sensor
This project is inspired by the theremin, an instrument you play without touching! Using a photoresistor for volume control and an ultrasonic sensor for pitch control, this 'instrument' captures that method of control as well.

## Components
 - ELEGOO Mega 2560 (Arudino Mega 2560) board
 - 500Ω - 50kΩ Photoresistor/photocell 
 - HC-SR04 Ultrasonic sensor
 - Passive buzzer
 - 1kΩ Resistor
 - Button

![](https://raw.githubusercontent.com/mnolander/SmartSafe/main/Overview.png?token=GHSAT0AAAAAAB2G5BWQQP2G3VCVIP2BS5LEY4G7YWA)

## Pins
| Component         | Pin(s)                                                    |
|-------------------|-----------------------------------------------------------|
| Photoresistor     | - A0                                                      |
| Ultrasonic sensor | - **Vcc**: 5V - **Trig**: 9 - **Echo**: 10 - **GND**: GND |
| Passive buzzer    | - **+**: 11 - **-**: 12                                   |
| 1kΩ resistor      | - After A0 leg of photoresistor into GND                  |
| Button            | - 2 - GND                                                 |

## Operation
 - Move right hand over ultrasonic sensor to adjust the **pitch**. By default, it is set to a maximum of 45cm and 8 notes.
 - Move left hand over photoresistor to block light and adjust the **volume**. **NOTE:** This may have to be tweaked depending on the ambient light in the room. Open the serial monitor without covering the photoresistor to get your ambient light level and adjust accordingly in the volume map.
 - Press the button to change **octaves**. Right now, there are just 2 octaves you can switch from, but it's easy to adjust the arrays at the top to whatever notes you want.
 
Source files are included for the libraries used.
