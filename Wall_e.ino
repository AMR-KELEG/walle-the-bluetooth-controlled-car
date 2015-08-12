#include <NewPing.h>

//Motor a on the Right
//Motor b on the left
/*
  ----------------
  |              |
  |              |
  |              |
  |Motor   Motor |
  O  B       A   O
  ----------------
*/
/*
Bluetooth Module Wires:
Vcc >> brown
GND >> red
Tx >> orange
Rx >> yellow
*/

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 1000 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

char blueToothVal;   //value sent over via bluetooth
// PINS INIT
int E1 = 3, a1 = 2, a2 = 4, //Motor 1
    E2 = 5, b1 = 6, b2 = 7, //Motor 2
    IRBackSensor = A0, //Infrared Back Sensor
    Threshold = 400,
    lightIntensity = A4, ledIntensity = 10;// LDR-LED

int lightVal, ledVoltage, //LDR-LED
    uS, //ultrasonic
    SumRightSensor, SumCenterSensor, SumLeftSensor,
    IRBackVal; //Infrared Back Sensor
void setup()
{
 Serial.begin(9600);
 // Motors Pins 
 pinMode(E1,OUTPUT);
 pinMode(a1,OUTPUT);
 pinMode(a2,OUTPUT);
 pinMode(E2,OUTPUT);
 pinMode(b1,OUTPUT);
 pinMode(b2,OUTPUT);
 // LDR-LED
 pinMode(lightIntensity,INPUT);
 pinMode(ledIntensity, OUTPUT);
 // Infrared Back Sensor
 pinMode(IRBackSensor,INPUT);
 // Line Tracking
 pinMode(A1,INPUT);
 pinMode(A2,INPUT);
 pinMode(A3,INPUT);
 // ultrasonic
 pinMode(ECHO_PIN , INPUT);
 pinMode(TRIGGER_PIN , OUTPUT);
}

void loop()
{
  //LDR-LED
  lightVal = analogRead(lightIntensity);
  ledVoltage = convertVoltage(lightVal);
  analogWrite(ledIntensity, ledVoltage);
  Serial.print("Light: ");
  Serial.println(lightVal);
  Serial.print("LED: ");
  Serial.println(ledVoltage);


  // Avoid obstacles
  IRBackVal = analogRead(IRBackSensor);
  uS = sonar.ping_cm(); // Send ping, get ping time in microseconds (uS).
  
  if(Serial.available())
  {
    //if there is data being recieved
    blueToothVal=Serial.read();
  }

  // Line Tracking
  if(blueToothVal=='W')
  {
    while(blueToothVal!='U')
    {
      SumRightSensor = 0;
      SumCenterSensor = 0;
      SumLeftSensor = 0;
      for(int i=0;i<10;i++)
      {
        SumRightSensor += analogRead(A1);
        SumCenterSensor += analogRead(A2);
        SumLeftSensor += analogRead(A3);
      }
      int RightSensor = SumRightSensor/10;
      int CenterSensor = SumCenterSensor/10;
      int LeftSensor = SumLeftSensor/10;
      if (RightSensor - LeftSensor > Threshold)
        Right();
      else if (RightSensor - CenterSensor > Threshold)
        Right();
      else if (LeftSensor - RightSensor > Threshold)
        Left();
      else if (LeftSensor - CenterSensor > Threshold)
        Left();
      else
        Forward();
      delay(200);
      blueToothVal=Serial.read();
      Serial.println(char(Serial.read()));
   }
 }
  
  else{
  if (blueToothVal=='S')
  {
    if((uS >3 && uS < 15) && IRBackVal <= 1000)
      Right();
    else if (uS >3 && uS < 15)
      Back();
    else if (IRBackVal <= 1000 )
      Forward();
    else
      Stop();
  }
  else if (blueToothVal=='F')
  {
    //if value from bluetooth serial is Forward
    if((uS >3 && uS < 15))
    {
      Stop();
    }
    else{
    Forward();
    }
  }
  else if (blueToothVal=='B' )
  {  
    //if value from bluetooth serial is Back
    if(IRBackVal <= 1000){
     Stop();
    }
    else{
      Back();
    }
  }
  else if (blueToothVal=='R')
  {
    //if value from bluetooth serial is Right
    Right();
  }
  else if (blueToothVal=='L')
  {//if value from bluetooth serial is Left
    Left();
  }
  else if (blueToothVal=='I')
  {//if value from bluetooth serial is Forward Right
    if((uS >3 && uS < 15)){
    Stop();
    }
    else{
    ForwardRight();
    }
  }
  else if (blueToothVal=='G')
  {//if value from bluetooth serial is Forward Left
    if((uS >3 && uS < 15)){
    Stop();
    }
    else{
    ForwardLeft();
    }
  }
  else if (blueToothVal=='H')
  {//if value from bluetooth serial is Back Left
      if(IRBackVal<=1000){
        Stop();
      }
      else{
        BackLeft();
      }
  }
  else if (blueToothVal=='J')
  {//if value from bluetooth serial is Back Right
     if(IRBackVal<=1000){
        Stop();
     }
     else{
      BackRight();
     }
  } 
  }
/*
  Serial.print("Ping: ");
  Serial.print(uS); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");*/
  delay(10); 
}
  void Back(){
    digitalWrite(E1,HIGH);
    digitalWrite(a1,LOW);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,LOW);
    digitalWrite(b2,HIGH);
  }
  void Left(){
        digitalWrite(E1,HIGH);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,LOW);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,LOW);
    digitalWrite(b2,HIGH);
  }
  void Right(){
        digitalWrite(E1,HIGH);
    digitalWrite(a1,LOW);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,LOW);
  }
  void Stop(){
    digitalWrite(E1,HIGH);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,HIGH);
  }

  void Forward(){
      digitalWrite(E1,HIGH);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,LOW);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,LOW);
  }

  void ForwardRight(){
        analogWrite(E1,200);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,LOW);  
    analogWrite(E2,255);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,LOW);
  }

  void ForwardLeft(){
    analogWrite(E1,255);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,LOW);  
    analogWrite(E2,200);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,LOW);
  }

  void BackRight(){
    analogWrite(E1,200);
    digitalWrite(a1,LOW);
    digitalWrite(a2,HIGH);  
    analogWrite(E2,255);
    digitalWrite(b1,LOW);
    digitalWrite(b2,HIGH);
  }

  void BackLeft(){
    analogWrite(E1,255);
    digitalWrite(a1,LOW);
    digitalWrite(a2,HIGH);  
    analogWrite(E2,200);
    digitalWrite(b1,LOW);
    digitalWrite(b2,HIGH);
  }

//LDR-LED
int convertVoltage(int reading)
{
  int result = -0.567*reading + 396.67;
  if(result<=0){
    return 0;
  }
  else if(result>=255){
    return 255;
  }
  else{
  return result;
  }
}

