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
  
  for(int i=8; i<11; i++) {
     pinMode(i, OUTPUT);
     digitalWrite(i, LOW);
  }
  
  digitalWrite(8, HIGH);
  
  /*while(FinalSetup == false) {
    if(Serial.available() > 0) {
      int IncomingByte = Serial.read()-'0';
    
      if(IncomingByte != RecieveSetupBit) {
        Serial.print(SendSetupBit);
      
      } else {
        FinalSetup = true;
      
      } 
      
    } else if(Serial.available() <= 0) {
      Serial.println("ERROR..............");
    
    }
    
    delay(DelayVar);
    Serial.flush();
  }*/
  
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  
  while (millis() < 5000) { 
    UltraSonic();
    Serial.println(cm);
    
    if(cm > MaxDistance) {
      MaxDistance = cm;
    }
    
  }
  
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
 
  Serial.println("Cal Dis: ");
  Serial.println(MaxDistance);
  Serial.p
