# RFID Door Lock System with Arduino

This project implements an RFID-based door lock system using Arduino. The system allows you to unlock a door by scanning an authorized RFID card or tag.

## Components Required

- Arduino UNO/Nano
- RC522 RFID Reader Module
- RFID Cards/Tags
- SG90 Servo Motor
- 16x2 I2C LCD Display
- Jumper Wires
- Breadboard
- 5V Power Supply
- Optional: Buzzer for sound feedback

## Features

- Secure access control using RFID technology
- LCD display for system status
- Servo motor for lock mechanism
- Support for multiple authorized RFID cards/tags
- Visual feedback through LCD
- Optional sound feedback through buzzer

## Circuit Connections

### RFID RC522 Module to Arduino
- SDA → Pin 10
- SCK → Pin 13
- MOSI → Pin 11
- MISO → Pin 12
- IRQ → Not connected
- GND → GND
- RST → Pin 9
- 3.3V → 3.3V

### I2C LCD Display to Arduino
- SDA → A4
- SCL → A5
- VCC → 5V
- GND → GND

### Servo Motor to Arduino
- Signal → Pin 3
- VCC → 5V
- GND → GND

### Optional Buzzer
- Positive → Pin 8
- Negative → GND

## Installation

1. Connect all components according to the circuit diagram
2. Install the required libraries:
   - MFRC522 (for RFID module)
   - LiquidCrystal_I2C (for LCD display)
   - Servo (included in Arduino IDE)
3. Upload the provided code to your Arduino board
4. Scan your RFID cards to register them (follow instructions in the code)

## Usage

1. Power on the system
2. The LCD will display "Put your card"
3. Scan an authorized RFID card/tag
4. If authorized, the servo will unlock the door and LCD will display "Door is Open"
5. To lock again, scan the card once more or wait for auto-lock (if enabled)
6. Unauthorized cards will display "Wrong card" on the LCD

## Customization

You can modify the code to:
- Change the unlock duration
- Add more authorized cards
- Implement auto-lock functionality
- Add sound alerts with a buzzer

## Troubleshooting

- If the RFID reader doesn't detect cards, check the wiring connections
- If the servo doesn't move, ensure proper power supply
- If the LCD doesn't display, verify I2C address and connections

## License

This project is open-source and available for personal and educational use.