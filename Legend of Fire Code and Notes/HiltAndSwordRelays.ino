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

void setup()
{
  // STOP RELAYS (to turn it on, use digitalWrite([name of relay], LOW);)
  digitalWrite(hiltRelay, HIGH);
  digitalWrite(swordRelay, HIGH);
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

void loop()
{
  // set0
  int valueSet0=analogRead(sense0);
  // set1
  int valueSet1=analogRead(sense1);
  // set2
  int valueSet2=analogRead(sense2);
  // set3
  int valueSet3=analogRead(sense3);

  // ALL THREE LIQUIDS ABOVE 910
  if(valueSet0>=910 and valueSet1>=910 and valueSet2>=910){
    Serial.println("1 and 2 and 3 (liquids done)");
    digitalWrite(hiltRelay, LOW);
  }
  else{
    Serial.println("Nothing");
  }
  // SWORD
  if(valueSet3 >=910){
    Serial.println("Sword in");
    digitalWrite(swordRelay, LOW);
  }
  else{
    Serial.println("Nothing");
  }
  
  
}
