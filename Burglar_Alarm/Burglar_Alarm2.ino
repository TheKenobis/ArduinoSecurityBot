const int trigPin = 2;
const int echoPin = 4;

const int SendSetupBit = 5;
const int RecieveSetupBit = 6;
const int ChangeinSensor = 7;
const int HardwareError = 8;

const int DelayVar = 100;

const int MaxRange = 0;

boolean FinalSetup = false;

// establish variables for duration of the ping, 
// and the distance result in inches and centimeters:
long duration, inches, cm, MaxDistance = 0;
int SafetyNet = 3;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);

  for(int i=8; i<11; i++) {
     pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
  }
  digitalWrite(8, HIGH);
  Serial.print(9);
  while(FinalSetup == false) {

    if(Serial.available() > 0) {            //needs serial communication for it to work, either java or serial monitor
      int IncomingByte = Serial.read()-'0';
    
      if(IncomingByte != RecieveSetupBit) {
        Serial.println(SendSetupBit);
      
      } else {
        FinalSetup = true;
      } 
    
      delay(DelayVar);
      
    }  /*else {
      Serial.println("ERROR..............");
    } */
    
  } 
  
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  
  
  while(millis() < 8000) { 
    UltraSonic();
    //Serial.println(cm);
    
    if(cm > MaxDistance) {
      MaxDistance = cm;
    }
      
  }
  
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);

}

void loop() {
  
   /*Serial.println(cm);
    Serial.println(MaxDistance);
    Serial.println(" ");*/
    delay(1000);
    
    if(Serial.available() > 0) {  //needs serial communication for it to work, either java or serial monitor
      
      Serial.flush();
      
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
  
      UltraSonic();
      //Serial.println(cm);
      
      if(cm < (MaxDistance-SafetyNet)) {
        //Serial.println("Report");
        Serial.print(ChangeinSensor);
      
      } else if(cm <= 0){
        Serial.print(HardwareError);
      
      } else {
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW);
        digitalWrite(10, LOW);
      }
      
    digitalWrite(12, LOW);
    delay(100);
    
    }  /*else {
      Serial.println("ERROR..............");*/
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
    
    delay(DelayVar);
}

long microsecondsToCentimeters(long microseconds) {
    // The speed of sound is 340 m/s or 29 microseconds per centimeter.
    // The ping travels out and back, so to find the distance of the
    // object we take half of the distance travelled.
    return microseconds / 29 / 2;
}