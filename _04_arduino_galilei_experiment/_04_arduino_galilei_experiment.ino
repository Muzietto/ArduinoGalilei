
const int switchPin   = 2;
const int coilPin     = 9;
const int redLedPin   = 3;
const int greenLedPin = 4;

const int foto0Pin = A0; // start
const int foto1Pin = A1; // start
const int foto2Pin = A2; // end
const int foto3Pin = A3; // end
const int foto4Pin = A4; // middle

const int INACTIVE  = 0;
const int ARMED     = 1;
const int RUNNING   = 2;
const int RESETTING = 3;

int foto0Low  = 1023;
int foto0High = 0;
int foto0Reading;
int foto0Threshold;
int foto0PassageTime;

int foto1Low  = 1023;
int foto1High = 0;
int foto1Reading;
int foto1Threshold;
int foto1PassageTime;

int foto2Low  = 1023;
int foto2High = 0;
int foto2Reading;
int foto2Threshold;
int foto2PassageTime;

int foto3Low  = 1023;
int foto3High = 0;
int foto3Reading;
int foto3Threshold;
int foto3PassageTime;

int foto4Low  = 1023;
int foto4High = 0;
int foto4Reading;
int foto4Threshold;
int foto4PassageTime;

int state;
int calibrated;
int startTime;
int safetyThreshold = 8;
int fotoDelay = 50;

float deltaXStart = 0.073; // metri
float deltaXEnd   = 0.070; // metri

// PUT HERE POSITIONS OF MAIN SENSORS (use meters!!!)
float foto0Pos = 0.088;            // start1
float foto4Pos = 0.694;            // middle
float foto2Pos = foto4Pos + 0.753; // end1

float foto1Pos = foto0Pos + deltaXStart;
float foto3Pos = foto2Pos + deltaXEnd;

