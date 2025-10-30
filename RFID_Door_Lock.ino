/*
 * RFID Door Lock System
 * Based on: https://srituhobby.com/how-to-make-a-rfid-door-lock-with-arduino/
 */

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Pin definitions
#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 3
#define BUZZER_PIN 8

// Constants
#define UNLOCK_ANGLE 0
#define LOCK_ANGLE 70
#define UNLOCK_DURATION 5000 // Time door stays unlocked in milliseconds

// Initialize objects
MFRC522 rfid(SS_PIN, RST_PIN);  // RFID reader
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD display (0x27 is default I2C address)
Servo lockServo;  // Servo motor for lock mechanism

// Variables
String authorizedUIDs[] = {""}; // Store authorized card UIDs here
int numAuthorizedCards = 0;     // Number of authorized cards
bool doorLocked = true;         // Door state
unsigned long unlockTime = 0;   // Time when door was unlocked

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize SPI bus and RFID reader
  SPI.begin();
  rfid.PCD_Init();
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize servo
  lockServo.attach(SERVO_PIN);
  lockServo.write(LOCK_ANGLE); // Start with door locked
  
  // Initialize buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  
  // Display welcome message
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");
  
  // Print program info to serial monitor
  Serial.println("RFID Door Lock System");
  Serial.println("Scan a card to register it as authorized (first run)");
  Serial.println("or to check access (after cards are registered)");
}

void loop() {
  // Check if it's time to auto-lock the door
  if (!doorLocked && millis() - unlockTime > UNLOCK_DURATION) {
    lockDoor();
  }
  
  // Check if a new card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Read the card
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }
  
  // Get the UID of the card
  String cardUID = getUID();
  
  // Print the UID to serial monitor
  Serial.print("Card UID: ");
  Serial.println(cardUID);
  
  // Check if this is the first run (no authorized cards)
  if (numAuthorizedCards == 0) {
    registerNewCard(cardUID);
  } else {
    // Check if the card is authorized
    if (isAuthorized(cardUID)) {
      // Toggle door state
      if (doorLocked) {
        unlockDoor();
      } else {
        lockDoor();
      }
    } else {
      // Unauthorized card
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Wrong card");
      beep(3); // Three short beeps for unauthorized
      
      // Return to welcome message after 2 seconds
      delay(2000);
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("Welcome!");
      lcd.setCursor(1, 1);
      lcd.print("Put your card");
    }
  }
  
  // Halt PICC and stop encryption
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Function to get card UID as a String
String getUID() {
  String UID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    // Add leading zero if needed
    if (rfid.uid.uidByte[i] < 0x10) {
      UID += "0";
    }
    UID += String(rfid.uid.uidByte[i], HEX);
  }
  UID.toUpperCase();
  return UID;
}

// Function to register a new card
void registerNewCard(String uid) {
  // Add the card to the authorized list
  authorizedUIDs[numAuthorizedCards] = uid;
  numAuthorizedCards++;
  
  // Display confirmation
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card registered!");
  lcd.setCursor(0, 1);
  lcd.print("UID: " + uid);
  
  Serial.println("Card registered with UID: " + uid);
  beep(1); // One long beep for confirmation
  
  delay(2000);
  
  // Return to welcome message
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");
}

// Function to check if a card is authorized
bool isAuthorized(String uid) {
  for (int i = 0; i < numAuthorizedCards; i++) {
    if (authorizedUIDs[i] == uid) {
      return true;
    }
  }
  return false;
}

// Function to unlock the door
void unlockDoor() {
  lockServo.write(UNLOCK_ANGLE);
  doorLocked = false;
  unlockTime = millis();
  
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Door is Open");
  
  beep(2); // Two short beeps for unlock
}

// Function to lock the door
void lockDoor() {
  lockServo.write(LOCK_ANGLE);
  doorLocked = true;
  
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Door is Locked");
  
  beep(2); // Two short beeps for lock
  
  // Return to welcome message after 2 seconds
  delay(2000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Welcome!");
  lcd.setCursor(1, 1);
  lcd.print("Put your card");
}

// Function for beep patterns
void beep(int pattern) {
  switch (pattern) {
    case 1: // One long beep (success)
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      break;
    case 2: // Two short beeps (action)
      for (int i = 0; i < 2; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        delay(100);
      }
      break;
    case 3: // Three short beeps (error)
      for (int i = 0; i < 3; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        delay(100);
      }
      break;
  }
}