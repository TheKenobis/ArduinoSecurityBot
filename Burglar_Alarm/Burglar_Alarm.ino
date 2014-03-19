//Ultra sonic sensor pin numbers
const int trigPin = 2;
const int echoPin = 4;

//Vaules which will be used during the java communication phase
const int SendSetupBit = 5;
const int RecieveSetupBit = 6;
const int ChangeinSensor = 7;
const int HardwareError = 8;

//Sets up certain delay amount which will be used later
const int DelayVar = 2000;
const int DelaySec = 100;

boolean FinalSetup = false;

//Vaules which will be used while the senso is activated
long duration, cm, MaxDistance = 0;
//Value will help prevent false alarms, as sensor can sometimes produce vaules higher or lower than the real value being produced
int SafetyNet = 3;

void setup() {
  //Serial bit rate at 9600, java needs to be the same
  Serial.begin(9600);                   

  //for loop setting up the lights to output, then turning them off
  for(int i=8; i<11; i++) {                
     pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
  }  
  
  //Turns the red led on
  digitalWrite(8, HIGH);  
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  
  //while loop which prevents the arduino from starting, before it is connected to the java program  
  while(FinalSetup == false) {
  
    //Prints the number 5 to the serial port, which will be used by the java
    Serial.print(SendSetupBit);
    delay(DelayVar); 
    
    //The hardware is reading the serial port for the number 6, which will produced by the java when it finds the number 5 
    int IncomingByte = Serial.read()-'0';
    
    //If the number 6 is found the while loop is broken
    if(IncomingByte == RecieveSetupBit) {
      FinalSetup = true;
    }
      
  }
  
  //Turns the yellow led on, red off
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  delay(1);
  
  //Calls the 'Calibration' subroutine
  Calibration();
  
  //Turns the yellow led off, the green on
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(2000);

}

void loop() {
  
  //Calls the 'UltraSonic' subroutine
  UltraSonic();
  //Small delay prevents the program from running to quick and skipping code
  delay(1);
  
  //If statenment is to check that there has been has been any motion
  if(cm < (MaxDistance-SafetyNet)) { //code when enemy is near
    
    //Prints to the serial port the number 7
    Serial.println(ChangeinSensor); 
    
    //Turns the red led on, the green off
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);  
    digitalWrite(10, LOW);  
    
    //delay has been introduced to aviod spam, delay of 10 secs
    delay(10000);
  
  //This else if statement is used to detect if the hardware is not working properly    
  } else if(cm <= 0){
    //Prints to the serial port the number 8
    Serial.println(HardwareError);
    delay(10000);
  
  //    
  } else if(cm > (MaxDistance+SafetyNet) {
    
    //Turns the yellow led on, the other off
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);  
    digitalWrite(10, LOW);  

    //Calls the 'Calibration' subroutine
    Calibration();    

    //Turns the green led on, the other off
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);  
    digitalWrite(10, HIGH);  
    
    
  } else{
    //Turns the green led on, the other off
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);  
    digitalWrite(10, HIGH);  

  
  }
}

void Calibration() {
  
  //While loop lasts for about 5 secs, for best results 
  while(millis() < 8000) { 
    //Calls the 'UltraSonic' subroutine
    UltraSonic();
    
    //Allows the adjustment of the 'MaxDistance', this is done to allow the product to be used in different door frames etc
    if(cm > MaxDistance) {
      MaxDistance = cm;
    }
      
  }
}

void UltraSonic() {  
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    //Read the signal from the sensor: a HIGH pulse whose
    //Duration is the time (in microseconds) from the sending of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
  
    //Convert the time into a distance
    cm = microsecondsToCentimeters(duration);
    
    //delay(DelayVar);
}

long microsecondsToCentimeters(long microseconds) {
    //The speed of sound is 340 m/s or 29 microseconds per centimeter.
    //The ping travels out and back, so to find the distance of the
    //object we take half of the distance travelled.
    return microseconds / 29 / 2;
}
