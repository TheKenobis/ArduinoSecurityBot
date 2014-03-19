const int trigPin = 2;
const int echoPin = 4;

const int SendSetupBit = 5;
const int RecieveSetupBit = 6;
const int ChangeinSensor = 7;
const int HardwareError = 8;

const int DelayVar = 2000;
const int DelaySec = 100;
const int MaxRange = 0;

boolean FinalSetup = false;

long duration, cm, MaxDistance = 0;
int SafetyNet = 3;

void setup() {
  Serial.begin(9600);                     //Serial bit rate at 9600, java needs to be the same

  for(int i=8; i<11; i++) {                //for loop setting up the lights to output
     pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
  }  
  
  digitalWrite(8, HIGH);  
  
  while(FinalSetup == false) {              //while loop which prevents the arduino from starting, before it is connected to the java program
     Serial.print(SendSetupBit);
     delay(DelayVar); 
     
     int IncomingByte = Serial.read()-'0';
     if(IncomingByte == RecieveSetupBit) {
       FinalSetup = true;
     }
      
  }
  
 digitalWrite(8, LOW);
 digitalWrite(9, HIGH);
 digitalWrite(10, LOW);
 delay(1);
 
 Calibration();

 digitalWrite(8, LOW);
 digitalWrite(9, LOW);
 digitalWrite(10, HIGH);
 
delay(2000);

}

void loop() {
  UltraSonic();
    delay(1);
  //Serial.println(cm);
  
  
  if(cm < (MaxDistance-SafetyNet)) { //code when enemy is near
    Serial.print(ChangeinSensor); 
    digitalWrite(8, HIGH);
  digitalWrite(9, LOW);  
    digitalWrite(10, LOW);  
    
    //delay has been introduced to aviod spam
    delay(10000);
      
  } else if(cm <= 0){
    Serial.print(HardwareError);
    //delay(DelaySec);
      
  } else{
      digitalWrite(8, LOW);
  digitalWrite(9, LOW);  
    digitalWrite(10, HIGH);  

  
  }
}

void Calibration() {
  
  while(millis() < 8000) { 
    UltraSonic();
    //Serial.println(cm);
    
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
  
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
  
    // convert the time into a distance
    cm = microsecondsToCentimeters(duration);
    
    //delay(DelayVar);
}

long microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return microseconds / 29 / 2;
}
