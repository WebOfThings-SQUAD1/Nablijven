#include <Wire.h> 
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

const int secretCode[] = {1, 9, 9, 3};
const int ledPins[] = {5,6,7,8};
const int pinA = 3; // CLK
const int pinB = 4; // DT
const int SW = 2; // SW

const int servo = 9;

int guessed[4];
int amountGuessed = 0;
int amountCorrect = 0;
int encoderPosCount = 0;
int pinALast;
int aVal;
boolean bCW;

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t Lock[8] = {0xe,0x11,0x11,0x1f,0x1b,0x1b,0x1f,0x0};
uint8_t Block[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

void setup() { 
  lcdSetup();
   
  for(int i=0;i<=4;i++){
    pinMode(ledPins[i],OUTPUT);
  }
  pinMode (servo, OUTPUT);
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  pinMode (SW, INPUT);
  analogWrite(servo, 13);
  pinALast = digitalRead(pinA);
  Serial.begin (9600);
}
void loop() {
  // Huidige stand
  aVal = digitalRead(pinA);
  if (digitalRead(SW) == LOW) {
    Serial.println("Pushed knob");
    Serial.println(encoderPosCount/2);
    while (digitalRead(SW) == LOW) delay(5);
    guessed[amountGuessed] = encoderPosCount/2;
    amountGuessed++;
    if(amountGuessed == 4){
      showResult();
    }    
  }
  if (aVal != pinALast) {
    if (digitalRead(pinB) != aVal) { // rechts draaien
      encoderPosCount ++;
      if(encoderPosCount == 19) encoderPosCount = 0;
      bCW = true;
    } else {
      bCW = false;
      encoderPosCount--;
      if(encoderPosCount == -1) encoderPosCount = 18;
    }
    Serial.print ("Rotated: ");
    if (bCW) {
      Serial.println ("clockwise");
    } else {
      Serial.println("counterclockwise");
    }
    Serial.print("Encoder Position: ");
    Serial.println(encoderPosCount);
    if(amountGuessed<4)updateCharacter(amountGuessed);
  }
  pinALast = aVal;
}

void updateCharacter(int index){
  lcd.setCursor(8+index, 2);
  lcd.blink();
  lcd.print(encoderPosCount/2);
}

void lcdSetup(){
  lcd.init();
  lcd.clear();  
  lcd.backlight();   
  lcd.createChar(0, Lock);
  lcd.createChar(1, Block);
  
  lcd.home();
  for(int i=0; i<20; i++){
    lcd.printByte(1);
  }
  lcd.setCursor(0, 1);
  lcd.printByte(1);
  lcd.print(' ');
  lcd.printByte(0);
  lcd.print(" Voer code in:  ");
  lcd.printByte(1);
  lcd.setCursor(0,2);
  lcd.printByte(1);
  lcd.print("                  ");
  lcd.printByte(1);
  lcd.setCursor(0,3);
  for(int i=0; i<20; i++){
    lcd.printByte(1);
  }
}

void showResult(){
  lcd.noBlink();
  
  for(int i=0;i<=4;i++){
    if(guessed[i] == secretCode[i]){
      amountCorrect++;
      digitalWrite(ledPins[i],HIGH);
    }
  }
  if(amountCorrect==4) analogWrite(servo, 25);
}
