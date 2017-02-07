/* ----------------------------------------------------------------------
							THE HAND SOURCE CODE
	
	All code in this file belongs to Amrit Amar and no one has the right
	to reproduce this code without permission from Amrit Amar.
	
	This code is for the BOTHO COLLEGE ICT LINKZ CHALLENGE 2013. The
	project is called "The Hand". This code calculates the Input from
	connected Flex Sensors and produces the Output to Servos, which
	control Finger Movement on a Artificial Hand. The code also Implements
	2 Buttons which control various functions.
	
	--------------------------------------------------------------------- */

// ----- CODE DECLARATIONS ----- \\

//Imports Servo Library for using it's Functions
#include <Servo.h>

//Creates 2 Integers to store Mapped Servo Positions
int servoPosition1;
int servoPosition2;

//Creates 2 Servo Objects
Servo servo1;
Servo servo2;

//Creates 2 Integers to denote the Pins to which the Buttons are attached to
int pushButton1 = 2;
int pushButton2 = 3;

//Creates 2 Integers to denote the Pins to which the Servos are attached to
int servoPin1 = 9; //This Pin is a PWM
int servoPin2 = 11; //This Pin is a PWM

//Create 2 Integers to denote the Pins to which a LED and a Speaker is attached to
int lightPin = 13;
int soundPin = 5;

// ----- CODE METHODS ----- \\

//This is the Setup Method. This is run first by Any Arduino.
void setup() {
  
	//This starts the Serial Monitor to start, at 9600 Bauds
	Serial.begin(9600);
  
	//This is a Servo Library Function. It attached the servo to the Pin given by the Argument
	servo1.attach(servoPin1); //Attaches a Servo to Pin 9 which is PWM
	servo2.attach(servoPin2); //Attached a Servo to Pin 11 which is PWM
  
	//This sets the given Pin (Argument 1) to either be a INPUT or a OUTPUT (Argument 2)
	pinMode(pushButton1, INPUT); //Pin 2 is now an INPUT. 
	pinMode(pushButton2, INPUT); //Pin 3 is now an INPUT. 
	pinMode(lightPin, OUTPUT); //Pin 13 is now an OUTPUT.
	pinMode(soundPin, OUTPUT);//Pin 5 is now an OUTPUT.
  
}

//This is the Loop Method. This is run by the Arduino over and over again after the Setup Method
void loop() {
  
	//This creates 2 Integers to denote the Values from the Method called.
	//The Method called basically gets the State or Values given by the Pin (Argument 1).
	//The Pins here are Pin 2 and Pin 3.
	int pushButtonReadings1 = digitalRead(pushButton1); //The Integer Stores the Value returned from the Button on Pin 2
	int pushButtonReadings2 = digitalRead(pushButton2); //The Integer Stores the Value returned from the Button on Pin 3
  
	//Here, the same thing as above happens, except the Readings are from the Analog Input Pins
	//The Pins have the Flex Sensors attached to them.
	int flexSensorValue2 = analogRead(A0); //The Integer Stores the Value returned from the Flex Sensor on Pin A0
	int flexSensorValue1 = analogRead(A1); //The Integer Stores the Value returned from the Flex Sensor on Pin A1
	
	//This Code takes the Input Values from the Analog Inputs and Maps them from 0 to 179 (ANGLES).
	//The Arguments are: map(PinValues, Maximum Integer Value from PinValues, Minimum Integer Value from PinValues, mapped Maximum Value, mapped Minimum Value)
	//For Example: Here, the readings are from the Analog Input Pins earlier.
	//I checked the Readings and found that the Flex Sensor UNBENT gave a value of 467. This is my Maximum Value.
	//I bent the Flex Sensor and chose a appropriate value.
	//Then I specified the number to which 467 is to. 467 : 0.
	//Same thing with the other Values.
	//The Code automatically maps itself out through-out the given Values
	servoPosition1 = map(flexSensorValue1, 467, 300, 0, 179); //Takes Integer created from mapping and stores it in the Variable
	servoPosition2 = map(flexSensorValue2, 240, 150, 0, 179); //Takes Integer created from mapping and stores it in the Variable
	
	//Now that I have my Angles mapped from the Flex Sensors, I can now write them to the Servo using their Write Function
	//This Writes the Angles to the Servo and Servo adjusts itself to the Angles Given
	servo1.write(servoPosition1); //The First Servo is given the angle
	servo2.write(servoPosition2); //The Second Servo is given the angle
	
	//This code writes Values to the Serial Monitor.
	//This is useful for Debugging and Tweaking Values
	Serial.print("Finger 1 Sensor Input = " );                       
	Serial.print(flexSensorValue1);      
	Serial.print("\t Finger 2 Sensor Input = ");      
	Serial.print(flexSensorValue2);
	Serial.print("\t Servo 1 Output = ");      
	Serial.print(servoPosition1);
	Serial.print("\t Servo 2 Output = ");
	Serial.print(servoPosition2);
	Serial.print("\t Button 1 Input = ");
	Serial.print(pushButtonReadings1);
	Serial.print("\t Button 2 Input = ");
	Serial.println(pushButtonReadings2);
	
	//This is the Code for Switching on the Light on pressing the Button.
	//It reads the State of the Button and checks if it is being clicked (1) or it is not (0).
	//It then executes the Code.
	if (pushButtonReadings1 == 1) //Check if the Button is being Clicked
	{ //If True then
    
		digitalWrite(lightPin, HIGH); //Send out a current on the Pin
    
	} else { //Otherwise

		digitalWrite(lightPin, LOW); //Do Not Send out a current on the Pin
    
	} //End of Checking and if Statement
	
	//This is the Code for Switching on the Sound on pressing the Button.
	//It reads the State of the Button and checks if it is being clicked (1) or it is not (0).
	//It then executes the Code.
	if (pushButtonReadings2 == 1) //Check if the Button is being Clicked
	{ //If True then
    
		digitalWrite(soundPin, HIGH); //Send out a current on the Pin
    
	} else { //Otherwise
    
		digitalWrite(soundPin, LOW); //Do Not Send out a current on the Pin
    
	} //End of Checking and if Statement	
	
	delay(15);  //This Delays the Code for 15 Milliseconds. 
				//This allows the Serial Monitor to print the lines and for the Servos to Get to their Angles.
  
}
