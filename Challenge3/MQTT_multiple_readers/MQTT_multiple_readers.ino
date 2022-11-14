/*
 * ------------------------------------------------------------------
 */
/* BlinkOnWifiProp.ino
   MIT License (c) Faure Systems <dev at faure dot systems>

   Adapt the Blink example (https://www.arduino.cc/en/tutorial/blink) as a
   simple MQTT prop. Avoid delay() calls (except short ones) in loop() to
   ensure CPU for MQTT protocol. Use PropAction checks instead.

   Copy and change it to build your first Arduino connected prop, you will
   only be limited by your imagination.

   Requirements:
   - install ArduinoProps2.zip library and dependencies (https://github.com/gdm-webofthings/ArduinoProps2)
   - help: https://github.com/gdm-webofthings/ArduinoProps2/blob/main/help/ArduinoProp_sketch.md
*/
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


// If you're running xcape.io Room software you have to respect prop inbox/outbox
// topic syntax: Room/[escape room name]/Props/[propsname]/inbox|outbox
// https://xcape.io/go/room

/* ---------------
 * Configure your WiFi Prop here
 * --------------- */
WifiProp prop(u8"rfids", // as MQTT client id, should be unique per client for given broker
              u8"Room/squad1/Props/rfids/inbox",
              u8"Room/squad1/Props/rfids/outbox",
              "192.168.50.46", // your MQTT server IP address
              1883); // your MQTT server port;

/* ---------------
 * Define the variables (internal and Xcape.io variables)
 * --------------- */

PropDataLogical led(u8"led");
PropDataLogical connection(u8"connection");

void rfids();
void blink();
PropAction rfidsAction = PropAction(1000, rfids);
PropAction blinkAction = PropAction(1000, blink);

bool wifiBegun(false); // this is an internal variable to use
const char* ssid = "WOT";
const char *passphrase = "enterthegame";
const int propNumber = 30;

/* ---------------
 * Do the setup process
 * --------------- */

boolean SOLVED = false;

void setup() {

  Serial.begin(9600);
  SPI.begin();

  prop.addData(&led);
  prop.addData(&connection);

  prop.begin(InboxMessage::run); // this will start a loop to check for MQTT messages

  for (uint8_t i=0; i < numReaders; i++) {
    // Init the reader
    mfrc522[i].PCD_Init(SS_PINS[i], RST_PIN);
  }
}

/**
 * Validate the Wifi (do this in every loop)
 */
bool validateWifi() {
  // if the Wifi was not initialized yet
  if (!wifiBegun) {
    WiFi.begin(ssid, passphrase); // start connecting
    Serial.print("WiFiNNA firmware version: \t");
    Serial.println(WiFi.firmwareVersion());
    delay(250); // acceptable freeze for this prop (otherwise use PropAction for async-like behavior)
    // do static IP configuration disabling the dhcp client, must be called after every WiFi.begin()

    // uncomment this, to set the static IP address
    WiFi.config(IPAddress(192, 168, 50, 3), // local_ip
    IPAddress(192, 168, 50, 1),  // dns_server (sets to default gateway)
    IPAddress(192, 168, 50, 1),  // gateway
    IPAddress(255, 255, 255, 0)); // subnet

    // if the Wifi is in connected state
    if (WiFi.status() == WL_CONNECTED) {
      wifiBegun = true;
      Serial.print("Your local IP address: \t\t");
      Serial.println(WiFi.localIP());
      Serial.print("Your subnet mask: \t\t");
      Serial.println(WiFi.subnetMask());
      Serial.print("Gateway IP address: \t\t");
      Serial.println(WiFi.gatewayIP());
    } else {
      WiFi.end();
    }
  } else if (wifiBegun && WiFi.status() != WL_CONNECTED) { 
    WiFi.end();
    wifiBegun = false;
  }
}

void loop()
{
  validateWifi(); // validate the Wifi connection
  prop.loop(); // start looping the prop (superpowers gottin from xcape.io)
  connection.setValue(SOLVED); // read I/O
  rfidsAction.check();
  blinkAction.check();
}


 /*
  * ---------------------------------------
  */

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



void rfids()
{
  bool SOLVED = true;

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


  // if puzzleSolved is set, all sensors detected the correct ID
  if (puzzleSolved) {
    onSolve();
  }

  if(!SOLVED){
    connection.setValue(SOLVED);
  }
  if(SOLVED){
    digitalWrite(8, HIGH);
    connection.setValue(SOLVED);
    prop.sendOver("rfids");
  }
  prop.sendData(u8"test");
}

void blink()
{
}


/* ---------------
 * The Xcape.io logic/code
 * --------------- */

void InboxMessage::run(String a) {

  if (a == u8"app:startup")
  {
    prop.sendAllData();
    prop.sendDone(a);
  }
  else if (a == u8"reset-mcu")
  {
    prop.resetMcu();
  }
  else if (a == "1")
  {
    Serial.println("The lamp is on");
    prop.sendDone(a);
  }
  else if (a == "0")
  {
    Serial.println("The lamp is off");
    prop.sendDone(a);
  }
  else
  {
    // acknowledge omition of the prop command
    prop.sendOmit(a);
  }
}
