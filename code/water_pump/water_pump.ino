int relay=7;
void setup() {
  pinMode(relay, OUTPUT);  
  digitalWrite(relay, LOW);  

}

void loop() {
  digitalWrite(relay, HIGH);    
    delay(10000);  
    digitalWrite(relay, LOW);  
    delay(5000);
}
