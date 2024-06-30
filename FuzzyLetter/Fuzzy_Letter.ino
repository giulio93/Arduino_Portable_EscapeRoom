// To use ArduinoGraphics APIs, please include BEFORE Arduino_LED_Matrix
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"
#include "letters.h"

ArduinoLEDMatrix matrix;
int GroundTwo = 2;
int analogPin = 0;
int GroundThree = 3;
int analogPinOne = 1;
int val = 0;
int valOne = 0;

uint32_t mask[3] = {0x0, 0x0, 0x0};
uint32_t frame[3] = {0x0, 0x0, 0x0};
char code[] = {"ABBCCA00"};

int first2digits = 0;
int second2digits = 0;
int third2digits = 0;



void setup() {
  Serial.begin(115200);
  matrix.begin();

  // make the pushbutton's pin an input:
  pinMode(GroundTwo, OUTPUT);
  pinMode(GroundThree, OUTPUT);

  randomSeed(analogRead(analogPin));

  //Initialize the sequence
  // 0 1 2 A B C right Matrix
  // 3 4 5 A B C left Matrix
  first2digits = 23;
  second2digits = 13;
  third2digits = 25;


}

void loop() {

  //Set 2 to GROUND
  digitalWrite(GroundTwo,LOW);
  digitalWrite(GroundThree,LOW);

  // val = analogRead(analogPin);  
  // valOne = analogRead(analogPinOne);

  
  
  for (int k=0; k<8;){
    
    
    val = analogRead(analogPin);
    valOne = analogRead(analogPinOne); 
    if (val < 50 ){
      val = 0;
    }
    if (valOne < 50){
      valOne = 0;
    }

    Mask(valOne*val*27584930445, mask);
    setMask(&code[k], &code[k+1],frame,mask);
    k = k+2;
    matrix.loadFrame(frame);
    delay(2000%val%valOne);
    //Serial.println(k);

  } 

}

void mergeMask(const uint32_t *leftN, const uint32_t *rightN,uint32_t *frame, uint32_t *mask){
  frame[0] = leftN[0] | mask[0] | rightN[0];
  frame[1] = leftN[1] | mask[1] | rightN[1];
  frame[2] = leftN[2] | mask[2] | rightN[2];

}


void setMask(char* left,char* right,uint32_t* frame,uint32_t* mask){
  
  int i = 0;
  int j = 0;
  switch (*left){
    case 'A':
      i = 0; break;
    case 'B':
      i = 1; break;
    case 'C':
      i = 2; break;
    case '0':
      i = 6; break;

  }
    switch (*right){
    case 'A':
      j = 3; break;
    case 'B':
      j = 4; break;
    case 'C':
      j = 5; break;
    case '0':
      j = 7; break;
  }

  mergeMask(letters[i], letters[j],frame, mask);

}


// Function to split the integer into three 32-bit unsigned integers
void Mask(int value, uint32_t array[3]) {
  // Mask and shift to split the integer
  array[0] = (uint32_t)(value & 0xFFFFFFFF);        // Lower 32 bits
  array[1] = (uint32_t)((value >> 32) & 0xFFFFFFFF); // Middle 32 bits
  array[2] = (uint32_t)((value >> 64) & 0xFFFFFFFF); // Upper 32 bits (if necessary)
}


