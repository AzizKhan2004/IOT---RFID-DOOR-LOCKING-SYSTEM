# RFID Door Lock System - Components and Setup Instructions

## Components List

| Component | Quantity | Description |
|-----------|----------|-------------|
| Arduino UNO/Nano | 1 | Main microcontroller |
| RC522 RFID Reader Module | 1 | For reading RFID cards/tags |
| RFID Cards/Tags | 2+ | For access control |
| SG90 Servo Motor | 1 | For lock mechanism |
| 16x2 I2C LCD Display | 1 | For status display |
| Jumper Wires | 20+ | For connections |
| Breadboard | 1 | For prototyping |
| 5V Power Supply | 1 | For powering the system |
| Buzzer (optional) | 1 | For sound feedback |
| Foam Board/Cardboard | - | For mounting components |
| Hot Glue Gun | - | For securing components |

## Required Libraries

1. **MFRC522** - For RFID module
   - Install via Arduino Library Manager
   - Search for "MFRC522" by GithubCommunity

2. **LiquidCrystal_I2C** - For I2C LCD display
   - Install via Arduino Library Manager
   - Search for "LiquidCrystal I2C" by Frank de Brabander

3. **Servo** - For servo motor control (included in Arduino IDE)

## Setup Instructions

### Step 1: Hardware Assembly

1. **Mount the components** on a foam board or suitable base:
   - Position the RFID reader where it will be easily accessible
   - Mount the servo motor where it can interact with the door lock mechanism
   - Place the LCD display where it's visible to users
   - Secure the Arduino in a protected location

2. **Create a simple lock mechanism**:
   - Cut a small piece of plastic or wood to serve as the lock bolt
   - Attach it to the servo horn
   - Position it so that when the servo rotates, it can move in and out of a slot to lock/unlock the door

### Step 2: Wiring Connections

Follow the circuit diagram and connect components as follows:

#### RFID RC522 Module to Arduino
- SDA → Pin 10
- SCK → Pin 13
- MOSI → Pin 11
- MISO → Pin 12
- IRQ → Not connected
- GND → GND
- RST → Pin 9
- 3.3V → 3.3V

#### I2C LCD Display to Arduino
- SDA → A4
- SCL → A5
- VCC → 5V
- GND → GND

#### Servo Motor to Arduino
- Signal → Pin 3
- VCC → 5V
- GND → GND

#### Optional Buzzer
- Positive → Pin 8
- Negative → GND

### Step 3: Software Setup

1. **Install Required Libraries**:
   - Open Arduino IDE
   - Go to Sketch > Include Library > Manage Libraries
   - Search for and install the MFRC522 and LiquidCrystal_I2C libraries

2. **Upload the Code**:
   - Open the RFID_Door_Lock.ino file in Arduino IDE
   - Connect your Arduino board via USB
   - Select the correct board and port from Tools menu
   - Click Upload

### Step 4: First-Time Setup

1. **Register RFID Cards**:
   - Power on the system
   - The first card scanned will be automatically registered as an authorized card
   - You can modify the code to register multiple cards if needed

2. **Test the System**:
   - Scan the registered card to unlock the door
   - The servo should move to the unlock position
   - The LCD should display "Door is Open"
   - Scan again to lock or wait for auto-lock

### Step 5: Mounting on Door

1. **Prepare the Door**:
   - Determine the best location for the lock mechanism
   - Create a slot or catch for the lock bolt
   - Ensure the servo has enough clearance to move freely

2. **Mount the System**:
   - Secure the main board to the door or door frame
   - Position the RFID reader on the outside of the door
   - Mount the servo so its movement aligns with the lock slot
   - Route wires carefully to avoid pinching

3. **Power Supply**:
   - For permanent installation, use a reliable 5V power adapter
   - Consider adding a battery backup for power outages

## Troubleshooting

- **RFID Reader Not Detecting Cards**:
  - Check wiring connections
  - Ensure the card is compatible with the RC522 module
  - Try reducing the distance between the card and reader

- **Servo Not Moving**:
  - Check power supply (servos may need more current than USB can provide)
  - Verify the servo pin connection
  - Test the servo with a simple sweep code to ensure it works

- **LCD Not Displaying**:
  - Verify the I2C address (may need to be changed in the code)
  - Check the I2C connections
  - Adjust the contrast if the display is powered but not showing text

- **System Restarting**:
  - This may indicate power issues - ensure adequate power supply
  - Add a capacitor (100-470μF) between 5V and GND to stabilize power