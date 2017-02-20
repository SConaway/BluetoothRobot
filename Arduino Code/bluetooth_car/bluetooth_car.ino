extern int LED, Trig, Echo, servoPin;
extern const byte rxPin;
#include <ReceiveOnlySoftwareSerial.h>
ReceiveOnlySoftwareSerial myserial (rxPin);

volatile int state = LOW;
char getstr;

int ABS=150;

#include <Servo.h>
Servo myservo;
int forangle = 94;
int leftangle = 170;
int rightangle = 15;


#include <NewPing.h>
#define warningdist 25
NewPing sonar(15, 14, 200);
long middleDistance, rightDistance, leftDistance;

void UA() {
    myservo.write(forangle);//set servo position according to scaled value 
    middleDistance = sonar.ping_cm();
    #ifdef send
    Serial.print("middleDistance=");
    Serial.println(middleDistance);
    #endif

    if(middleDistance<=warningdist)  {
      _mStop();
      delay(50);                         
      myservo.write(rightangle);          
      delay(100);      
      rightDistance = sonar.ping_cm();

      #ifdef send
      Serial.print("rightDistance=");
      Serial.println(rightDistance);
      #endif

      delay(50);
       myservo.write(forangle);              
      delay(100);                                                  
      myservo.write(leftangle);              
      delay(100); 
      leftDistance = sonar.ping_cm();

     #ifdef send
      Serial.print("leftDistance=");
      Serial.println(leftDistance);
      #endif

      delay(50);
      myservo.write(forangle);              
      delay(100);
      if(rightDistance>leftDistance)  {
          _mright();
          delay(50);
        }
      else if(rightDistance<leftDistance){
            _mleft();
            delay(50);
       }
      else if((rightDistance<=warningdist)||(leftDistance<=warningdist)){
            _mBack();
            delay(50);
       }
       else{
           _mForward();
       }
    }  
    else
        _mForward();                     
}


void stateChange()  {
  state = !state;
  digitalWrite(LED, state);  
}
void setup()  { 
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  myserial.begin(9600);
  myservo.attach(servoPin);
  _mStop();
}
void loop()  { 
  getstr=myserial.read();

  if(getstr=='f')  {
    _mForward();
    delay(100);
  }
  else if(getstr=='b')  {
    _mBack();
    delay(100);
  }
  else if(getstr=='l')  {
    _mleft();
    delay(100);
  }
  else if(getstr=='r')  {
    _mright();
    delay(100);
  }
  else if(getstr=='s')  {
     _mStop();     
  }
  else if(getstr=='o')  {
     UA();    
  }
  else if(getstr=='A')  {
    stateChange();
  }
}


