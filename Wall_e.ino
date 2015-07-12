/************************
Exercise the motor using
the L293 chip
************************/

#define ENABLE 3
#define DIRB 4
#define DIRA 5

void setup() {
  int i;

  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);

  //---back and forth example
/*
  digitalWrite(ENABLE,HIGH); // enable on
  for (i=0;i<5;i++) {
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
    delay(500);
    digitalWrite(DIRA,LOW);  //reverse
    digitalWrite(DIRB,HIGH);
    delay(500);
  }
  digitalWrite(ENABLE,LOW); // disable
  delay(4000);

  //---fast/slow stop example
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(1000);
  digitalWrite(ENABLE,LOW); //slow stop
  delay(3000);
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(1000);
  digitalWrite(DIRA,LOW); //fast stop
  delay(3000);
*/
  //---PWM example, full speed then slow
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(10000);
  digitalWrite(ENABLE,LOW); //all done
}

void loop() {
}
