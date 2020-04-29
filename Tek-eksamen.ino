v// Biblioteker
#include <I2CSoilMoistureSensor.h> // Fugtighedssensor
#include <Wire.h>                  // Sensor til arduino (I2C)
#include <Servo.h>                 // Servo

Servo myservo;                     // Servo objekt
I2CSoilMoistureSensor fugtSensor;  // Sensor objekt

// Globale værdier
int fugtNiveau;        // Hvor fugtig jorden er
int fugtGraensevaerdi; // Grænseværdien for vanding
int vande_tid = 10000; // pt sat til 10 sekunder
int pos;               // Variable til at gemme positionen af servo

void setup() {
  Wire.begin();       // Forbinder servo med arduino
  Serial.begin(9600); // Starter konsolen på 9600 BAUD 
  myservo.attach(9);  // Pin som servo sidder i

  // Starter sensor og giver tid at boot
  fugtSensor.begin();
  delay(1000);
}
  void loop() {
    // Venter 50ms hvis fugtighedssensor er i gang med en måling
    while(fugtSensor.isBusy()) {
       delay(50);
     }

    // Sætter fugtigheds niveauet ind i fugtNiveau int og printer det i konsolen
    fugtNiveau = fugtSensor.getCapacitance();
    Serial.print("Fugt i jord: " + fugtNiveau);

    // Åbner for vand
    if (fugtNiveau > fugtGraensevaerdi) {
      for (pos = 0; pos = 90; pos++) { // Går fra 0 til 90 grader (åbner for vandet)
          myservo.write(pos);          // Fortæller servo at den skal gå til position pos
          delay(10);                   // Venter 10ms på at servo når frem til positionen
      }
      delay(vande_tid);                // Vander i dette stykke tid

     // Lukker for vand
     for (pos; pos = 0; pos--) {       // Går fra 90 til 0 grader (åbner for vandet)
        myservo.write(pos);            // Fortæller servo at den skal gå til position pos
        delay(10);                     // Venter 10ms på at servo når frem til positionen
     }
   }
}
