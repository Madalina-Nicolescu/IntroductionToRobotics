# IntroductionToRobotics
Repository for Introduction to Robotics laboratory homework. The course is taken in the 3rd year at the Faculty of Mathematics and Computer Science. Each section includes requirements, implementation details, code and image files.


# Homework 1


<details>
<summary>See details</summary>
<br>
  
## Requirements
Control an RGB led using 3 potentiometers, each of them manipulating one of the RGB colors' brightness

## Components
- RGB LED
- 3 potentiometers
- resistors
- wires

## Setup

<img src = "https://github.com/Madalina-Nicolescu/IntroductionToRobotics/blob/main/analogRGB/setup.jpeg" width = "500" height= "500">
<img src = "https://github.com/Madalina-Nicolescu/IntroductionToRobotics/blob/main/analogRGB/setup1.jpeg" width = "500" height= "500">

## Video
You can find a demo at: https://youtu.be/p0GPexGWI7E

</details>

# Homework 2

<details>
<summary>See details</summary>
<br>
  
## Requirements
Building  the  traffic  lights  for  a  crosswalk using 2 LEDs to represent the traffic lights for people (red and green) and 3 LEDs to represent the traffic lights for cars (red, yellow and green). The traffic lights simulator will start once the button is pressed, following these states:
 - State 1: (default, reinstated after state 4 ends):  green light for cars, red  light  for  people,  no  sounds.  Duration:  indefinite,  changed  bypressing the button.
 - State 2: (initiated by counting down 10 seconds after a button press): the  light  should  be  yellow  for  cars,  red  for  people  and  no  sounds. Duration:  3 seconds.
 - State 3: (iniated after state 2 ends): red for cars, green for people and a beeping sound from the buzzer at a constant interval.  Duration: 10 seconds.
 - State 4: (initiated after state 3 ends):  red for cars, blinking green for people and a beeping sound from the buzzer,  at a constant interval,  faster than the beeping in state 3.  Duration: 5 seconds.
  
Pressing the button in any other state than state 1 will have no effect.
  
  
## Components
- 5 leds
- 1 button
- 1 buzzer
- wires
- resistors

## Setup

<img src = "https://github.com/Madalina-Nicolescu/IntroductionToRobotics/blob/main/CrosswalkSimulator/setup.jpeg" width = "500" height= "500">
<img src = "https://github.com/Madalina-Nicolescu/IntroductionToRobotics/blob/main/CrosswalkSimulator/setup1.jpeg" width = "500" height= "500">

## Video
You can find a demo at: https://youtu.be/3DVMIWi4b4I

</details>

# Homework 3

<details>
<summary>See details</summary>
<br>
  
## Requirements
Build an EMF detector (a ghost detector) that should print the value on the 7-segment display and should make a sound based on the intensity.
  
  
## Components
- 7-segment display
- 1 buzzer
- wires
- resistors

## Setup

<img src = "https://github.com/Madalina-Nicolescu/IntroductionToRobotics/blob/main/emf_detector/setup.jpeg" width = "500" height= "500">

## Video
You can find a demo at: https://youtu.be/_BhiAIe7Mo0

</details>

# Homework 4

<details>
<summary>See details</summary>
<br>
  
## Requirements
Use  a  joystick  in  setting  the  values  on  each  digit  of  a  4-digit7-segment display connected to a shift register 74hc595.
- <b>First  state:</b>   you  can  use  a  joystick  axis  to  cycle  through  the  4digits; using the other axis does nothing.  A blinking decimal point shows the current digit position.  When pressing the button, using interrupts,  you  lock  in  on  the  selected  digit  and  enter  the second state. 
- <b>Second state:</b> the decimal point stays always on, no longer blinking and you can no longer use the axis to cycle through the 4 digits. Instead, using the other axis, you can increment on decrement the number on the current digit.  Pressing the button again returns you to the previous state.

The previous value is saved on eeprom and loaded whenever we start the arduino.
  
  
## Components
- 4-digit 7-segment display
- 74hc595  shiftregister
- joystick
- wires
- resistors

## Setup

<img src = "https://github.com/Madalina-Nicolescu/IntroductionToRobotics/blob/main/4digits_7segment/setup.jpeg" width = "500" height= "500">
<img src = "https://github.com/Madalina-Nicolescu/IntroductionToRobotics/blob/main/4digits_7segment/setup1.jpeg" width = "500" height= "500">

## Video
You can find a demo at: https://youtu.be/Jy5S3hLJrWk

</details>
