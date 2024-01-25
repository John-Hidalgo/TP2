#pragma once
#include "Action.h"
#include "GererCompacteur.h"

class ActionInitialiserCanettes : public Action<>
{
private:
    GererCompacteur* m_compacteur;

public:
    ActionInitialiserCanettes(GererCompacteur* p_compacteur)
    {
        m_compacteur = p_compacteur;
    }
    virtual void Executez() 
    {
        m_compacteur->ActivierDesactiverCompactuer();
    };

};


