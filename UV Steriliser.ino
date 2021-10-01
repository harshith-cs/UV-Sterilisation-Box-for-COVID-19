#include <SoftwareSerial.h>
SoftwareSerial BTserial(0, 1); // RX | TX
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int in;
unsigned long starttime;
unsigned long endtime;
unsigned long st;
unsigned long et;
int loopcount = 0;
String pstate;
String dstate;
int sec;
int IR = 5;
int out1 = 6;
int out2 = 7;
void printing(){
  

  delay(3000);
    
}
int checkTemp1(){
  int temp1;
  int r;
  sensors.requestTemperatures(); 
  temp1=(int)sensors.getTempCByIndex(0);
  if(temp1<60){
     r=temp1;
  }
  return r;
}
int checkTemp2(){
  int temp2;
  int r;
  sensors.requestTemperatures(); 
  temp2 = (int)sensors.getTempCByIndex(1);
  if(temp2<60){
    r=temp2;
  }
  return r;
}
int checkDoor(){
  int dval;
  int r=0;
  dval = digitalRead(IR);
  if(dval==0){
    r=0;
  }
  else{
    r=1;
  }
  return r;
}

void setup() {
  BTserial.begin(9600);
  Serial.begin(9600);
  sensors.begin();
  pinMode(IR, INPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);

}

void loop() {
 pstate = "The device is OFF";
  if(checkDoor() == 0){
    dstate="Door is CLOSED";
  }
  else{
    dstate="Door is OPEN";
  }

  if (Serial.available() > 0)
  {
    in = Serial.read();            
    sec = in * 1000;
    starttime = millis();
    endtime = starttime;
    while ((endtime - starttime) <= sec) 
    {
      if(checkTemp1()<60 && checkTemp2()< 80 && checkDoor()==0)
      {
        digitalWrite(out2, HIGH);
        int t1=checkTemp1();
        int t2=checkTemp2();
        Serial.print(t1);
        Serial.print("C");
        Serial.print("|");
        Serial.print(t2); 
        Serial.print("C");
        Serial.print("|");
        Serial.print(pstate);
        Serial.print("|");
        Serial.println(dstate);
        loopcount = loopcount + 1;
        endtime = millis();
        pstate = "The device is ON";
      }
     else
     {
      digitalWrite(out1, LOW);
      digitalWrite(out2, LOW);
      pstate = "The device is OFF";
      break;
     }
    }
    digitalWrite(out1, LOW);
    digitalWrite(out2, LOW);
    pstate = "The device is OFF";
  }
  int t1=checkTemp1();
  int t2=checkTemp2();
  Serial.print(t1);
  Serial.print("C");
  Serial.print("|");
  Serial.print(t2); 
  Serial.print("C");
  Serial.print("|");
  Serial.print(pstate);
  Serial.print("|");
  Serial.println(dstate);
  delay(1000);
}
