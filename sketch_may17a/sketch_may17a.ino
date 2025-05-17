
int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;
int pitchLow = 100;
int pitchHigh =1000;

const int ledPin = 13;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  while(millis() < 5000) {
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh){
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow){
      sensorLow=sensorValue;
    }
    // Serial.print(sensorValue);
  }
  digitalWrite(ledPin,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  sensorValue = analogRead(A0);
  
  int pitch = map(sensorValue,sensorLow,sensorHigh, pitchLow, pitchHigh);

  tone(8,pitch,20);

  handleCLI();
  
  //Serial.print(sensorValue);
 // Serial.print("\n");
 // Serial.  digitalWrite(ledPin, LOW);  // Turn LED offprint(pitch);
 // Serial.print("\n");
}

void handleCLI(){

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read the incoming command

    command.trim(); // Remove any leading/trailing spaces or newline characters

    // Process commands
    if (command == "LED_ON") {
      digitalWrite(ledPin, HIGH);  // Turn LED on
      Serial.println("LED turned ON");
    }
    else if (command == "LED_OFF") {
      digitalWrite(ledPin, LOW);  // Turn LED off
      Serial.println("LED turned OFF");
    }
    else if (command == "SENSORVAL") {
      Serial.println(sensorValue);
    }
    else if (command == "STATUS") {
      if (digitalRead(ledPin) == HIGH) {
        Serial.println("LED is ON");
      } else {
        Serial.println("LED is OFF");
      }
    }
    else {
      Serial.println("Unknown command");
    }
  }

  
}
