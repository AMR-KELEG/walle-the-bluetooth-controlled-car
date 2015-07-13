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
char blueToothVal;   //value sent over via bluetooth
int E1=3,a1=2,a2=4,E2=5,b1=6,b2=7;
void setup()
{
 Serial.begin(9600); 
 pinMode(E1,OUTPUT);
 pinMode(a1,OUTPUT);
 pinMode(a2,OUTPUT);
 pinMode(E2,OUTPUT);
 pinMode(b1,OUTPUT);
 pinMode(b2,OUTPUT);
}
 
 
void loop()
{
  
  if(Serial.available())
  {//if there is data being recieved
    Serial.println(char(Serial.read()));
    blueToothVal=Serial.read(); //read it
  }
  
  if (blueToothVal=='F')
  {//if value from bluetooth serial is Forward
    digitalWrite(E1,HIGH);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,LOW);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,LOW);
  }
  else if (blueToothVal=='B')
  {//if value from bluetooth serial is Back
    digitalWrite(E1,HIGH);
    digitalWrite(a1,LOW);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,LOW);
    digitalWrite(b2,HIGH);
  }
  else if (blueToothVal=='R')
  {//if value from bluetooth serial is Right
    digitalWrite(E1,HIGH);
    digitalWrite(a1,LOW);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,LOW);
  }
  else if (blueToothVal=='L')
  {//if value from bluetooth serial is Left
    digitalWrite(E1,HIGH);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,LOW);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,LOW);
    digitalWrite(b2,HIGH);
  }
  else if (blueToothVal=='I')
  {//if value from bluetooth serial is Forward Right
    analogWrite(E1,200);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,LOW);  
    analogWrite(E2,255);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,LOW);
  }
  else if (blueToothVal=='G')
  {//if value from bluetooth serial is Forward Left
    analogWrite(E1,255);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,LOW);  
    analogWrite(E2,200);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,LOW);
  }
  else if (blueToothVal=='H')
  {//if value from bluetooth serial is Back Left
    analogWrite(E1,255);
    digitalWrite(a1,LOW);
    digitalWrite(a2,HIGH);  
    analogWrite(E2,200);
    digitalWrite(b1,LOW);
    digitalWrite(b2,HIGH);
  }
  else if (blueToothVal=='J')
  {//if value from bluetooth serial is Back Right
    analogWrite(E1,200);
    digitalWrite(a1,LOW);
    digitalWrite(a2,HIGH);  
    analogWrite(E2,255);
    digitalWrite(b1,LOW);
    digitalWrite(b2,HIGH);
  }
  else if (blueToothVal=='S')
  {
    digitalWrite(E1,HIGH);
    digitalWrite(a1,HIGH);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    digitalWrite(b1,HIGH);
    digitalWrite(b2,HIGH);
  }
     
 /* else if (blueToothVal=='B')
  {//if value from bluetooth serial is n
    digitalWrite(13,LOW);             //turn off LED
    if (lastValue!='F')
      Serial.println(F("LED is off")); //print LED is on
    lastValue=blueToothVal;
  }
 */
  delay(10); 
}
