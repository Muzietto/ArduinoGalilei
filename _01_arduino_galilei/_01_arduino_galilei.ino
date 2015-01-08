
// read 2 HIGH -> set 9 LOW (coil OFF)
const int switchPin = 2;
const int greenLedPin = 4;
const int redLedPin = 3;
const int coilPin = 9; // transistor gate
const int foto0Pin = A0; // start
const int foto1Pin = A1; // start
const int foto2Pin = A2; // end
const int foto3Pin = A3; // end
const int foto4Pin = A4; // middle

int switchState = 0; // off
int startTime = 0;
int currentTime = 0;
int fotoThreshold = 500;

void setup() {
  pinMode(coilPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(foto0Pin, INPUT);
  pinMode(foto1Pin, INPUT);
  pinMode(foto2Pin, INPUT);
  pinMode(foto3Pin, INPUT);
  pinMode(foto4Pin, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  switchState = digitalRead(switchPin);
  
  if (switchState == LOW) { // prepare experiment
  
    digitalWrite(coilPin, HIGH); // power the coil    
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    
    // calibrate fotoresistors - see page 75
    
  } else { // press button --> start experiment

    if (startTime == 0) {
      startTime = millis();
    }
    
    digitalWrite(coilPin, LOW); // coil OFF
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    
    if (analogRead(foto0Pin) < fotoThreshold) {
      // alert console
      Serial.print("Foto 0 - start 1; Time=");
      Serial.println(millis());
    }
    if (analogRead(foto1Pin) < fotoThreshold) {
      // alert console
      Serial.print("Foto 1 - start 2; Time=");
      Serial.println(millis());
    }
    if (analogRead(foto4Pin) < fotoThreshold) {
      // alert console
      Serial.print("Foto 4 - middle; Time=");
      Serial.println(millis());      
    }
    if (analogRead(foto2Pin) < fotoThreshold) {
      // alert console
      Serial.print("Foto 2 - end 1; Time=");
      Serial.println(millis());      
    }
    if (analogRead(foto3Pin) < fotoThreshold) {
      // alert console
      Serial.print("Foto 3 - end 2; Time=");
      Serial.println(millis());
      Serial.println("***************************************");      
    }
  }
}

