# RFID Door Lock System - Usage and Troubleshooting Guide

## Basic Usage

### Normal Operation

1. **Power on the system**
   - The LCD will display "Welcome!" and "Put your card"
   - The door will be in locked state

2. **Unlocking the door**
   - Place an authorized RFID card/tag near the reader
   - The system will read the card and verify it
   - If authorized, the servo will move to unlock position
   - The LCD will display "Door is Open"
   - The buzzer will beep twice (if installed)

3. **Locking the door**
   - The door will automatically lock after the set time (default: 5 seconds)
   - Alternatively, scan the authorized card again to lock immediately
   - The LCD will display "Door is Locked"
   - The buzzer will beep twice (if installed)

4. **Unauthorized access attempt**
   - If an unauthorized card is scanned, the LCD will display "Wrong card"
   - The buzzer will beep three times (if installed)
   - The door will remain locked

### First-Time Setup

1. **Registering the first card**
   - When the system is first powered on with no cards registered
   - The first card scanned will be automatically registered as authorized
   - The LCD will display "Card registered!" and the card's UID
   - This card can now be used to unlock and lock the door

## Customizing the System

### Modifying the Code

#### Adding More Authorized Cards

To add more authorized cards, modify the `authorizedUIDs` array in the code:

```cpp
// Increase the array size to accommodate more cards
String authorizedUIDs[3] = {"", "", ""};  // For 3 cards
```

Then modify the `registerNewCard` function to handle multiple cards:

```cpp
void registerNewCard(String uid) {
  // Check if we have space for more cards
  if (numAuthorizedCards < 3) {  // Change this to match your array size
    authorizedUIDs[numAuthorizedCards] = uid;
    numAuthorizedCards++;
    
    // Display confirmation
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Card registered!");
    lcd.setCursor(0, 1);
    lcd.print("UID: " + uid);
    
    Serial.println("Card registered with UID: " + uid);
    beep(1);
    
    delay(2000);
    
    // Return to welcome message
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Welcome!");
    lcd.setCursor(1, 1);
    lcd.print("Put your card");
  } else {
    // No more space for new cards
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Max cards reached");
    beep(3);
    delay(2000);
  }
}
```

#### Changing the Unlock Duration

To change how long the door stays unlocked, modify the `UNLOCK_DURATION` constant:

```cpp
// Change from 5000ms (5 seconds) to your desired time in milliseconds
#define UNLOCK_DURATION 10000  // 10 seconds
```

#### Disabling Auto-Lock

To disable the auto-lock feature, comment out the auto-lock check in the `loop()` function:

```cpp
void loop() {
  // Comment out these lines to disable auto-lock
  /*
  if (!doorLocked && millis() - unlockTime > UNLOCK_DURATION) {
    lockDoor();
  }
  */
  
  // Rest of the code...
}
```

## Troubleshooting

### Common Issues and Solutions

#### RFID Reader Not Detecting Cards

**Symptoms:**
- LCD shows "Put your card" but nothing happens when a card is presented
- No response when scanning cards

**Solutions:**
1. Check all wiring connections between the RFID module and Arduino
2. Ensure the card is compatible with the RC522 module (13.56MHz MIFARE cards)
3. Try reducing the distance between the card and reader (optimal distance is 1-3cm)
4. Check if the RFID module is receiving power (3.3V)
5. Try using the RFID scanning example code to test the module independently

#### Servo Not Moving

**Symptoms:**
- System recognizes the card but the lock doesn't move
- Servo makes noise but doesn't rotate properly

**Solutions:**
1. Check power supply - servos require more current than USB can provide
2. Verify the servo pin connection to Arduino pin 3
3. Test the servo with a simple sweep code to ensure it works
4. Check if the servo is mechanically obstructed
5. Try a different servo if available

#### LCD Not Displaying

**Symptoms:**
- Blank screen
- Backlight on but no text
- Garbled characters

**Solutions:**
1. Verify the I2C address (default is 0x27, but some displays use 0x3F)
   - If needed, change the address in the code: `LiquidCrystal_I2C lcd(0x3F, 16, 2);`
2. Check the I2C connections (SDA to A4, SCL to A5)
3. Run an I2C scanner sketch to confirm the address
4. Adjust the contrast if the display is powered but not showing text

#### System Restarting Randomly

**Symptoms:**
- System resets when the servo moves
- Inconsistent operation

**Solutions:**
1. Use an external power supply instead of USB
2. Add a capacitor (100-470μF) between 5V and GND to stabilize power
3. Separate the servo power from the logic power if possible
4. Check for loose connections that might cause momentary power loss

### Advanced Troubleshooting

#### Checking Card UIDs

If you need to check the UID of your cards:

1. Open the Serial Monitor in Arduino IDE (set to 9600 baud)
2. Scan your cards one by one
3. The UIDs will be displayed in the format: `Card UID: ABCD1234`
4. Note these UIDs for programming into your system

#### Debugging with Serial Monitor

Add more Serial.print statements to debug specific parts of the code:

```cpp
// Example debug code to add
Serial.println("Checking card authorization...");
Serial.print("Card UID: ");
Serial.println(cardUID);
Serial.print("Authorized: ");
Serial.println(isAuthorized(cardUID) ? "Yes" : "No");
```

#### Testing Components Individually

If you suspect a specific component is faulty, test it with a simple standalone sketch:

- For the RFID module, use the "DumpInfo" example from the MFRC522 library
- For the LCD, use the "HelloWorld" example from the LiquidCrystal_I2C library
- For the servo, use the "Sweep" example from the Servo library

## Maintenance

### Regular Checks

1. **Power Supply**
   - Check for stable power supply
   - Replace batteries if using battery power

2. **Mechanical Parts**
   - Lubricate moving parts of the lock mechanism if needed
   - Check for wear on the servo horn or lock bolt

3. **Connections**
   - Periodically check all wire connections
   - Look for loose or damaged wires

### Firmware Updates

Consider implementing these improvements in future updates:

1. **EEPROM Storage**
   - Store authorized UIDs in EEPROM to persist after power loss
   - Add code to read/write card data to Arduino's EEPROM

2. **Admin Mode**
   - Implement an admin card that can add/remove other cards
   - Add a special sequence (like scanning admin card twice) to enter admin mode

3. **Activity Logging**
   - Add an SD card module to log access attempts
   - Record timestamps, card UIDs, and access results