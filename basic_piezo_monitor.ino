// const int PIEZO_PIN = A9; // Piezo output
// const float thresh = 500; // 

#include "zanimal.h"
#include "chien.h"

// struct Animal {
//   int nPattes;
//   int nYeux;

//   // Animal (int a, int b) {
//   //   nPattes = a;
//   //   nYeux = b;
//   // }
//   // OR
//   Animal (int a, int b): nPattes(a), nYeux(b) {}
//   void post() {
//     Serial.println(this->nPattes);
//   };
// };

// struct Chien: Animal {
//   int nPoils;
//   // Chien (int a, int b, int c) : Animal (a, b) {
//   //   nPoils = c;
//   // }
//   // OR
//   Chien (int a, int b, int c) : Animal (a, b), nPoils (c) {}

// };

// Chien ch(7, 8, 9);
// Animal ani(44, 2);
// chien ch;

void setup() 
{
}

void loop() 
{
  // ani.post();
  // ch.post();
Serial.println(*ani.nOreilles);

//   // Read Piezo ADC value in, and convert it to a voltage
//   int piezoADC = analogRead(PIEZO_PIN);
// //  float piezoV = piezoADC / 1023.0 * 3.3;
//   if (piezoADC >= thresh) { 
  // Serial.println(piezoADC); // Print the voltage.
//   }
// //  Serial.println(piezoV); // Print the voltage.
//   delay(1);
}