//----PINS----

//button Pin
const int buttonPin = 2;

//buzzer pin
const int buzzerPin = 4;

//leds pins
const int redPasserLedPin = 6;
const int greenPasserLedPin = 7;
const int greenCarLedPin = 8;
const int yellowCarLedPin = 9;
const int redCarLedPin = 10;



//----INITIAL STATES----

//button initial state
bool buttonState = LOW;

//leds initial states - red for pedestrians, green for cars
bool redPasserLedState = HIGH;
bool greenPasserLedState = LOW;
bool greenCarLedState = HIGH;
bool yellowCarLedState = LOW;
bool redCarLedState = LOW;

//buzzer initial state
bool buzzerState = LOW;



//----HELPER VARIABLES---- 

//variables for reading the button
bool pressedButton = 0;
bool reading = HIGH;
bool previousReading = HIGH;
unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

//variables for starting the buzzer
int buzzerTone = 1500;
int toneDuration = 10;
unsigned int buzzerInterval = 1000;
unsigned int buzzerIntermittenInterval = 500;
unsigned int lastBuzzerPlay = 0;

//variables for blinking green
unsigned int lastGreenBlink = 0;
unsigned int blinkingDuration = 500;

//states' intervals
unsigned long startCrosswalk = 0;
unsigned int stateOneInterval = 10000;
unsigned int stateTwoInterval = 13000;
unsigned int stateThreeInterval = 23000;
unsigned int stateFourInterval = 28000;

void setup() {
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  pinMode(redPasserLedPin, OUTPUT); 
  pinMode(greenPasserLedPin, OUTPUT);
  pinMode(greenCarLedPin, OUTPUT); 
  pinMode(yellowCarLedPin, OUTPUT); 
  pinMode(redCarLedPin, OUTPUT);  

  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);

}

void loop() {
  
  digitalWrite(greenCarLedPin, greenCarLedState);
  digitalWrite(yellowCarLedPin, yellowCarLedState);
  digitalWrite(redCarLedPin, redCarLedState);
  digitalWrite(greenPasserLedPin, greenPasserLedState);
  digitalWrite(redPasserLedPin, redPasserLedState);

  readingButton();

  if(pressedButton){
    if (millis() - startCrosswalk > stateOneInterval && greenCarLedState){
      //State 2
      //10 seconds after pressing the button
      //yellow for cars
      //red for people
      //duration: 3 sec
      state2();
    }
    else if (millis() - startCrosswalk > stateTwoInterval && yellowCarLedState){
      //State 3
      //red for cars
      //green for pedestrians
      //duration: 10 sec
      //buzzer starts
      state3();
    }
    else if (millis() - startCrosswalk > stateThreeInterval && millis() - startCrosswalk <= stateFourInterval && redCarLedState){
      //State 4
      //red for cars
      //intermitten green for pedestrians
      //duration: 5 sec
      //buzzer start beeping faster
      state4();        
    }
    else if (millis() - startCrosswalk > stateFourInterval){
      //the algorithm is over, everything returns to the default state
      //green for cars
      //red for people
      //until the button is pressed again
      state1();
    }

   playBuzzer();
   
  }
}


void readingButton(){
  //read the state of the button
  reading = digitalRead(buttonPin);

  //checking if there is a change from its previous state
  if (reading != previousReading){
    lastDebounceTime = millis();
  }
  
  //checking if the button was pressed intentionally or if it was just noise
  if (millis() - lastDebounceTime > debounceDelay){
    if (reading != buttonState){
      buttonState = reading;
      
      //checking if the button was not pressed previously, before the semaphore got to its end
      if (buttonState == LOW && !pressedButton){
        //the button was pressed, so the algorithm should start now
        pressedButton = 1;
        startCrosswalk = millis();
      }
    }
  }
  previousReading = reading;
}


void state1(){
  //default
  //red for people, green for cars
  //duration: indefinite
  greenPasserLedState = LOW; 
  redPasserLedState = !redPasserLedState;
  greenCarLedState = !greenCarLedState;
  redCarLedState = !redCarLedState;
  
  //now the button can be pressed again
  pressedButton = 0;
}


void state2(){
  //red for people, yellow for cars
  //duration: 3 sec
  greenCarLedState = !greenCarLedState; 
  yellowCarLedState = !yellowCarLedState;
}


void state3(){
  //green for people, red for cars
  //duration: 10 sec
  yellowCarLedState = !yellowCarLedState; 
  redCarLedState = !redCarLedState;
  greenPasserLedState = !greenPasserLedState; 
  redPasserLedState = !redPasserLedState;
  buzzerState =! buzzerState;
}

void state4(){
  //blinking green for people, red for cars
  //duration: 5 sec
  if(millis()-lastGreenBlink > blinkingDuration){
    greenPasserLedState = !greenPasserLedState; 
    lastGreenBlink = millis();
  }
}


void playBuzzer(){
  Serial.println(millis()- startCrosswalk);
  if (buzzerState){
    if(millis()- startCrosswalk > stateFourInterval){
      //the buzzer stops, state 1
      buzzerState = !buzzerState;
    }
    else if(millis()- startCrosswalk > stateThreeInterval && millis() - lastBuzzerPlay > buzzerIntermittenInterval){
      //the buzzer starts playing faster, state 4
      tone(buzzerPin, buzzerTone, toneDuration);
      lastBuzzerPlay = millis();
    }
    else if(millis()- startCrosswalk > stateTwoInterval && millis()-lastBuzzerPlay > buzzerInterval){
      //the buzzer start playing, state 3
      tone(buzzerPin, buzzerTone, 10);
      lastBuzzerPlay = millis();
    }
  }  
}
