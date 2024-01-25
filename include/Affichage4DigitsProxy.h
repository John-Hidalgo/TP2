#pragma once
#include <Arduino.h>
#include <TM1637Display.h>


const int8_t segments[] = 
{
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00000111,  // 7
    0b01111111,  // 8
    0b01101111   // 9
};
// // class Affichage4DigitsProxy 
// // {
// // public:
// //     virtual void afficher(uint8_t p_d1, uint8_t p_d2, uint8_t p_d3, uint8_t p_d4) = 0;
// //     virtual void AfficherHeure() = 0;
// // };

class Affichage4DigitsProxy //: public Affichage4DigitsProxy 
{
 public:
  Affichage4DigitsProxy(int p_pinHorloge,int p_pinDonnees) 
  {
    this->m_tm1637 = new TM1637Display(p_pinHorloge, p_pinDonnees);
    this->m_tm1637->setBrightness(7); 
  }
  void afficher(uint8_t p_d1, uint8_t p_d2, uint8_t p_d3, uint8_t p_d4)
  {
    uint8_t segments[] = {p_d1, p_d2, p_d3, p_d4};
    this->m_tm1637->setSegments(segments);
    
  }
  void AfficherHeure()
  {
    time_t now = time(nullptr);
    struct tm *timeinfo;
    timeinfo = localtime(&now);
    int displayValue = (timeinfo->tm_min % 100) * 100 + (timeinfo->tm_sec % 100);
    m_tm1637->showNumberDecEx(displayValue, 0b01000000, true);
    m_tm1637->showNumberDecEx(displayValue, 0b01000000, false); 
  }
  void AffichezFloat(float p_valeur)
  {
  int intValue = int(p_valeur * 100);

  // Display the integer value on the 7-segment display
  //display.showNumberDec(intValue);
  m_tm1637->showNumberDecEx(intValue, 0b01000000, true);
  delay(1000);
  }

 private:
  TM1637Display* m_tm1637;
};