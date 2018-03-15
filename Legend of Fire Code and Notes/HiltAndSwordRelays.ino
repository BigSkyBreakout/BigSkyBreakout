// Based Off Of: http://www.instructables.com/id/ARDUINO-Burglar-Alarm-Using-Infrared-Emitter-Detec/
// Set 0 (for the flasks of opaque liquid)
int detect0 = 8;
int sense0 = A0; //analog

// Set 1 (for the flasks of opaque liquid)
int detect1 = 9;
int sense1 = A1; //analog

// Set 2 (for the flasks of opaque liquid)
int detect2 = 10;
int sense2 = A2; //analog
 
// Set 3 (for sword)
int detect3 = 11;
int sense3 = A3; //analog

// Relays
int hiltRelay = 7;
int swordRelay = 6;

// Reset button
int resetButton = 5;
int buttonState;
bool needsToBeReset = false;

// speaker
int speakerPin = 2;
bool playing = false;

// button to turn everything on or off
int powerButton = 4;
int powerButtonState;

// MUSIC
char notes[] = "gabygabyxzCDxzCDabywabywzCDEzCDEbywFCDEqywFGDEqi        azbC"; // a space represents a rest
int length = sizeof(notes); // the number of notes
int beats[] = { 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1, 2,3,3,16,};
int tempo = 75;

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'x', 'a', 'z', 'b', 'C', 'y', 'D', 'w', 'E', 'F', 'q', 'G', 'i' };
  // c=C4, C = C5. These values have been tuned.
  int tones[] = { 1898, 1690, 1500, 1420, 1265, 1194, 1126, 1063, 1001, 947, 893, 843, 795, 749, 710, 668, 630, 594 };
  // play the tone corresponding to the note name
  for (int i = 0; i < 18; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(hiltRelay, OUTPUT);
  pinMode(swordRelay, OUTPUT);
  digitalWrite(hiltRelay, LOW);
  digitalWrite(swordRelay, LOW);
  // Set 0
  pinMode(detect0,OUTPUT);
  pinMode(sense0,INPUT);
  digitalWrite(detect0,HIGH);
  // Set 1
  pinMode(detect1,OUTPUT);
  pinMode(sense1,INPUT);
  digitalWrite(detect1,HIGH);
  // Set 2
  pinMode(detect2,OUTPUT);
  pinMode(sense2,INPUT);
  digitalWrite(detect2,HIGH);
  // Set 3
  pinMode(detect3,OUTPUT);
  pinMode(sense3,INPUT);
  digitalWrite(detect3,HIGH);
  Serial.begin(9600);
}

void loop() {
  // set0
  int valueSet0=analogRead(sense0);
  // set1
  int valueSet1=analogRead(sense1);
  // set2
  int valueSet2=analogRead(sense2);
  // set3
  int valueSet3=analogRead(sense3);
  // power off everything. In order to turn it back on just hit reset button
  powerButtonState = digitalRead(powerButton);
  if (powerButtonState == HIGH) {
    digitalWrite(detect0, LOW);
    digitalWrite(detect1, LOW);
    digitalWrite(detect2, LOW);
    digitalWrite(detect3, LOW);
    digitalWrite(hiltRelay, LOW);
    digitalWrite(swordRelay, LOW);
  }
  //reset button code
  buttonState = digitalRead(resetButton);
  if (buttonState == HIGH) {
    if(needsToBeReset == true){
      needsToBeReset = false;
      digitalWrite(hiltRelay, LOW);
      digitalWrite(swordRelay, LOW);
      playing = false;
    }
  }
  // ALL THREE LIQUIDS ABOVE 945
  if(valueSet0>=945 and valueSet1>=945 and valueSet2>=945){
    Serial.println("1 and 2 and 3 (liquids done)");
    digitalWrite(hiltRelay, HIGH);
    needsToBeReset = true;
    if(playing == false){
      playing = true;
      music();
    }
  }
  // Testing
  else{
    Serial.println("Nothing");
  }
  //SWORD
  if(valueSet3 >=945){
    Serial.println("Sword in");
    digitalWrite(swordRelay, HIGH);
    needsToBeReset = true;
  }
  // for testing
  else{
    Serial.println("Nothing");
  }
}

void music() {
  pinMode(speakerPin, OUTPUT);
  for (int i = 48; i < length; i++) {
  if (notes[i] == ' ') {
    delay(beats[i] * tempo); // rest
  } else {
    playNote(notes[i], beats[i] * tempo);
    } 
  // pause between notes
  delay(tempo / 2); 
  }
  delay(100);
}
