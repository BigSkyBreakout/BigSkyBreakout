// Pin for the 3 keys
int keyCabinet0 = 8;

// Pin for Relay
int keyCabinetRelay = 9;


void setup() {
  pinMode(keyCabinet0, OUTPUT);
  pinMode(keyCabinetRelay, OUTPUT);
  // STOP RELAY (to turn it on, use digitalWrite([name of relay], HIGH);)
  digitalWrite(keyCabinetRelay, LOW);
  Serial.begin(9600);
}

void loop() {
  int valueSet0 = digitalRead(keyCabinet0);
  if(valueSet0 == HIGH){
    digitalWrite(keyCabinetRelay, HIGH);
    
  }
  else{
    digitalWrite(keyCabinetRelay, LOW);
  }
  

}


