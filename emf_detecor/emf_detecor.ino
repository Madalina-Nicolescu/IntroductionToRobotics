const int pinA = 2;
const int pinB = 3;
const int pinC = 4;
const int pinD = 5;
const int pinE = 6;
const int pinF = 7;
const int pinG = 8;
const int pinDP = 9;
const int buzzerPin = 10;
const int antennaPin = A5;


int toneMultiplier = 100;
int buzzerDuration = 100;
int senseLimit = 100; // raise this number to decrease sensitivity (up to 1023 max)
int antennaValue = 0; 
int numberOfReadings = 15;
int index = 0;                            
int total = 0;                           
int average = 0; 
int updateTime = 50;


const int segSize = 8;
const int noOfDigits = 10;
int segments[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

bool digitMatrix[noOfDigits][segSize-1] = {
// a  b  c  d  e  f  g
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void displayNumber(byte digit){
  for(int i = 0; i < segSize - 1; i++){
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
}

void setup() {
  for (int i = 0; i < segSize; i++){
    pinMode(segments[i], OUTPUT);
  }

  pinMode(antennaPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}


void loop() {

  //for 15 readings, we calculate the average value of the atenna input
  if (index < numberOfReadings){
    antennaValue = analogRead(antennaPin);
    Serial.println(antennaValue);
    antennaValue = constrain(antennaValue, 0, senseLimit);
    antennaValue = map(antennaValue, 0, senseLimit, 0, noOfDigits);
    total += antennaValue;
    index++;
  }
  else if (index == numberOfReadings){
    average = total/numberOfReadings;
    index = 0;
    total = 0;
    //we display the average on the 7-segment-display
    displayNumber(average);
    if (average != 0){
      tone(buzzerPin, average * toneMultiplier, buzzerDuration);
    }
  }
  delay(updateTime);
}
