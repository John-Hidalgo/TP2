#pragma once

#include "Affichage4DigitsProxy.h"

class Affichage4Digits 
{
public:
    Affichage4Digits(Affichage4DigitsProxy* p_proxy)
    : m_proxy(p_proxy) 
    {
      ;
    }

    void afficher(uint8_t p_d1, uint8_t p_d2, uint8_t p_d3, uint8_t p_d4) const
    {
      this->m_proxy->afficher(p_d1, p_d2, p_d3, p_d4);
    };
    void afficherBinaire(uint8_t p_valeur) const
    {
      this->m_proxy->afficher(
        segments[p_valeur >> 3 & 1],
        segments[p_valeur >> 2 & 1],
        segments[p_valeur >> 1 & 1], 
        segments[p_valeur & 1]);
    }

    void afficherDecimal(uint16_t p_valeur) const
    {
      uint16_t valeur = p_valeur;
      uint8_t d4 = valeur % 10;
      valeur /= 10;
      uint8_t d3 = valeur % 10;
      valeur /= 10;
      uint8_t d2 = valeur % 10;
      valeur /= 10;
      uint8_t d1 = valeur % 10;

      this->m_proxy->afficher(segments[d1], segments[d2], segments[d3],segments[d4]);
    }
    void AfficherHeure()
    {
        m_proxy->AfficherHeure();
    }
    void AffichezFloat(float p_valeur)
    {
      m_proxy->AffichezFloat(p_valeur);
    }
private:
    Affichage4DigitsProxy *m_proxy;
};