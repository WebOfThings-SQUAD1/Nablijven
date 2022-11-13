// DEFINE
#define DEBUG

// LIBRARIES
#include  <SPI.h>
#include  <MFRC522.h>

// GLOBAL
// Number of RFID readers
const byte numReaders= 3;
// Unique pins of the readers
const byte SS_PINS[] = {2, 5, 8};
// reset pin
const byte RST_PIN = 9;
// Initialise an array of the RFID readers
MFRC522 mfrc522[numReaders];
// Correct sequence of NFC tag ids
const String correctIDs[] = {"EC6AB6C2", "10090E69", "02724544"};
// Tag id currently detected by each reader
String currentIDs[numReaders];

void setup() {

  #ifdef DEBUG
	Serial.begin(9600);
	SPI.begin();
  #endif

  // Ergens moet de init komen van het lock

  for (uint8_t i=0; i < numReaders; i++) {
    // Init the reader
    mfrc522[i].PCD_Init(SS_PINS[i], RST_PIN);

    // Dump debug info
    Serial.print(F("Reader #"));
    Serial.print(i);
    Serial.print(F(" initialised on pin "));
    Serial.print(SS_PINS[i]);
    Serial.print(F(". Version: "));
    mfrc522[i].PCD_DumpVersionToSerial();

    delay(100);
  }

  Serial.println(F("--- END SETUP ---"));
}

/*
 * Helper function to dump a byte array as hex values to Serial.
 */
String dump_byte_array(byte *buffer, byte bufferSize) {
  String str = "";
  for (byte i = 0; i  <  bufferSize; i++) {
    str = str + ((((buffer[i] & 0xF0) >> 4) <= 9) ? (char)(((buffer[i] & 0xF0) >> 4) + '0') : (char)(((buffer[i] & 0xF0) >> 4) + 'A' - 10));
    str = str + (((buffer[i] & 0x0F) <= 9) ? (char)((buffer[i] & 0x0F) + '0') : (char)((buffer[i] & 0x0F) + 'A' - 10));
  }
  return str;
}

void loop() {
  
  bool puzzleSolved = true;

  bool changedValue = false;

  // Loop through each reader
  for (uint8_t i=0; i < numReaders; i++) {
      // Init the sensor
      mfrc522[i].PCD_Init();

      // String to hold id detected by each sensor
      String readRFID = "";

      // If sensor detects a tag and can read it
      if (mfrc522[i].PICC_IsNewCardPresent() && mfrc522[i].PICC_ReadCardSerial()) {
        // Extract id from tag
        readRFID = dump_byte_array(mfrc522[i].uid.uidByte, mfrc522[i].uid.size);
      }

        // If current reading is different from the last know reading
      if (readRFID != currentIDs[i]) {
        // Set flag to show that puzzle state has changed
        changedValue = true;
        // Update stored value for this sensor
        currentIDs[i] = readRFID;
      }

      // If the reading fails to match the correct ID for this sensor
      if (currentIDs[i] != correctIDs[i]) {
        // the puzzle has not been solved
        puzzleSolved = false;
      }

      // Halt PICC
      mfrc522[i].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[i].PCD_StopCrypto1(); 
    }

    // If the changedValue has been set, at least one sensor has changed
    if (changedValue) {
      // Dump to serial the current state of all sensors
      for (uint8_t i=0; i < numReaders; i++) {
        Serial.print(F("Reader #"));
        Serial.print(String(i));
        Serial.print(F(" on pin #"));
        Serial.print(String(SS_PINS[i]));
        Serial.print(F(" detected tag: "));
        Serial.println(currentIDs[i]);
      }

      Serial.println("-----");
    }

  // if puzzleSolved is set, all sensors detected the correct ID
  if (puzzleSolved) {
    onSolve();
  }

  delay(4);
}


/**
 * Called when correct puzzle solution has been entered
  */

void onSolve() {

  #ifdef DEBUG
  // Print debugging message
  Serial.println(F("Puzzle solved!"));
  
  // Puzzel opgelost dus lock moet lossen, dus power high?  

  #endif

  while(true) {
  }

}
