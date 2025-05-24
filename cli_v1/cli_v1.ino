// this program is based in project 4 of the arduino book and in a cli code I got from chat gpt
// there are a couple of example cli commands that do numeric operations, and one that sets the red, green, blue
// components of the rgb LED 

// LED pins and colors definitions

const int greenLEDPin = 9;
const int redLEDPin = 11;
const int blueLEDPin = 10;


int redValue = 50;
int greenValue = 0;
int blueValue = 100;


// CLI definitions

#define MAX_TOKENS 10
String tokens[MAX_TOKENS];
int values[MAX_TOKENS - 1];  // exclude the key
int valueCount = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Enter: key val1 val2 ... valn");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (parseCommand(input)) {
      handleCommand(tokens[0]);
    } else {
      Serial.println("Invalid input format.");
    }
  }

analogWrite(redLEDPin, redValue);
analogWrite(greenLEDPin, greenValue);
analogWrite(blueLEDPin, blueValue);
}

bool parseCommand(String input) {
  // Reset
  for (int i = 0; i < MAX_TOKENS; i++) tokens[i] = "";
  valueCount = 0;

  int tokenCount = 0;
  while (input.length() > 0 && tokenCount < MAX_TOKENS) {
    int spaceIndex = input.indexOf(' ');
    if (spaceIndex == -1) {
      tokens[tokenCount++] = input;
      break;
    } else {
      tokens[tokenCount++] = input.substring(0, spaceIndex);
      input = input.substring(spaceIndex + 1);
    }
  }

  if (tokenCount < 1) return false;

  // Parse values
  valueCount = tokenCount - 1;
  for (int i = 1; i < tokenCount; i++) {
    values[i - 1] = tokens[i].toInt();
  }

  return true;
}


void handleCommand(String key) {
  if (key == "add") {
    int sum = 0;
    for (int i = 0; i < valueCount; i++) {
      sum += values[i];
    }
    Serial.println("Sum = " + String(sum));

  } else if (key == "mul") {
    int product = 1;
    for (int i = 0; i < valueCount; i++) {
      product *= values[i];
    }
    Serial.println("Product = " + String(product));

  } else if (key == "max") {
    if (valueCount == 0) {
      Serial.println("No values provided.");
      return;
    }
    int maxVal = values[0];
    for (int i = 1; i < valueCount; i++) {
      if (values[i] > maxVal) maxVal = values[i];
    }
    Serial.println("Max = " + String(maxVal));

  } 
    else if (key == "rgbset") {
    if (valueCount < 3) {
      Serial.println("rgbset requires 3 values");
      return;
    }

    redValue = values[0];
    greenValue = values[1];
    blueValue = values[2];

  }   
  else {
    Serial.println("Unknown command: " + key);
  }
}
