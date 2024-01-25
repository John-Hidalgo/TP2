#include "GererCompacteur.h"

GererCompacteur::GererCompacteur(Bouton* p_boutonClients,Bouton* p_boutonOperateur,Affichage4Digits* p_digits,LCD1602* p_lcd,SenseurDistance* p_senseur,Transaction* p_transaction)
:m_boutonClients(nullptr),m_boutonOperateur(nullptr),m_digits(nullptr),m_lcd(nullptr),m_senseur(nullptr),m_transaction(nullptr)
{
    m_boutonClients = p_boutonClients;
    m_boutonOperateur = p_boutonOperateur;
    m_digits = p_digits;
    m_lcd = p_lcd;
    m_senseur = p_senseur;
    m_transaction = p_transaction;
}

/// @brief call this from the concrete ActionTraiterCannetes
void GererCompacteur::TraitezCanette(int p_resultat)
{
    if(p_resultat == 0)
    {
        this->m_transaction->Incrementez();
        this->m_lcd->effacer().afficher(DepotCompacteur::Lire("etat",4));
    }
    else if(p_resultat == 1)  
    {
        String message = DepotCompacteur::Lire("etat",1);
        int position = message.indexOf("onnue");
        String part1 = message.substring(0, position);
        String part2 = message.substring(position);
        this->m_lcd->effacer().afficher(part1).definirPositionCurseur(0,1).afficher(part2);
    }
    else if(p_resultat == 2)
    {
        String message = DepotCompacteur::Lire("etat",2);
        int position = message.indexOf("canette");
        String part1 = message.substring(0, position);
        String part2 = message.substring(position);
        this->m_lcd->effacer().afficher(part1).definirPositionCurseur(0,1).afficher(part2);
    }
    else
    {
        this->m_lcd->effacer().afficher(DepotCompacteur::Lire("etat",0));
    }
    
}
/// @brief call this in the server class to reset the cannettes
/// @return It returns the result of the json file.
String GererCompacteur::InitialiserCanettes()
{
    DepotCompacteur::SauveGarder("totalCanetteseRecu",0);
    int res = DepotCompacteur::Lire<int>("totalCanetteseRecu");
    // Serial.print("value reading within repository : ");
    // Serial.println(res);
    return String(res);
}
/// @brief Call this in the server class to modify the state
/// and in the implementation from the client button and in ActionEtatCompacteur
/// @return It returns the current state in the json file
String GererCompacteur::ActivierDesactiverCompactuer() const
{
    String status = DepotCompacteur::Lire<String>("status");
    if (status == "actif") 
    {
        DepotCompacteur::SauveGarder("status", "repos");
        this->m_transaction->SauveGarderTransaction();
    } 
    else 
    {
        DepotCompacteur::SauveGarder("status", "actif");
        this->m_transaction->ChargerTransaction();
    }
    return DepotCompacteur::Lire<String>("status");
}
/// @brief Call this in the server class to modify the address
/// @return It returns the current address in the json file
String GererCompacteur::ModifiezAdresse(String p_nouvelleAdresse) const
{
    DepotCompacteur::SauveGarder("adresseEmplacement",p_nouvelleAdresse);
    return DepotCompacteur::Lire<String>("adresseEmplacement");
}
void GererCompacteur::TerminezTransaction()
{
    String status = DepotCompacteur::Lire<String>("status");
    if (status == "actif") 
    {
        String message = DepotCompacteur::Lire("etat",3);
        int position = message.indexOf("recu");
        String part1 = message.substring(0, position);
        String part2 = message.substring(position);

        this->m_lcd->effacer().afficher(part1).definirPositionCurseur(0,1).afficher(part2);
        int totalCanettes =  DepotCompacteur::Lire<int>("totalCanettesRecu");
        float totalRecu =  DepotCompacteur::Lire<float>("totalRecuParClients");
        totalCanettes += this->m_transaction->ObtiensCanettes();
        totalRecu += this->m_transaction->ObtiensRecu();
        DepotCompacteur::SauveGarder("totalCanettesRecu",totalCanettes);
        DepotCompacteur::SauveGarder("totalRecuParClients",totalRecu);
        this->m_transaction->MiseEnNouvelle();
        this->m_transaction->SauveGarderTransaction();  
    }   
}

void GererCompacteur::Geres()
{
    m_boutonOperateur->Ecoutes();
    m_boutonClients->Ecoutes();
    unsigned long tempsCourant = millis();
    if(DepotCompacteur::Lire<String>("status") == "actif")
    {
        m_senseur->Ecoutez();
        m_transaction->AfficherTransaction(m_digits);
    }
    else if (tempsCourant - m_dernierTempsAfficher >= 1000)
    {
        m_lcd->effacer().afficher(DepotCompacteur::Lire<String>("status"));
        m_digits->afficher(0,0,0,0);
        m_dernierTempsAfficher = millis();
    }
}

// void GererCompacteur::Geres()
// {
//     m_boutonOperateur->Ecoutes();
//     m_boutonClients->Ecoutes();
//     unsigned long tempsCourant = millis();
//     if (DepotCompacteur::Lire<String>("status") == "actif")
//     {
//         m_senseur->Ecoutez2();
//         if (tempsCourant - m_dernierTempsAfficher >= 1000)
//         {
//             if (this->m_afficherRecu) 
//             {
//                 //Serial.println(this->m_transaction->ObtiensRecu());
//                 m_digits->AffichezFloat(this->m_transaction->ObtiensRecu());
//             } 
//             else 
//             {
//                 //this->m_disgits2->showNumberDec(m_transaction->ObtiensCanettes());
//                 //Serial.println(this->m_transaction->ObtiensCanettes());
//                 m_digits->afficherDecimal(this->m_transaction->ObtiensCanettes());
//             }
//             m_afficherRecu = !m_afficherRecu;
//             m_dernierTempsAfficher = millis();
//         }
//     }
//     // if (tempsCourant - m_dernierTempsAfficher >= 1000)
//     // {
//     //     m_lcd->effacer().afficher(DepotCompacteur::Lire<String>("status"));
//     //     m_digits->afficher(0, 0, 0, 0);
//     //     m_dernierTempsAfficher = millis();
//     // }
// }


String GererCompacteur::ObtiensCanettes() const
{
    int res = DepotCompacteur::Lire<int>("totalCanettesRecu");
    //Serial.println(res);
    return String(res);
}
String GererCompacteur::ObtiensClientsRecu() const
{
    float res = DepotCompacteur::Lire<float>("totalRecuParClients");
    //Serial.println(res);
    return String(res);
}