void setup(){

  calibrated = 0;
  state = INACTIVE;
  
  pinMode(switchPin,  INPUT);
  pinMode(coilPin,    OUTPUT);
  pinMode(redLedPin,  OUTPUT);
  pinMode(greenLedPin,OUTPUT);
  
  pinMode(foto0Pin,INPUT); // start1
  pinMode(foto1Pin,INPUT); // start2
  pinMode(foto2Pin,INPUT); // end1
  pinMode(foto3Pin,INPUT); // end2
  pinMode(foto4Pin,INPUT); // middle
  
  digitalWrite(coilPin,LOW);
  digitalWrite(redLedPin,LOW);
  digitalWrite(greenLedPin,LOW);

  while(!Serial){}

  Serial.begin(9600);
  Serial.println(""); 
  Serial.println("***************************************");
  Serial.println("             CALIBRATION");
  Serial.println("***************************************");
}

  
void loop(){
  
  if (calibrated == 1) { // running experiments

    if (digitalRead(switchPin) == HIGH) { // switch CLOSED
      
      if (state == RUNNING) {
        // present results
        Serial.println("---------------------------------------");
        Serial.println("             RESULTS");
        Serial.println("---------------------------------------");
        Serial.print("Foto 0 - start 1; Position(m)=");
        Serial.print(foto0Pos);
        Serial.print("; Time(ms)=");
        Serial.println(foto0PassageTime);
        Serial.print("Foto 1 - start 1; Position(m)=");
        Serial.print(foto1Pos);
        Serial.print("; Time(ms)=");
        Serial.println(foto1PassageTime);
        Serial.print("Foto 4 - middle;  Position(m)=");
        Serial.print(foto4Pos);
        Serial.print("; Time(ms)=");
        Serial.println(foto4PassageTime);
        Serial.print("Foto 2 - end 1;  Position(m)=");
        Serial.print(foto2Pos);
        Serial.print("; Time(ms)=");
        Serial.println(foto2PassageTime);
        Serial.print("Foto 3 - end 2;  Position(m)=");
        Serial.print(foto3Pos);
        Serial.print("; Time(ms)=");
        Serial.println(foto3PassageTime);
        Serial.println("---------------------------------------");
        Serial.print("Speed at start (m/s)=");
        Serial.println(deltaXStart /  (((float)(foto1PassageTime-foto0PassageTime))/1000.0));
        Serial.print("Speed at end  (m/s)=");
        Serial.println(deltaXEnd /  (((float)(foto3PassageTime-foto2PassageTime))/1000.0));
        Serial.println("---------------- END  -----------------");

        // pressToReset
        digitalWrite(redLedPin,HIGH);
        state = RESETTING;
        Serial.println("state --> RESETTING");
        
        
      }
      if (state == INACTIVE) {
        // pressToArm
        digitalWrite(redLedPin,HIGH);
        digitalWrite(coilPin,HIGH);
        state = ARMED;        
        Serial.println("state --> ARMED");
      }

    } else { // switch OPEN
      // check fotos
      
      foto0Reading = analogRead(foto0Pin);
      if (foto0Reading < foto0Threshold) {
        Serial.print("Foto 0 - start 1; Threshold0=");
        Serial.print(foto0Threshold);
        Serial.print("; Reading0=");
        Serial.print(foto0Reading);
        Serial.print("; Time=");
        foto0PassageTime = millis() - startTime;
        Serial.println(foto0PassageTime);
        delay(fotoDelay*2);
      }
    
      foto1Reading = analogRead(foto1Pin);
      if (foto1Reading < foto1Threshold) {
        Serial.print("Foto 1 - start 2; Threshold1=");
        Serial.print(foto1Threshold);
        Serial.print("; Reading1=");
        Serial.print(foto1Reading);
        Serial.print("; Time=");
        foto1PassageTime = millis() - startTime;
        Serial.println(foto1PassageTime);
        delay(fotoDelay*2);
      }
    
      foto4Reading = analogRead(foto4Pin);
      if (foto4Reading < foto4Threshold) {
        Serial.print("Foto 4 - middle;  Threshold4=");
        Serial.print(foto4Threshold);
        Serial.print("; Reading4=");
        Serial.print(foto4Reading);
        Serial.print("; Time=");
        foto4PassageTime = millis() - startTime;
        Serial.println(foto4PassageTime);
        delay(fotoDelay*1.5);
      }
    
      foto2Reading = analogRead(foto2Pin);
      if (foto2Reading < foto2Threshold) {
        Serial.print("Foto 2 - end 1;   Threshold2=");
        Serial.print(foto2Threshold);
        Serial.print("; Reading2=");
        Serial.print(foto2Reading);
        Serial.print("; Time=");
        foto2PassageTime = millis() - startTime;
        Serial.println(foto2PassageTime);
        delay(fotoDelay);
      }
    
      foto3Reading = analogRead(foto3Pin);
      if (foto3Reading < foto3Threshold) {
        Serial.print("Foto 3 - end 2;   Threshold3=");
        Serial.print(foto3Threshold);
        Serial.print("; Reading3=");
        Serial.print(foto3Reading);
        Serial.print("; Time=");
        foto3PassageTime = millis() - startTime;
        Serial.println(foto3PassageTime);
        delay(fotoDelay);
      }
      
      if (state == RESETTING) {
        // releaseToInactive
        digitalWrite(redLedPin,LOW);
        digitalWrite(greenLedPin,LOW);
        state = INACTIVE;
        Serial.println("state --> INACTIVE");
        delay(2000);
      }
      if (state == ARMED) {
        delay(1000);
        // releaseToRun
        digitalWrite(redLedPin,LOW);
        digitalWrite(greenLedPin,HIGH);
        digitalWrite(coilPin,LOW);
        startTime = millis();
        state = RUNNING;
        Serial.println("state --> RUNNING");
      }
    }
    
  } else { // calibrate
  
    if (digitalRead(switchPin) == LOW) { // check foto's
      
        foto0Reading = analogRead(foto0Pin);
        if (foto0Reading < foto0Low)  {
          Serial.print("Foto 0 - start 1; analogRead()=");
          Serial.print(foto0Reading);
          Serial.println(" <-- adjusting  LOW"); 
          foto0Low =  foto0Reading; 
        }
        if (foto0Reading > foto0High) {
          Serial.print("Foto 0 - start 1; analogRead()=");
          Serial.print(foto0Reading);
          Serial.println(" <-- adjusting  LOW"); 
          foto0High = foto0Reading;
        }

        foto1Reading = analogRead(foto1Pin);
        if (foto1Reading < foto1Low)  {
          Serial.print("Foto 1 - start 2; analogRead()=");
          Serial.print(foto1Reading);
          Serial.println(" <-- adjusting  LOW");
          foto1Low =  foto1Reading;
        }
        if (foto1Reading > foto1High) {
          Serial.print("Foto 1 - start 2; analogRead()=");
          Serial.print(foto1Reading);
          Serial.println(" <-- adjusting HIGH");
          foto1High = foto1Reading;
        }
  
        foto4Reading = analogRead(foto4Pin);
        if (foto4Reading < foto4Low)  {
          Serial.print("Foto 4 - middle;  analogRead()=");
          Serial.print(foto4Reading);
          Serial.println(" <-- adjusting  LOW");
          foto4Low =  foto4Reading;
        }
        if (foto4Reading > foto4High) {
          Serial.print("Foto 4 - middle;  analogRead()=");
          Serial.print(foto4Reading);
          Serial.println(" <-- adjusting HIGH");
          foto4High = foto4Reading;
        }
  
        foto2Reading = analogRead(foto2Pin);
        if (foto2Reading < foto2Low)  {
          Serial.print("Foto 2 - end 1;   analogRead()=");
          Serial.print(foto2Reading);
          Serial.println(" <-- adjusting  LOW");
          foto2Low =  foto2Reading;
        }
        if (foto2Reading > foto2High) {
          Serial.print("Foto 2 - end 1;   analogRead()=");
          Serial.print(foto2Reading);
          Serial.println(" <-- adjusting HIGH");
          foto2High = foto2Reading;
        }
  
        foto3Reading = analogRead(foto3Pin);
        if (foto3Reading < foto3Low)  {
          Serial.print("Foto 3 - end 2;   analogRead()=");
          Serial.print(foto3Reading);
          Serial.println(" <-- adjusting  LOW");
          foto3Low =  foto3Reading;
        }
        if (foto3Reading > foto3High) {
          Serial.print("Foto 3 - end 2;   analogRead()=");
          Serial.print(foto3Reading);
          Serial.println(" <-- adjusting HIGH");
          foto3High = foto3Reading;
        }
    } else { // write results and exit loop
    
      foto0Threshold = (foto0Low + foto0High)/2 - safetyThreshold;
      foto1Threshold = (foto1Low + foto1High)/2 - safetyThreshold;
      foto2Threshold = (foto2Low + foto2High)/2 - safetyThreshold;
      foto3Threshold = (foto3Low + foto3High)/2 - safetyThreshold;
      foto4Threshold = (foto4Low + foto4High)/2 - safetyThreshold;
      
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
      Serial.println("state --> INACTIVE");
    
      calibrated = 1;
      delay(2000);
    }
  }
}

