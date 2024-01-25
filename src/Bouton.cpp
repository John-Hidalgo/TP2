#include "Bouton.h"

Bouton::Bouton(const int pin, Action<>* p_action) 
: m_buttonPin(pin), m_action(p_action), m_dernierEtat(false), m_etatStable(false)
{}

bool Bouton::DebounceAppuyee(int etatLu) 
{
    (etatLu != m_dernierEtat) ? (m_tempsDernierEtatChanger = millis()) : 0;
    return ((millis() - m_tempsDernierEtatChanger) > m_tempsIgnorer && etatLu != m_etatStable)
        ? ((m_etatStable = etatLu) == LOW ? true : false)
        : false;
}

void Bouton::Ecoutes() 
{
    int etatLu = digitalRead(m_buttonPin);
    DebounceAppuyee(etatLu) ? m_action->Executez() : void();
    m_dernierEtat = etatLu;
}
void Bouton::AffectezAction(Action<>* p_action) 
{
    m_action = p_action;
}