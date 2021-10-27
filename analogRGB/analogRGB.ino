//led pins
const int ledRedPin = 11;
const int ledGreenPin = 10;
const int ledBluePin = 9;

//potentiometer pins
const int potRedPin = A0;
const int potGreenPin = A1;
const int potBluePin = A2;

//max values
const int maxPotValue = 1023;
const int maxLedValue = 255;

//input values from potentiometers
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

//intensity of color
int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;

void setup() {
  //initialize led pins as output pins
  pinMode(ledBluePin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(ledRedPin, OUTPUT);

  //initialize potentiometer pins as input pins
  pinMode(potBluePin, INPUT); 
  pinMode(potGreenPin, INPUT);
  pinMode(potRedPin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  //read the input on analog pins
  redValue = analogRead(potRedPin);
  greenValue = analogRead(potGreenPin);
  blueValue = analogRead(potBluePin);

  //map the value of the input to the values of each led
  redBrightness = map(redValue, 0, maxPotValue, 0, maxLedValue);
  greenBrightness = map(greenValue, 0, maxPotValue, 0, maxLedValue); 
  blueBrightness = map(blueValue, 0, maxPotValue, 0, maxLedValue);   

  analogWrite(ledRedPin, redBrightness);
  analogWrite(ledGreenPin, greenBrightness);
  analogWrite(ledBluePin, blueBrightness);
}
