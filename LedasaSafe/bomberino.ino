#include <Scheduler.h>
#include <Servo.h>
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "right.h"
#include "left.h"
#include "MatrixTimer.h"
#include "Modulino.h"





ArduinoLEDMatrix matrix;
ModulinoKnob encoder;
ModulinoPixels leds;
ModulinoBuzzer buzzer;
ModulinoButtons buttons;
Servo myservo;

int timer = 99;
int led = 0;
int count = 0;
int newLed = 0;
int servoPos = 0;
int ServoPWMPin = 9;

bool defeat = false;
bool password = false;
bool boom = false;
bool openSafe = false;

int LedBrigh[8]= {-1,-1,-1,-1,-1,-1,-1,-1};
//int LedBrigh[8]={12,0,11,21,5,16,22,1};
//int LedSucc[8]= {25,37,10,25,15,3,33,12};
int LedSucc[8]= {12,0,12,22,5,13,25,1};
int LedWinns[8]= {100,90,80,70,40,50,30,20};

char code[] = {"ABBCCA"};
char passkey[] ={"XXXXXX"};
int nextLetter = 0;




void setup() {

  Modulino.begin();
  encoder.begin();
  leds.begin();
  buzzer.begin();
  buttons.begin();

  myservo.attach(ServoPWMPin);

  Serial.begin(115200);
  //Initialize Led Matrix
  matrix.begin();
  //Init LEDs Modulino
  initializeLEDs();
  // Start the timer task
  Scheduler.startLoop(Countdown_99);
  //Close the door
  myservo.write(0);   




}

void loop() {
  if (!boom){
    updateLEDs();
  }

  int value = encoder.get() % 100;

  if (value < 0) {
    encoder.set(0);
  }
  Serial.println(value);
  if (value == LedSucc[led]){
      matchLed(value);
  } else if (value < LedSucc[led]+10 && value > LedSucc[led]-10) {
      buzzer.tone(100+value, 100);
  }
  leds.show();

  if (defeat && password) {
    yield();               // Trigger YOU WIN!
    WinLEDs();
    OpenLock();
    delay(7000);   
   
  }
  
  if (defeat == true && password == false && boom == false ){
    if (buttons.update()) {
      if (buttons.isPressed(0)) {
        passkey[nextLetter] = 'A';
        nextLetter++;
      }
      if (buttons.isPressed(1)) {
        passkey[nextLetter] = 'B';
        nextLetter++;      

      } 
      if (buttons.isPressed(2)) {
          passkey[nextLetter] = 'C'; 
          nextLetter++;     
      }
      if (nextLetter>5 && !(String(passkey)==String(code))){
        nextLetter = 0;
        wrongPassword();
        for (int n=0; n<6; n++){
           passkey[n] = 'X'; 
        }

      }     
    }
    if (encoder.isPressed()){
        //  Serial.println("presse");
        //  for (int n=0; n<6; n++){
        //    passkey[n] = 'X'; 
        //  }
    }
  
  }

  if (String(passkey)==String(code)){
      password = true;
  }

  

  Serial.println(passkey);

  yield();

}

