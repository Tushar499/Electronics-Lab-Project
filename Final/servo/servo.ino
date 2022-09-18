#include<Servo.h>
Servo s;
int x=31; //digital pin 2 has a push button attached to it. Give it an name

//the setup routine runs once when you press reset
void setup() {

  //IR START
   pinMode(35,INPUT);
  pinMode(42,OUTPUT);
  pinMode(26,OUTPUT);
  //IR END

  Serial.begin(9600); //initialize serial comm. at 9600 bits per second

  pinMode(31, INPUT);//make the push button's pin an input
  s.attach(33);
  s.write(0);
  //pinMode(42,OUTPUT);
}

//the loop routine runs over and over again forever
void loop() {
  //IR START
  if(digitalRead(35)==0){
    digitalWrite(26,LOW);
     digitalWrite(42,HIGH);
  }
  if(digitalRead(35)==1){
     digitalWrite(26,HIGH);
    digitalWrite(42,LOW);
  } 
  //IR END

  int buttonState = digitalRead(x); //read the input pin

  Serial.println(buttonState); //print out the state of the button

  delay(1000); //delay in between reads for stability
  if(buttonState!=0){
    s.write(0);
    delay(5000);
   // digitalWrite(4,HIGH);
    }
    
    else{
      s.write(180);
     // digitalWrite(4,LOW);
      }
}
