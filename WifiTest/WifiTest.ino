#include <SoftwareSerial.h>
#include<MsTimer2.h>
#include <AFMotor.h>

#define led 2 
#define WIFT_TX 0
#define WIFI_RX 1

const int TrigPin = 9; 
const int EchoPin = 10; 

boolean  isturn; 
SoftwareSerial wifi(WIFI_RX, WIFT_TX);   //RX, TX
float cm;
char inByte;
int speedint=255;

AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
AF_DCMotor motor4(4, MOTOR12_64KHZ);

void flash(){  //定时中断函数
  //发一个10ms的高脉冲去触发TrigPin 
digitalWrite(TrigPin, LOW); 
delayMicroseconds(2); 
digitalWrite(TrigPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(TrigPin, LOW); 
cm = pulseIn(EchoPin, HIGH) / 58.0; //算成厘米 
cm = (int(cm * 100.0)) / 100.0; //保留两位小数 
  }

void speed(int speedint){
   motor1.setSpeed(speedint);
   motor2.setSpeed(speedint-5);
   motor3.setSpeed(speedint);
   motor4.setSpeed(speedint-5);
  }
void forward(){
   motor1.run(FORWARD);
   motor2.run(FORWARD);
   motor3.run(FORWARD);
   motor4.run(FORWARD);
  } 
  void backward(){
     motor1.run(BACKWARD);
     motor2.run(BACKWARD);
     motor3.run(BACKWARD);
     motor4.run(BACKWARD);
    }
    void turnRight(){
     motor2.run(RELEASE);
     if(isturn){
     motor1.run(FORWARD);
     motor3.run(FORWARD);
     }else{
       motor1.run(BACKWARD);
     motor3.run(BACKWARD);
      }
     motor4.run(RELEASE);
    }
     void turnLeft(){
     motor1.run(RELEASE);
     motor3.run(RELEASE);
      if(isturn){
     motor2.run(FORWARD);
     motor4.run(FORWARD);
     }else{
      motor2.run(BACKWARD);
     motor4.run(BACKWARD);
      }
    }
     void stop(){
     motor1.run(RELEASE);
     motor2.run(RELEASE);
      motor4.run(RELEASE);
      motor3.run(RELEASE);
    }
void setup()
{
    Serial.begin(115200);  
     wifi.begin(115200);
   pinMode(TrigPin, OUTPUT); 
     pinMode(EchoPin, INPUT); 
    pinMode(led,OUTPUT);
    digitalWrite(led,LOW);
    MsTimer2::set(100,flash); // 中断设置函数，每 100ms 进入一次中断
  MsTimer2::start();    //开始计时
    speed(speedint);
}

void loop()
{

if(Serial.available())
{
inByte = char(Serial.read());//读取
if(inByte=='1'){
 digitalWrite(led, HIGH); 
   delay(100);
   forward();
    isturn=true;
 digitalWrite(led, LOW);
}
if(inByte=='2'){
  digitalWrite(led, HIGH);
   delay(100);
  backward();
  isturn=false;
   digitalWrite(led, LOW);
}
if(inByte=='3'){
   digitalWrite(led, HIGH);
   delay(100);
  turnLeft();
  delay(1000);
  if(isturn){
   forward();
  }else {
  backward();
  }
     
   digitalWrite(led, LOW);
}
if(inByte=='4'){
 delay(100);
   digitalWrite(led, HIGH);
  turnRight(); 
    delay(1000);
       forward();
     if(isturn){
   forward();
  }else {
  backward();
  }
 digitalWrite(led, LOW);
}
if(inByte=='5'){
 digitalWrite(led, HIGH);
  delay(100);
 stop(); 
  digitalWrite(led, LOW);
}
if(inByte=='6'){
 digitalWrite(led, HIGH);
  delay(100);
  if(speedint>=100){
    speedint-=20;
     if(speedint<100)
     speedint=100;
   speed(speedint); 
  digitalWrite(led, LOW);
  }
}
if(inByte=='7'){
  digitalWrite(led, HIGH);
  delay(100);
  if(speedint<=255){
    speedint+=20;
   if(speedint>255)
     speedint=255;
    speed(speedint); 
  digitalWrite(led, LOW);
}
}
} 
  if(cm<=5){
    stop();
    } 
}



