#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>
#include <Stepper.h>
#include <EEPROM.h>
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);
int sudut;
/*
#define BIN2 2
#define BIN1 3
#define AIN1 4
#define AIN2 5
*/
#define LDR1 A0
#define LDR2 A1
#define LDR3 A2
#define LDR4 A3
#define limit 12
#define up    11
#define down  10

#define CLK 4
#define CW  5

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display
char data[16],Byte,dataPrint[100];
int i,DataLDR[4][100];
void setup() {
  // put your setup code here, to run once:
  // initialize the LCD
  /*pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  */
  pinMode(CLK,OUTPUT);
  pinMode(CW,OUTPUT);
  digitalWrite(CW,LOW);
  digitalWrite(CLK,LOW);
  
  pinMode(limit,INPUT);
  pinMode(up,INPUT);
  pinMode(down,INPUT);
  lcd.begin(16,2);
  Serial.begin(9600);

  // Turn on the blacklight and print a message.
  lcd.setBacklight(255);
  lcd.setCursor(0, 0);
  lcd.print("    Spektrum    ");
  lcd.setCursor(0, 1);
  lcd.print("     Sensor     ");
  delay(1000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  sprintf(data,"%-4d",analogRead(LDR1));
  lcd.print(data);
  lcd.setCursor(0, 1);
  sprintf(data,"%-4d",analogRead(LDR2));
  lcd.print(data);
  lcd.setCursor(12, 0);
  sprintf(data,"%4d",analogRead(LDR3));
  lcd.print(data);
  lcd.setCursor(12, 1);
  sprintf(data,"%4d",analogRead(LDR3));
  lcd.print(data);
  //sudut
  sudut=EEPROM.read(1);
  lcd.setCursor(7, 0);
  sprintf(data,"%-3d",sudut);
  lcd.print(data);//cek limit
  if(digitalRead(limit) == 0){
    EEPROM.write(1,0);
    sudut=0;
  }
  if(digitalRead(up) == 0 && sudut < 130){
    digitalWrite(CW,LOW);
    digitalWrite(CLK,HIGH);
    delayMicroseconds(100);
    digitalWrite(CLK,LOW);
    EEPROM.write(1,sudut+1);
    delay(500);
  }
  else if(digitalRead(down) == 0 && sudut>0 ){
    digitalWrite(CW,HIGH);
    digitalWrite(CLK,HIGH);
    delayMicroseconds(100);
    digitalWrite(CLK,LOW);
    //myStepper.step(-1);
    EEPROM.write(1,sudut-1);
    delay(500);
  }
  if (Serial.available() > 0) {
    // read the incoming byte:
    Byte = Serial.read();
    if(Byte == '1'){
      for(i=0;i<100;i++){
        DataLDR[0][i]=analogRead(LDR1);
        DataLDR[1][i]=analogRead(LDR2);
        DataLDR[2][i]=analogRead(LDR3);
        DataLDR[3][i]=analogRead(LDR4);
      }
      i=0;
      for(i=0;i<100;i++){
        sprintf(dataPrint,"%4d : %4d : %4d : %4d",DataLDR[0][i],DataLDR[1][i],DataLDR[2][i],DataLDR[3][i]);
        Serial.println(dataPrint);
      }
    }
    
  }
}
