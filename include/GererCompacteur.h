#pragma once 

#include "Bouton.h"
#include "DepotCompacteur.h"
#include "LCD1602.h"
#include "Affichage4Digits.h"
#include "Transaction.h"
#include "SenseurDistance.h"

class GererCompacteur
{
    private:
    Bouton* m_boutonClients;
    Bouton* m_boutonOperateur;
    Affichage4Digits* m_digits;
    TM1637Display * m_disgits2;
    LCD1602* m_lcd;
    SenseurDistance* m_senseur;
    Transaction* m_transaction;
    unsigned long m_dernierTempsAfficher = 0;
    unsigned long m_dernierAffichage = 0;
    bool afficherDeuxiemeMessage = true;
    bool m_afficherRecu = true;

    public:
    GererCompacteur(Bouton* p_boutClients,Bouton* p_clientOperateur,Affichage4Digits* p_digits,LCD1602* p_lcd,SenseurDistance* p_senseur,Transaction* p_transaction);
    void TraitezCanette(int p_resultat);
    String InitialiserCanettes();
    String ObtiensCanettes() const;
    String ObtiensClientsRecu()const;
    String ActivierDesactiverCompactuer() const;
    String ModifiezAdresse(String p_nouvelleAdresse) const;
    void TerminezTransaction();
    void Geres();
};
