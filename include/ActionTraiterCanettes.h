#pragma once
#include "Action.h"
#include "GererCompacteur.h"

class ActionTraiterCanettes : public Action<const unsigned int&>
{
private:
    GererCompacteur* m_compacteur;
public:
    ActionTraiterCanettes(GererCompacteur* p_compacteur)
    {
        m_compacteur = p_compacteur;
    }
    virtual void Executez(const unsigned int& p_distance) 
    {
        m_compacteur->TraitezCanette(p_distance);
        //Serial.println("actio traiter canettes");
    };
};