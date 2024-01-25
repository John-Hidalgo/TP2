#pragma once
//#include "DepotCompacteur.h" 
//#include "Action.h"

class Transaction
{
private:
    int m_montantCanettes = 0;
    float m_montantRecu = 0.0f;
    unsigned long m_dernierAffichage = 0;
    bool afficherRecu = true;
public:
    void Incrementez()
    {
        m_montantCanettes++;
        m_montantRecu = m_montantCanettes * 0.1;
    }
    void AfficherTransaction(Affichage4Digits* p_digits)
    {
        if (millis() - m_dernierAffichage >= 1000) 
        {
            m_dernierAffichage = millis();
            if (afficherRecu) 
            {
                p_digits->AffichezFloat(m_montantRecu);
            } 
            else 
            {
                p_digits->afficherDecimal(m_montantCanettes);
            }
            afficherRecu = !afficherRecu;
        }
    }
    void SauveGarderTransaction()
    {
        DepotCompacteur::SauveGarder("dernierTransaction",this->m_montantCanettes);
    }
    void ChargerTransaction()
    {
        this->m_montantCanettes = DepotCompacteur::Lire<int>("dernierTransaction");
        this->m_montantRecu = m_montantCanettes * 0.1;
    }
    void MiseEnNouvelle()
    {
        m_montantCanettes = 0;
        m_montantRecu = 0.0f;
    }
    int ObtiensCanettes() const {return this->m_montantCanettes;};
    float ObtiensRecu() const {return this->m_montantRecu;};
};


