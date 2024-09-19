int PUL=7; //define Pulse pin
int DIR=6; //define Direction pin
int ENA=5; //define Enable Pin
void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);

}

void loop() {
  for (int i=0; i<1600; i++)    //Forward 6400 steps
  {
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(200);
    digitalWrite(PUL,LOW);
    //delayMicroseconds(200);
  }
  delay(1000);
  // for (int i=0; i<200; i++)   //Backward 6400 steps
  // {m 
  //   digitalWrite(DIR,HIGH);
  //   digitalWrite(ENA,HIGH);
  //   digitalWrite(PUL,HIGH);
  //   delayMicroseconds(100);
  //   digitalWrite(PUL,LOW);
  //   delayMicroseconds(100);
  // }
}