const uint32_t questionmark[] = {
		0x79e49269,
		0xa08230c2,
		0x8000208
	};

void Countdown_99() {

  //Setup frame
  uint32_t frame[3] = {0x0, 0x0, 0x0};

  setNumber(timer,frame);
  matrix.loadFrame(frame);
  delay(1000);
  timer = timer -1;

  if (timer < 1) {
    boom = true;
    LooseLeds();
    matrix.beginDraw();

    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(75);

    // add the text
    const char text[] = "BBBBBOOOOM YOU LOOOOSE!";
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(text);
    matrix.endText(SCROLL_LEFT);

    matrix.endDraw();
    delay(5000);
  }
  if (defeat == true && password == false){

      // Make it scroll!
    matrix.beginDraw();

    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(25);

    // add the text
    const char text[] = "PASSWORD PLEASE!!";
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(text);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
    matrix.loadFrame(questionmark);
    delay(500);
    yield();

  }
  if (defeat == true && password == true){

      // Make it scroll!
    matrix.beginDraw();

    matrix.stroke(0xFFFFFFFF);
    matrix.textScrollSpeed(75);

    // add the text
    const char text[] = "YOU WIN!";
    matrix.textFont(Font_5x7);
    matrix.beginText(0, 1, 0xFFFFFF);
    matrix.println(text);
    matrix.endText(SCROLL_LEFT);
    matrix.endDraw();
    delay(5000);

  }  
}


