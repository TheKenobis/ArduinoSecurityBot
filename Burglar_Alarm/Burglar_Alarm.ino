const int trigPin = 2;
const int echoPin = 4;

//apple

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10,OUTPUT);
}

void loop()
{
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, cm;

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

  Serial.println(cm);
  
    if (cm < 20){
      for(int i = 0; i < 10; i++){
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    delay(1.3);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    delay(1.3);
      }
  }
  else{
   digitalWrite(9,LOW); 
  }
  
  delay(100);
}


long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

