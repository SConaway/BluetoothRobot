extern int LED, Trig, Echo, servoPin;
extern const byte rxPin;
#include <ReceiveOnlySoftwareSerial.h>
ReceiveOnlySoftwareSerial myserial (rxPin);

volatile int state = LOW;
char getstr;
int ABS=150;

void stateChange()
{
  state = !state;
  digitalWrite(LED, state);  
}
void setup()
{ 
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  myserial.begin(9600);
  _mStop();
}
void loop()
  { 
  getstr=myserial.read();
 if(getstr=='f')
  {
    _mForward();
  }
  else if(getstr=='b')
  {
    _mBack();
    delay(200);
  }
  else if(getstr=='l')
  {
    _mleft();
    delay(200);
  }
  else if(getstr=='r')
  {
    _mright();
    delay(200);
  }
  else if(getstr=='s')
  {
     _mStop();     
  }
  else if(getstr=='A')
  {
  stateChange();
  }
}

