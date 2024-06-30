void initializeLEDs() {
        
        for (int i = 0; i < 8; i++) {
            leds.set(i, GREEN, 10);
        }
        delay(500);
        for (int i = 0; i < 8; i++) {
            leds.set(i, RED, 10);
            buzzer.tone(100 * i, 100);
            leds.show();
            delay(500);
        }     

    }

void updateLEDs() {
        for (int i = 0; i < 8; i++) {
            if (LedBrigh[i] == -1) {
                leds.set(i, RED, 10);
                defeat = false;
            } else {
                leds.set(i, GREEN, LedBrigh[i]);
                defeat = true;
            }
            leds.show();
        }
}

void matchLed (int value) {
     LedBrigh[led] = value;
      buzzer.tone(700, 200);
      delay(200);
      buzzer.tone(440, 200);
      delay(200);
      newLed = (led + 1) % 8;
      leds.set(newLed, BLUE, 10);
      leds.clear(led);
      leds.show();
      count = 0;
      led = newLed;
      delay(500);
}

void WinLEDs() {
        
        for (int i = 0; i < 8; i++) {
            leds.set(i, BLUE, 0);
            leds.show();
            buzzer.tone(200 + LedWinns[i], 100);
            delay(500);
        }
    }

void LooseLeds() {
        
        for (int i = 0; i < 8; i++) {
            leds.set(i, VIOLET, 100);
            leds.show();
            buzzer.tone(200 + (100-LedWinns[i]) , 100);
            delay(500);
        }
    }



void matchLetter() {

      buzzer.tone(700, 200);
      delay(200);
      buzzer.tone(440, 200);
      delay(200);

}

void wrongPassword () {
      buzzer.tone(700, 200);
      delay(200);
      buzzer.tone(440, 200);
      delay(200);
      buzzer.tone(200, 200);
      delay(200);
      buzzer.tone(150, 200);
      delay(200);
}