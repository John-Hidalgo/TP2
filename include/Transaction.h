#pragma once
#include <Arduino.h>
#include "Affichage4Digits.h"
#include "DepotCompacteur.h"

class Transaction
{
private:
    int m_montantCanettes = 0;
    float m_montantRecu = 0.0f;
    unsigned long m_dernierAffichage = 0;
    const unsigned long m_durationAlternance = 1000;
    bool afficherRecu = true;
public:
    void Incrementez();
    void AfficherTransaction(Affichage4Digits* p_digits);
    void SauveGarderTransaction();
    void ChargerTransaction();
    void MiseEnNouvelle();
    int ObtiensCanettes() const ;
    float ObtiensRecu() const ;
};
