const int trigPin = 2;
const int echoPin = 4;

const int RecieveSetupBit = 8;
const int SendSetupBit = 9;

const int DelayVar = 100;

const int MaxRange = 0;

boolean FinalSetup = false;

// establish variables for duration of the ping, 
// and the distance result in inches and centimeters:
long duration, inches, cm, MaxDistance = 0;
int ConditionVariable = 0;
int SafetyNet = 3;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  
  while (millis() < 5000) { 
    UltraSonic();
    Serial.println(cm);
    
    if(cm > MaxDistance) {
      MaxDistance = cm;
    }
    
  }
  
  Serial.println("Cal Dis: ");
  Serial.println(MaxDistance);
  Serial.println("Setup Done");
  
}

void loop() {
    UltraSonic();
    Serial.println(cm);
    
    if(cm < (MaxDistance-SafetyNet)) {
      Serial.println("Report");
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
