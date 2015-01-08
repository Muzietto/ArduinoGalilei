
const int switchPin = 2;
const int foto0Pin = A0; // start
const int foto1Pin = A1; // start
const int foto2Pin = A2; // end
const int foto3Pin = A3; // end
const int foto4Pin = A4; // middle

int calibrated = 0; // off

int startTime = 0;
int currentTime = 0;
int fotoThreshold = 500;

int foto0Low  = 1023;
int foto0High = 0;
int foto0Reading;
int foto0Threshold;

int foto1Low  = 1023;
int foto1High = 0;
int foto1Reading;
int foto1Threshold;

int foto2Low  = 1023;
int foto2High = 0;
int foto2Reading;
int foto2Threshold;

int foto3Low  = 1023;
int foto3High = 0;
int foto3Reading;
int foto3Threshold;

int foto4Low  = 1023;
int foto4High = 0;
int foto4Reading;
int foto4Threshold;

void setup() {

  pinMode(switchPin, INPUT);
  pinMode(foto0Pin, INPUT);
  pinMode(foto1Pin, INPUT);
  pinMode(foto2Pin, INPUT);
  pinMode(foto3Pin, INPUT);
  pinMode(foto4Pin, INPUT);
  
  while(!Serial) {}
  
  Serial.begin(9600);
  Serial.println("***************************************");      
  Serial.print("CALIBRATION; millis()=");
  Serial.println(millis());
  Serial.println("***************************************");      

}

void loop() {
  
  if (calibrated == 0) {
    if (digitalRead(switchPin) == LOW) { // check foto's
      
        Serial.println("***************************************");
        Serial.print("setup; millis()=");
        Serial.println(millis());
        Serial.println("***************************************");
  
        foto0Reading = analogRead(foto0Pin);
        Serial.print("Foto 0 - start 1; analogRead()=");
        Serial.print(foto0Reading);
        if (foto0Reading < foto0Low)  { foto0Low =  foto0Reading; Serial.print(" <-- adjusting  LOW"); }
        if (foto0Reading > foto0High) { foto0High = foto0Reading; Serial.print(" <-- adjusting HIGH"); }
        Serial.println("");
  
        foto1Reading = analogRead(foto1Pin);
        Serial.print("Foto 1 - start 2; analogRead()=");
        Serial.print(foto1Reading);
        if (foto1Reading < foto1Low)  { foto1Low =  foto1Reading; Serial.print(" <-- adjusting  LOW"); }
        if (foto1Reading > foto1High) { foto1High = foto1Reading; Serial.print(" <-- adjusting HIGH"); }
        Serial.println("");
  
        foto4Reading = analogRead(foto4Pin);
        Serial.print("Foto 4 - middle;  analogRead()=");
        Serial.print(foto4Reading);
        if (foto4Reading < foto4Low)  { foto4Low =  foto4Reading; Serial.print(" <-- adjusting  LOW"); }
        if (foto4Reading > foto4High) { foto4High = foto4Reading; Serial.print(" <-- adjusting HIGH"); }
        Serial.println("");
  
        foto2Reading = analogRead(foto2Pin);
        Serial.print("Foto 2 - end 1;   analogRead()=");
        Serial.print(foto2Reading);
        if (foto2Reading < foto2Low)  { foto2Low =  foto2Reading; Serial.print(" <-- adjusting  LOW"); }
        if (foto2Reading > foto2High) { foto2High = foto2Reading; Serial.print(" <-- adjusting HIGH"); }
        Serial.println("");
  
        foto3Reading = analogRead(foto3Pin);
        Serial.print("Foto 3 - end 2;   analogRead()=");
        Serial.print(foto3Reading);
        if (foto3Reading < foto3Low)  { foto3Low =  foto3Reading; Serial.print(" <-- adjusting  LOW"); }
        if (foto3Reading > foto3High) { foto3High = foto3Reading; Serial.print(" <-- adjusting HIGH"); }
        Serial.println("");
        Serial.println("***************************************");
      
      
      delay(5000);
    } else { // write results and exit loop
    
      foto0Threshold = (foto0Low + foto0High)/2;
      foto1Threshold = (foto1Low + foto1High)/2;
      foto2Threshold = (foto2Low + foto2High)/2;
      foto3Threshold = (foto3Low + foto3High)/2;
      foto4Threshold = (foto4Low + foto4High)/2;
      
      Serial.println("----------------- RESULTS -----------------");

      Serial.print("Foto 0 - start 1; low=");
      Serial.print(foto0Low);
      Serial.print("; high=");
      Serial.print(foto0High);
      Serial.print("; threshold=");
      Serial.print(foto0Threshold);
      Serial.println("");

      Serial.print("Foto 1 - start 2; low=");
      Serial.print(foto1Low);
      Serial.print("; high=");
      Serial.print(foto1High);
      Serial.print("; threshold=");
      Serial.print(foto1Threshold);
      Serial.println("");

      Serial.print("Foto 4 - middle;  low=");
      Serial.print(foto4Low);
      Serial.print("; high=");
      Serial.print(foto4High);
      Serial.print("; threshold=");
      Serial.print(foto4Threshold);
      Serial.println("");

      Serial.print("Foto 2 - end 1;   low=");
      Serial.print(foto2Low);
      Serial.print("; high=");
      Serial.print(foto2High);
      Serial.print("; threshold=");
      Serial.print(foto2Threshold);
      Serial.println("");

      Serial.print("Foto 3 - end 2;   low=");
      Serial.print(foto3Low);
      Serial.print("; high=");
      Serial.print(foto3High);
      Serial.print("; threshold=");
      Serial.print(foto3Threshold);
      Serial.println("");

      Serial.println("----------------------------------------");      
    
      calibrated = 1;
    }
  }
}

