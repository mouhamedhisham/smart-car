#define speedLeft 11 // enA
#define In1 9
#define In2 8
#define In3 7
#define In4 6
#define speedRight 5 //enB
#define flame 2
#define trig 4
#define echo 10
long duration, distance;
char reading;
#define buzzer 13
int Val = 0;

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MQ2pin A1
int sensorValue = 0;

#define ldr A2
#define led A0
#define led2 A3
int threshold = 60;
int level ;


void setup() {
  Serial.begin(9600);
  for (int i = 5;
       i <= 10; i++)
    pinMode(i, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(flame , INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
   lcd.init();
  lcd.backlight();
  //analogWrite(led2, 255);
}

void forward()
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(speedLeft, 200);
  analogWrite(speedRight, 182);
}

void backward()
{
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH);
  digitalWrite(In3, LOW);
  digitalWrite(In4, HIGH);
  analogWrite(speedLeft, 200);
  analogWrite(speedRight, 182);
}

void left()
{
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, HIGH);
  digitalWrite(In4, LOW);
  analogWrite(speedLeft, 0);
  analogWrite(speedRight, 200);
}

void right()
{
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
  analogWrite(speedLeft, 200);
  analogWrite(speedRight, 0);
}

void stopp()
{
  analogWrite(speedLeft, 0);
  analogWrite(speedRight, 0);
}

void loop() {

  if (Serial.available() > 0)
  {
    reading = Serial.read();

    switch (reading)
    {
      case 'F':
        forward();
        break;
      case 'B':
        backward();
        break;
      case 'R':
        right();
        break;
      case 'L':
        left();
        break;
      case 'S':
        stopp();
        break;
      case 'V':
        digitalWrite(buzzer, HIGH);
        delay(100);
        break;
      case 'v':
        digitalWrite(buzzer, LOW);
        break;
    }
  }
  Val = digitalRead(flame);
  if (Val == LOW) {
    lcd.print("Fire detected");
    lcd.setCursor(0,0);
    digitalWrite(buzzer, HIGH);
    delay(10);
    
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("NO Fire detected");
    digitalWrite(buzzer, LOW);
  }
  sensorValue = analogRead(MQ2pin);
  if (sensorValue > 300) {
    digitalWrite(buzzer, HIGH); 
  }
  else {
    digitalWrite(buzzer, LOW);
  }
  level = analogRead(ldr);
  if (level < threshold) {
    analogWrite(led, 255);
  }
  else {
    analogWrite(led, 0);
  }

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) * 0.0343; 
  //Serial.println(distance);
  delay(5); // wait till next scan

 if( distance < 30 && distance >0)
  {
      analogWrite(led2, 240);
     
  }
  else {
     analogWrite(led2, 0);
     
  }
  
    

}
