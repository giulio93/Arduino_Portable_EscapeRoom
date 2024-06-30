void OpenLock(){
    for (;servoPos<= 180 ; servoPos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(servoPos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position

  }
}