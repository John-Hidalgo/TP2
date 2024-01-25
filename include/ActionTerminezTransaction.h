#pragma once
#include "GererCompacteur.h"

class ActionTerminezTransaction : public Action<>
{
private:
    GererCompacteur* m_compacteur;

public:
    ActionTerminezTransaction(GererCompacteur* p_compacteur)
    {
        m_compacteur = p_compacteur;
    }
    virtual void Executez() 
    {
        m_compacteur->TerminezTransaction();
    };

};