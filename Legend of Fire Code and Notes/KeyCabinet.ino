// Pin for the 3 keys
int keyCabinet0 = 8; // Pin

// Pin for Relay
int keyCabinetRelay = 9; // Pin

// defaults the relay to off with digitalWrite and sets pins 8 and 9 to be outputs 
void setup() {
  pinMode(keyCabinet0, OUTPUT);
  pinMode(keyCabinetRelay, OUTPUT);
  // STOP RELAY (to turn it on, use digitalWrite([name of relay], HIGH);)
  digitalWrite(keyCabinetRelay, LOW);
  Serial.begin(9600);
}
// When switch is pressed, activate the relay
void loop() {
  int valueSet0 = digitalRead(keyCabinet0);
  if(valueSet0 == HIGH){
    digitalWrite(keyCabinetRelay, HIGH);
    
  }
  else{
    // Resets it when the switch isn't pressed
    digitalWrite(keyCabinetRelay, LOW);
  }
  

}


