/*
  Senior Design Project
  February 2, 2017

  Russell Okamura
  David Hua
*/

//--------------------------------------------------------------------------------------
//  This code is to be uploaded to the Teensy unit inside the lockbox, and will
//  recieve information via RF module from the Raspberry Pi unit.  It will recieve the
//  correct passcode, and will then check the input from the user on the keypad and turn
//  turn a servo to unlock the box if the inout was successful.
//--------------------------------------------------------------------------------------

//=======================================================================================
//                                 RF MODULE SETUP
//=======================================================================================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_pin    0
#define CSN_pin   1

RF24 radio(CE_pin, CSN_pin);

const byte rxAddr[6] = "00001";

//=======================================================================================
//                                 KEYPAD SETUP
//=======================================================================================

#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 2, 3, 4, 5 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 6, 7, 8, 9 };

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char key;

//=======================================================================================
//                                 GENERAL SETUP
//=======================================================================================
char stage = 'A';
/*
  Stage A: Startup
  Stage B: Wait for any key input
  Stage C: Enter First Code
  Stage D: Generate random number and send to RB3
  Stage E: Get input from user and compare
*/
bool check = true;
int i = 0;

//=======================================================================================
//                                 PIN SETUP
//=======================================================================================
#define RED_LED    33
//#define BLUE_LED   10
#define GREEN_LED  34
#define SERVO_PIN  35

//=======================================================================================
//                            RANDOM NUMBER SETUP
//=======================================================================================
char rand_code[6] = {0};
char first_code[6] = {'2', '2', '2', '2', '2', '2'};
char input[6] = {0};
int counter = 0;

//=======================================================================================
//                            PIN SETUP FUNCTION
//=======================================================================================
void PinSetup(){
  pinMode(RED_LED, OUTPUT);
  //pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(29, INPUT);
}
//=======================================================================================
//                                 SETUP FUNCTION
//=======================================================================================
void setup() {
  Serial.begin(38400);
  delay(1000);
  BeginRF();
  PinSetup();
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  delay(1000);
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}



//=======================================================================================
//                                 MAIN FUNCTION
//=======================================================================================
void loop() {
  switch (stage) {

    case 'A' :
      delay(20);
      check = true;
      stage = 'B';
      break;

    case 'B' :
      Serial.print("Stage B\n");
      delay(50);
      key = keypad.getKey();
      if (key != NO_KEY) {
        stage = 'C';
        delay(1000);
      }
      randomSeed(millis());
      break;

    case 'C' :
      Serial.print("Stage C\n");
      ReadKeypad();
      for (i = 0; i < 6; i++) {
        if (input[i] != first_code[i]) {
          check = false;
        }
      }
      if (check) {
        stage = 'D';
        digitalWrite(GREEN_LED, HIGH);
        delay(750);
        digitalWrite(GREEN_LED, LOW);
      }
      else {
        stage = 'A';
        digitalWrite(RED_LED, HIGH);
        delay(750);
        digitalWrite(RED_LED, LOW);
      }
      break;

    case 'D' :
      Serial.print("Stage D\n");
      CreateRandomNumber();
      delay(1000);
      SendData();
      ConvertRand();
      stage = 'E';
      break;

    case 'E' :
      Serial.print("Stage E\n");
      ReadKeypad();
      for (i = 0; i < 6; i++) {
        if (input[i] != rand_code[i]) {
          check = false;
        }
      }
      if (check) {
//        stage = 'D';
        Serial.println("correct");
        digitalWrite(GREEN_LED, HIGH);
        delay(750);
        digitalWrite(GREEN_LED, LOW);
        delay(50);
       // digitalWrite(
      }
      else {
        Serial.println("incorrect");
        stage = 'A';
        digitalWrite(RED_LED, HIGH);
        delay(750);
        digitalWrite(RED_LED, LOW);
      }
      break;

    default :
      Serial.print("ERROR!\n");
  }
}



//=======================================================================================
//                                 INITIALIZE RF MODULE
//=======================================================================================
void BeginRF(){
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(0x76);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.enableDynamicPayloads();
  radio.powerUp();
}


//=======================================================================================
//                                READ KEYPAD FUNCTION
//=======================================================================================
void ReadKeypad() {
  while (counter != 6) {
    key = keypad.getKey();

    if (key != NO_KEY) {
      input[counter] = key;
      Serial.print(key);
      counter++;
      delay(200);
    }
  }
  counter = 0;
  Serial.print("\n");
}

//=======================================================================================
//                                 RANDOM NUMBER FUNCTION
//=======================================================================================
void CreateRandomNumber() {
  for (i = 0; i < 6; i++) {
    rand_code[i] = random(10);
  }
}

void ConvertRand(){
  for (i = 0; i < 6; i++) {
    rand_code[i] += 48;
  }
}
//=======================================================================================
//                                 TRANSMISSION FUNCTION
//=======================================================================================
void SendData() {
  radio.write(&rand_code, sizeof(rand_code));
  delay(1000);
}
