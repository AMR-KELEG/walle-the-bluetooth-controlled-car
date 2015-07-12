char blueToothVal;   
//value sent over via bluetooth
//Motor a on the Right
//Motor b on the left
int E1=2,a1=3,a2=4,E2=7,b1=6,b2=8;
void setup()
{
 Serial.begin(9600); 
 pinMode(E1,OUTPUT);
 pinMode(a1,OUTPUT);
 pinMode(a2,OUTPUT);
}
 
 
void loop()
{
  if(Serial.available())
  Serial.println(char(Serial.read()));
  
  if(Serial.available())
  {//if there is data being recieved
    blueToothVal=Serial.read(); //read it
  }
  if (blueToothVal=='F')
  {//if value from bluetooth serial is Forward
    digitalWrite(E1,HIGH);
    analogWrite(a1,255);
    digitalWrite(a2,LOW);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,255);
    digitalWrite(b2,LOW);
  }
  else if (blueToothVal=='B')
  {//if value from bluetooth serial is Back
    digitalWrite(E1,HIGH);
    analogWrite(a1,0);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,0);
    digitalWrite(b2,HIGH);
  }
  else if (blueToothVal=='L')
  {//if value from bluetooth serial is Left
    digitalWrite(E1,HIGH);
    analogWrite(a1,0);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,255);
    digitalWrite(b2,LOW);
  }
  else if (blueToothVal=='R')
  {//if value from bluetooth serial is Right
    digitalWrite(E1,HIGH);
    analogWrite(a1,255);
    digitalWrite(a2,LOW);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,0);
    digitalWrite(b2,HIGH);
  }
  else if (blueToothVal=='I')
  {//if value from bluetooth serial is Forward Right
    digitalWrite(E1,HIGH);
    analogWrite(a1,200);
    digitalWrite(a2,LOW);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,255);
    digitalWrite(b2,LOW);
  }
  else if (blueToothVal=='G')
  {//if value from bluetooth serial is Forward Left
    digitalWrite(E1,HIGH);
    analogWrite(a1,255);
    digitalWrite(a2,LOW);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,200);
    digitalWrite(b2,LOW);
  }
  else if (blueToothVal=='H')
  {//if value from bluetooth serial is Back Left
    digitalWrite(E1,HIGH);
    analogWrite(a1,0);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,50);
    digitalWrite(b2,HIGH);
  }
  else if (blueToothVal=='J')
  {//if value from bluetooth serial is Back Right
    digitalWrite(E1,HIGH);
    analogWrite(a1,50);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,0);
    digitalWrite(b2,HIGH);
  }
    else
    {
      digitalWrite(E1,HIGH);
    analogWrite(a1,255);
    digitalWrite(a2,HIGH);  
    digitalWrite(E2,HIGH);
    analogWrite(b1,255);
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
  delay(5); 
}
