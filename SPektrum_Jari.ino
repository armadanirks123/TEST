#include <ESP32Servo.h>
Servo myservo;
int servoPin = 13;

int data1[80],data2[80],data3[80],i,pinA,pinB;
char tulis[100],pos;
void setup() {
  pinMode(12, INPUT_PULLUP);     // Initialize the LED_BUILTIN pin as an output
  pinMode(23, INPUT_PULLUP);
  Serial.begin(9600);
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 1000, 2000); // attaches the servo on pin 18 to the servo object

  ///atur sudut servo disini///
  pos=75;// atur sudut 75-180
}

// the loop function runs over and over again forever
void loop() {
  /*for(i=0;i<50;i++){
    if(digitalRead(23) == HIGH) pinA = 1;
    else {pinA=0; if(pos < 180) pos++;}
    if(digitalRead(12) == HIGH) pinB = 1;
    else {pinB=0; if(pos > 75) pos--;}
  }*/
  if(pos < 75) pos=75;
  else if(pos>180) pos=180;
  
  for(i=0;i<50;i++) {
    data1[i]=analogRead(35);
    data2[i]=analogRead(32);
    data3[i]=analogRead(33);
  }
  sprintf(tulis,"sudut: %3d:%d:%d",pos,pinA,pinB);
  Serial.println(tulis);
  Serial.println("///data///");
  for(i=0;i<50;i++){
    sprintf(tulis,"%2d: %4d,%4d,%4d",i+1,data1[i],data2[i],data3[i]);
    Serial.println(tulis);
  }
  myservo.write(pos); 
}
