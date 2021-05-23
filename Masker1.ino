/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
int data[80],i;
char tulis[100];
void setup() {
  //pinMode(A0, INPUT);     // Initialize the LED_BUILTIN pin as an output
  //pinMode(D3, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  for(i=0;i<50;i++) data[i]=analogRead(A0);
  Serial.println("///data///");
  for(i=0;i<50;i++){
    //sprintf(tulis,"%4d %4d %4d %4d %4d %4d %4d %4d %4d %4d",data[i],data[i+1],data[i+2],data[i+3],data[i+4],data[i+5],data[i+6],data[i+7],data[i+8],data[i+9]);
    sprintf(tulis,"%2d: %4d",i+1,data[i]);
    Serial.println(tulis);
  }
}
