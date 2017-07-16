#include <SoftwareSerial.h>
#include<MsTimer2.h>


#define led 14
#define WIFT_TX 0
#define WIFI_RX 1

const int TrigPin = 9;
const int EchoPin = 10;
boolean  ison;
SoftwareSerial wifi(WIFI_RX, WIFT_TX);   //RX, TX
float cm;
char inByte;
int speedint = 255;

void Onlight(int var) {
  if (ison) {
    digitalWrite(var, LOW );
    digitalWrite(led, HIGH);
    // digitalWrite(light,LOW);
    ison = false;
  } else {
    digitalWrite(var, HIGH );
    digitalWrite(led, LOW);
    ison = true;
  }
}


void flash()
{ //定时中断函数
  //发一个10ms的高脉冲去触发TrigPin
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58.0; //算成厘米
  cm = (int(cm * 100.0)) / 100.0; //保留两位小数
}
void setup()
{
  Serial.begin(115200);
  wifi.begin(115200);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  for (int i = 2; i < 25 ; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  MsTimer2::set(100, flash); // 中断设置函数，每 100ms 进入一次中断
  MsTimer2::start();    //开始计时
}

void loop()
{

  if (Serial.available())
  {
    inByte = char(Serial.read());//读取
    if (inByte == '1') {
      Onlight(8);
    }
    if (inByte == '2') {
      Onlight(2);
    }
    if (inByte == '3') {
      Onlight(3);
    }
    if (inByte == '4') {
      Onlight(4);
    }
    if (inByte == '5') {
      Onlight(5);
    }
    if (inByte == '6') {
      Onlight(6);
    }
    if (inByte == '7') {
      Onlight(7);
    }
    if (inByte == '8') {
      Onlight(11);
    }
    if (inByte == '9') {
      Onlight(12);
    }
  }
}



