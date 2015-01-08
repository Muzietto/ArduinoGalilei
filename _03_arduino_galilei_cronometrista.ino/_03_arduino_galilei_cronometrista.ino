
const int foto0Pin = A0; // start
const int foto1Pin = A1; // start
const int foto2Pin = A2; // end
const int foto3Pin = A3; // end
const int foto4Pin = A4; // middle

int startTime = 0;

int foto0Threshold = 563;
int foto1Threshold = 562;
int foto4Threshold = 720;
int foto2Threshold = 713;
int foto3Threshold = 727;

int foto0Reading;
int foto1Reading;
int foto2Reading;
int foto3Reading;
int foto4Reading;

int fotoDelay = 50;

void setup() {
  pinMode(foto0Pin, INPUT);
  pinMode(foto1Pin, INPUT);
  pinMode(foto2Pin, INPUT);
  pinMode(foto3Pin, INPUT);
  pinMode(foto4Pin, INPUT);
  
  while(!Serial){}
  
  Serial.begin(9600);
  Serial.println("***************************************");      
  Serial.print("setup; millis()=");
  Serial.println(millis());
  Serial.println("***************************************");      
}

void loop() {

  if (startTime == 0) {
    startTime = millis();
  }

  foto0Reading = analogRead(foto0Pin);
  if (foto0Reading < foto0Threshold) {
    Serial.print("Foto 0 - start 1; Threshold0=");
    Serial.print(foto0Threshold);
    Serial.print("; Reading0=");
    Serial.print(foto0Reading);
    Serial.print("; Time=");
    Serial.println(millis() - startTime);
    delay(fotoDelay*2);
  }

  foto1Reading = analogRead(foto1Pin);
  if (foto1Reading < foto1Threshold) {
    Serial.print("Foto 1 - start 2; Threshold1=");
    Serial.print(foto1Threshold);
    Serial.print("; Reading1=");
    Serial.print(foto1Reading);
    Serial.print("; Time=");
    Serial.println(millis() - startTime);
    delay(fotoDelay*2);
  }

  foto4Reading = analogRead(foto4Pin);
  if (foto4Reading < foto4Threshold) {
    Serial.print("Foto 4 - middle;  Threshold4=");
    Serial.print(foto4Threshold);
    Serial.print("; Reading4=");
    Serial.print(foto4Reading);
    Serial.print("; Time=");
    Serial.println(millis() - startTime);
    delay(fotoDelay*1.5);
  }

  foto2Reading = analogRead(foto2Pin);
  if (foto2Reading < foto2Threshold) {
    Serial.print("Foto 2 - end 1;   Threshold2=");
    Serial.print(foto2Threshold);
    Serial.print("; Reading2=");
    Serial.print(foto2Reading);
    Serial.print("; Time=");
    Serial.println(millis() - startTime);
    delay(fotoDelay);
  }

  foto3Reading = analogRead(foto3Pin);
  if (foto3Reading < foto3Threshold) {
    Serial.print("Foto 3 - end 2;   Threshold3=");
    Serial.print(foto3Threshold);
    Serial.print("; Reading3=");
    Serial.print(foto3Reading);
    Serial.print("; Time=");
    Serial.println(millis() - startTime);
    delay(fotoDelay);
  }
}

