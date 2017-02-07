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

//Creates 2 Integers to denote the Pins to which the Flex Sensors are attached to
int flexSensor1 = 0;
int flexSensor2 = 1;

//Create 2 Integers to denote the Values taken from Flex Sensor Readings
int flexSensorValue1;
int flexSensorValue2;

//Creates 2 Integers to denote the Pins to which the Buttons are attached to
int pushButton1 = 2;
int pushButton2 = 3;

//This creates 2 Integers to denote the Values taken from Button Readings
int pushButtonReadings1;
int pushButtonReadings2;

//Creates 2 Integers to denote the Pins to which the Servos are attached to
int servoPin1 = 9; //This Pin is a PWM
int servoPin2 = 11; //This Pin is a PWM

//Create 2 Integers to denote the Pins to which a LED and a Speaker is attached to
int lightPin = 13;
int soundPin = 5;

//Creates 2 Integers to denote the Pins to which the Flex Sensors are attached to
int ldrSensor = 2;

//Creates 1 Integer to denote the Values taken from the LDR Readings
int ldrValue;

//Create 2 Integers to denote the Pins for the LDR Light LED connections
int ldrHigh = 6;
int ldrLow = 4;

// ----- CODE METHODS ----- \\

//This is the Setup Method. 
//This is run first by Any Arduino.
void setup() {
  
	//This starts the Serial Monitor to start, at 9600 Bauds
	Serial.begin(9600);
  
	//This attaches each Servo to the Given Pin number
	servo1.attach(servoPin1); //Attaches a Servo to Pin 9 which is PWM
	servo2.attach(servoPin2); //Attached a Servo to Pin 11 which is PWM
  
	//Taking the Pin Number, it declares it either an INPUT or an OUTPUT
	pinMode(pushButton1, INPUT); //Pin 2 is now an INPUT. 
	pinMode(pushButton2, INPUT); //Pin 3 is now an INPUT. 
	pinMode(lightPin, OUTPUT); //Pin 13 is now an OUTPUT.
	pinMode(soundPin, OUTPUT);//Pin 5 is now an OUTPUT.
        pinMode(ldrHigh, OUTPUT);//Pin 6 is now an OUTPUT.
        pinMode(ldrLow, OUTPUT);//Pin 4 is now an OUTPUT.
  
} //End of Setup Method

//This is the Loop Method. 
//This is run by the Arduino over and over again after the Setup Method
void loop() {
  
        //I call a method to get the Readings of the Push Buttons
        //This is a Digital Read Function because the Buttons are connected to the Digital Pins
	pushButtonReadings1 = readDigitalValues(pushButton1); //Store Value in Variable
        pushButtonReadings2 = readDigitalValues(pushButton2); //Store Value in Variable
        
        //I call a method to get the Readings of the Flex Sensors and the LDR
        //This is a Analog Read Function because the Flex Sensors and the LDR are connected to the Analog Pins
	flexSensorValue2 = readAnalogValues(flexSensor2); //Store Value in Variable
	flexSensorValue1 = readAnalogValues(flexSensor1); //Store Value in Variable
        ldrValue = readAnalogValues(ldrSensor); //Store Value in Variable
	
	//I call a method to Map the Values of the Sensors to the Servos
        //This uses the Readings from the previous Methods
        //This uses the map() function
	mapServos();

        //I call a Method to get the mapped values and assign them to the Servos
        //This uses the Readings from the previous Methods
        //This uses the .write function which is part of the Servo Library
        writeServos(servo1, servoPosition1);
        writeServos(servo2, servoPosition2);
        
        //I call a Method to check the Button State and Switch on the Light/Sound
        //This uses Readings from the previous Methods
        //This uses an If function
        checkStateButton(pushButtonReadings1, lightPin);
        checkStateButton(pushButtonReadings2, soundPin);
        
        //I call a Method to check the LDR and then light up the correct lights
        //This uses Readings from the previous Methods
        //This uses an If function
        checkLDRState(ldrValue);
	
	//I call a Method to Print to the Monitor
        //This uses all the Readings
        //Prints Lines of Readings
        printMonitor();
        
	//This Delays the Code for 15 Milliseconds. 
	//This allows the Serial Monitor to print the lines and for the Servos to Get to their Angles.
	delay(15);
        


} //End of Loop Method

//Method for Calling Push Button Values
//Public Method that returns an Integer
int readDigitalValues(int Pin) {
  
        int Value; //Create new Integer called "Value"
        Value = digitalRead(Pin); //Get the Digital Value from given Pin Number
        
        return Value; //Return the Value
        
} //End of Method

//Method for Calling Analog Values
//Public Method that returns an Integer
int readAnalogValues(int Pin) {
  
        int Value; //Create new Integer called "Value"
        Value = analogRead(Pin); //Get the Analog Value from given Pin Number
        
        return Value; //Return the Value
        
} //End of Method

//This Method will Map the Flex Sensor Values to the Servo Position
//Public Method that returns nothing (Setter Method)
void mapServos() {

        //Gets the Variable and assigns the Angle mapped
        servoPosition1 = map(flexSensorValue1, 240, 150, 0, 179); //Maps and stores Variable
	servoPosition2 = map(flexSensorValue2, 467, 300, 0, 179); //Maps and stores Variable
	
} //End of Method

//This Method will set the Servo position
//Public Method that returns nothing (Setter Method)
void writeServos(Servo servoObject, int Value) {
  
        servoObject.write(Value); //Writes Angle to Servo
        
} //End of Method

//This Method will check the State of a button and Write Accordingly
//Public Method that returns nothing (Setter Method)
void checkStateButton(int Value, int Pin) {
 
        if (Value == 1) //Check if the Button is being Clicked
	{ //If True then
    
		digitalWrite(Pin, HIGH); //Send out a current on the Pin
    
	} else { //Otherwise

		digitalWrite(Pin, LOW); //Do Not Send out a current on the Pin
    
	} //End of Checking and if Statement
  
} //End of Method

//This Method will check the LDR Value and Write Accordingly
//Public Method that returns nothing (Setter Method)
void checkLDRState(int Value) {
  
        if (Value > 300) //Check if LDR is more than Relevant Light Level
        { //If True then
          
          digitalWrite(ldrLow, LOW); //Set Orange LED off
          digitalWrite(ldrHigh, HIGH); //Set Green LED on
          
          
        } else { //Otherwise
          
          digitalWrite(ldrHigh, LOW); //Set Green LED off
          digitalWrite(ldrLow, HIGH); //Set Orange LED on
          
        } //End of Checking and if Statement
  
} //End of Method

//This Method will Print to the Monitor
//Public Method that Returns nothing (Print Method)
void printMonitor() {
  
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
	Serial.print(pushButtonReadings2);
        Serial.print("\t LDR Input = ");
        Serial.println(ldrValue); 
  
} //End of Method
