#include <EEPROM.h>

//---SHIFT REGISTER PINS---
const int dataPin = 12; //DS
const int latchPin = 11; //STCP
const int clockPin = 10; //SHCP

//---4-DIGIT 7-SEGMENT DISPLAY PINs---
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

//---JOYSTICK PINS---
const int pinSW = 2; //digital pin 2 or 3 to use interrupts
const int pinX = A0;
const int pinY = A1;

//---JOYSTICK HELPER VARIABLES---
bool swState =LOW;
int xValue =0;
int yValue =0;
bool joyMoved = false;
volatile bool buttonPressed = false;
int minThreshold=400;
int maxThreshold=600;

//---4-DIGIT 7-SEGMENT DISPLAY HELPER VARIABLES---
int currentPosition = 0;
bool dpState = LOW;
unsigned long lastBlink = 0;
unsigned int blinkingDuration = 300;
unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

const int dislpayCount = 4;
const int displayDigits[] = {
  segD1, segD2, segD3, segD4
};

const int noOfDigits = 10;
int digitArray[noOfDigits] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
};

//the memory adresses for each digit and for the dp
int displayEEPROMAdresses[dislpayCount] = {
  0,1,2,3
};
int dpEEPROMAdress = 4;

//array to stock the digits that will be displayed
int digitsToBeDisplayed[dislpayCount] = {
  0,0,0,0
};

void setup() {
//shift register pins
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

//display pins
  for(int i = 0; i < dislpayCount; i++){
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);//to turn on
  }

//joystick pins
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinSW,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinSW), readSWState, FALLING);

//read the last displayed values from eeprom memory
  for(int i = 0; i < dislpayCount; i++){
    digitsToBeDisplayed[i] = EEPROM.read(displayEEPROMAdresses[i]);
  }
  currentPosition = EEPROM.read(dpEEPROMAdress);

  Serial.begin(9600);
}

void loop() {
  writeDigits();
  
  if(buttonPressed){ //if the button is pressed, we can modify the value of the current digit
    yMove();
  }
  else{ //else, we can cycle through the 4 digits
    xMove();
  }
  
  //we need to update the eeprom memory with the new values
  updateEEPROM();
}


//Interrupts, swithcing between the states
void readSWState(){
  if (millis() - lastDebounceTime > debounceDelay) {
    buttonPressed = !buttonPressed;
  }
  lastDebounceTime = millis();
}

//writing the digits on the display
void writeDigits(){
   for(int i = 0; i < dislpayCount; i++){
    showDigit(i);
    if(i == currentPosition){
      if(buttonPressed){
        //the decimal point stays always on
        writeReg(digitArray[digitsToBeDisplayed[i]]+1);
      }
      else{
        //the decimal point is blinking
        blinkingDP();
      }
    }
    else{
      writeReg(digitArray[digitsToBeDisplayed[i]]);
    }
    delay(5);
  }
}

//select only one display, the other ones are off
void showDigit(int digitNumber){
  for(int i = 0; i < dislpayCount; i++){
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[digitNumber], LOW);
}

//writing the digit and the dp to shift register
void writeReg(int digit){
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}

//increasing or decreasing the value of the current digit
void yMove(){
  yValue = analogRead(pinY);
  if(yValue < minThreshold && joyMoved == false){
    if(digitsToBeDisplayed[currentPosition] < noOfDigits - 1) {
      digitsToBeDisplayed[currentPosition]++;
    }
    else{
      digitsToBeDisplayed[currentPosition] = 0;
    }
    joyMoved = true;
  }

  if(yValue > maxThreshold && joyMoved == false){
    if(digitsToBeDisplayed[currentPosition] > 0) {
      digitsToBeDisplayed[currentPosition]--;
    }
    else{
      digitsToBeDisplayed[currentPosition] = noOfDigits - 1;
    }
    joyMoved = true;
  }

  if(yValue >= minThreshold && yValue <= maxThreshold){
    joyMoved = false;
  }
}


//cycling  through  the  4 digits
void xMove(){
  xValue = analogRead(pinX);
  if(xValue < minThreshold && joyMoved == false){
    if(currentPosition < dislpayCount - 1) {
      currentPosition++;
    }
    else{
      currentPosition = 0;
    }
    joyMoved = true;
  }
  if(xValue > maxThreshold && joyMoved == false){
    if(currentPosition > 0) {
      currentPosition--;
    }
    else{
      currentPosition = dislpayCount - 1;
    }
    joyMoved = true;
  }

  if(xValue >= minThreshold && xValue <= maxThreshold){
    joyMoved = false;
  }
}

void blinkingDP(){
  if (millis() - lastBlink > blinkingDuration) {
      dpState = !dpState;
      lastBlink = millis();
    }
    if (!dpState) {
      writeReg(digitArray[digitsToBeDisplayed[currentPosition]] + 1);
    } else {
      writeReg(digitArray[digitsToBeDisplayed[currentPosition]]);
    }
}

void updateEEPROM(){
  for(int i = 0; i < dislpayCount; i++){
    EEPROM.update(i, digitsToBeDisplayed[i]);
    EEPROM.update(4, currentPosition);
  }
}
