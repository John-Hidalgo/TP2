#pragma once
#include <Arduino.h>
#include "Action.h"

class Bouton
{
private:
    const int m_buttonPin;
    unsigned long m_tempsDernierEtatChanger;
    bool m_dernierEtat;
    bool m_etatStable;
    const unsigned long m_tempsIgnorer = 20;
    Action<>* m_action;

public:
    Bouton(const int pin, Action<>* p_action); 
    bool DebounceAppuyee(int etatLu);
    void Ecoutes(); 
    void AffectezAction(Action<>* p_action);
};