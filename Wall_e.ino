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

// Arduino pins tied to motor 1.
#define a1 2
#define E1 3
#define a2 4
// Arduino pins tied to motor 2.
#define E2 5
#define b1 6
#define b2 7
#define LED_INTENSITY 10 // Arduino pin tied to LEDs
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define IR_BACK_SENSOR A0 // Arduino pin tied to infrared back sensor.
#define IR_RIGHT_SENSOR A1 // Arduino pin tied to infrared right sensor.
#define IR_CENTER_SENSOR A2 // Arduino pin tied to infrared center sensor.
#define IR_LEFT_SENSOR A3 // Arduino pin tied to infrared left sensor.
#define LIGHT_INTENSITY A4 // Arduino pin tied to LDR.

#define MAX_DISTANCE 600 // Maximum distance we want ultrasonic sensor to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define US_MIN 3 // Minimum value that ultrasonic sensor can read. 
#define US_THRESHOLD 15 // Maximum value that should be measured by ultrasonic sensor if the the sensor reads less than this the car stops. 
#define LINE_THRESHOLD 200 // Line tracking threshold.
#define IR_BACK_THRESHOLD 800 // Maximum value that should be measured by infrared back sensor if the the sensor reads less than this the car stops. 


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

char blueToothVal;   //value sent over via bluetooth

int lightVal, ledVal, // LDR-LED.
    uS, // ultrasonic.
    // Line tracking infrared sensors.
    SumRightSensor, SumCenterSensor, SumLeftSensor,
    RightSensor, CenterSensor, LeftSensor, 
    IRBackVal; //Infrared back sensor.
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
 pinMode(LIGHT_INTENSITY,INPUT);
 pinMode(LED_INTENSITY, OUTPUT);
 // Infrared back Sensor
 pinMode(IR_BACK_SENSOR,INPUT);
 // Line tracking
 pinMode(IR_RIGHT_SENSOR,INPUT);
 pinMode(IR_CENTER_SENSOR,INPUT);
 pinMode(IR_LEFT_SENSOR,INPUT);
 // ultrasonic
 pinMode(ECHO_PIN , INPUT);
 pinMode(TRIGGER_PIN , OUTPUT);
}

void loop()
{
  //LDR-LED
  lightVal = analogRead(LIGHT_INTENSITY); // reads light value from LDR.
  ledVal = convertVoltage(lightVal); // map LDR value to required LED value.
  analogWrite(LED_INTENSITY, ledVal); // writes led value to LEDs

  // Avoid obstacles
  IRBackVal = analogRead(IR_BACK_SENSOR); // reads value from infrared back sensor.
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
      // calculate 10 readings from each sensor and calculate the average.
      SumRightSensor = 0;
      SumCenterSensor = 0;
      SumLeftSensor = 0;
      for(int i=0;i<10;i++)
      {
        SumRightSensor += analogRead(A1);
        SumCenterSensor += analogRead(A2);
        SumLeftSensor += analogRead(A3);
      }
      RightSensor = SumRightSensor/10;
      CenterSensor = SumCenterSensor/10;
      LeftSensor = SumLeftSensor/10;
      if (RightSensor - LeftSensor > LINE_THRESHOLD)
        Right();
      else if (RightSensor - CenterSensor > LINE_THRESHOLD)
        Right();
      else if (LeftSensor - RightSensor > LINE_THRESHOLD)
        Left();
      else if (LeftSensor - CenterSensor > LINE_THRESHOLD)
        Left();
      else
        Forward();
      delay(50);
      
    blueToothVal=Serial.read();
   }
 }
  
  else{
  if (blueToothVal=='S')
  {
    
    if((uS >US_MIN && uS < US_THRESHOLD) && IRBackVal <= IR_BACK_THRESHOLD)
      Right();
    else if (uS >US_MIN && uS < US_THRESHOLD)
      Back();
    else if (IRBackVal <= IR_BACK_THRESHOLD )
      Forward();
    else
      Stop();
  }
  else if (blueToothVal=='F')
  {
    //if value from bluetooth serial is Forward
    if((uS >US_MIN && uS < US_THRESHOLD))
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
    if(IRBackVal <= IR_BACK_THRESHOLD){
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
    if((uS >US_MIN && uS < US_THRESHOLD)){
    Stop();
    }
    else{
    ForwardRight();
    }
  }
  else if (blueToothVal=='G')
  {//if value from bluetooth serial is Forward Left
    if((uS >US_MIN && uS < US_THRESHOLD)){
    Stop();
    }
    else{
    ForwardLeft();
    }
  }
  else if (blueToothVal=='H')
  {//if value from bluetooth serial is Back Left
      if(IRBackVal<=IR_BACK_THRESHOLD){
        Stop();
      }
      else{
        BackLeft();
      }
  }
  else if (blueToothVal=='J')
  {//if value from bluetooth serial is Back Right
     if(IRBackVal<=IR_BACK_THRESHOLD){
        Stop();
     }
     else{
      BackRight();
     }
  } 
  }
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
    Serial.print("recieve: ");
    Serial.println(blueToothVal);
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

