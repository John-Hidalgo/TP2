#include "Transaction.h"

void Transaction::Incrementez()
{
    m_montantCanettes++;
    m_montantRecu = m_montantCanettes * 0.1;
}
void Transaction::AfficherTransaction(Affichage4Digits* p_digits)
{
    if (millis() - m_dernierAffichage >= m_durationAlternance) 
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
void Transaction::SauveGarderTransaction()
{
    DepotCompacteur::SauveGarder("dernierTransaction",this->m_montantCanettes);
}
void Transaction::ChargerTransaction()
{
    this->m_montantCanettes = DepotCompacteur::Lire<int>("dernierTransaction");
    this->m_montantRecu = m_montantCanettes * 0.1;
}
void Transaction::MiseEnNouvelle()
{
    m_montantCanettes = 0;
    m_montantRecu = 0.0f;
}
int Transaction::ObtiensCanettes() const {return this->m_montantCanettes;}
float Transaction::ObtiensRecu() const {return this->m_montantRecu;}