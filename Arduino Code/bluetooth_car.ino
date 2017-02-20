extern int LED, Trig, Echo, servoPin;
extern const byte rxPin;
#include <ReceiveOnlySoftwareSerial.h>
ReceiveOnlySoftwareSerial myserial (rxPin);

volatile int state = LOW;
char getstr;
int ABS=150;
int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;
#define warningdist 25
#include <Servo.h>
Servo myservo;

int Distance_test()   
{
  int Echo = A1;  
int Trig = A0; 
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(25);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Serial.println(Fdistance); 
  Fdistance= Fdistance/58;  
      Serial.println(Fdistance); 
  return (int)Fdistance;
}  

void UA() {
      myservo.write(90);//setservo position according to scaled value
    //delay(5); 
    middleDistance = Distance_test();
    //#ifdef send
    Serial.print("middleDistance=");
    Serial.println(middleDistance);
    //#endif

    if(middleDistance<=warningdist) 
    {     
      _mStop();
      delay(500);                         
      myservo.write(5);          
      delay(1000);      
      rightDistance = Distance_test();

      //#ifdef send
      Serial.print("rightDistance=");
      Serial.println(rightDistance);
      //#endif

      delay(500);
       myservo.write(90);              
      delay(1000);                                                  
      myservo.write(180);              
      delay(1000); 
      leftDistance = Distance_test();

     // #ifdef send
      Serial.print("leftDistance=");
      Serial.println(leftDistance);
      //#endif

      delay(500);
      myservo.write(90);              
      delay(1000);
      if(rightDistance>leftDistance)  
      {
        _mright();
        delay(360);
       }
       else if(rightDistance<leftDistance)
       {
        _mleft();
        delay(360);
       }
       else if((rightDistance<=warningdist)||(leftDistance<=warningdist))
       {
        _mBack();
        delay(180);
       }
       else
       {
        _mForward();
       }
    }  
    else
        _mForward();                     
}


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
  myservo.attach(servoPin);
  _mStop();
}
void loop()
  { 
  getstr=myserial.read();
getstr='o';
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
    else if(getstr=='o')
  {
     UA();     
  }
  else if(getstr=='A')
  {
  stateChange();
  }
}

