#include <Arduino.h>
#include "SenseurDistance.h"
#include "ServeurCompacteur.h"
#include "ActionTraiterCanettes.h"
#include "ActionEtatCompacteur.h"
#include "ActionTerminezTransaction.h"
#include "LCD1602.h"
#include "Affichage4Digits.h"
//#include "Transaction.h"
// const char *ssid = "oxio-9360";
// const char *password = "9c6aa39c12";
const char *ssid = "tp2compacteur";
const char *password = "0123456789";
const char *url = "http://192.168.1.17";
const int sclPin = 18; 
const int sdaPin = 19; 
const int echoPin = 25;
const int triggerPin = 26;
const int boutonOperPin = 17;
const int boutonClientPin = 16;

ServeurCompacteur* serv;
Bouton* boutonClient;
Bouton* boutonOperateur;
Affichage4Digits* digits;
LCD1602* lcd;
SenseurDistance* sens;
Transaction* transaction;
GererCompacteur* compacteur;
Action<const unsigned int&>* actionTraitezCanettes;
Action<>* actionInitialiserCanettes;
Action<>* actionTerminezTransaction;


void setup()
{
  Serial.begin(115200);
  Wire.begin();
  boutonOperateur = new Bouton(boutonOperPin,nullptr);
  boutonClient = new Bouton(boutonClientPin,nullptr);
  lcd = new LCD1602(new LCD1602ProxyI2C());
  digits = new Affichage4Digits(new Affichage4DigitsProxy(18,19));
  sens = new SenseurDistance(25,26);
  transaction = new Transaction();
  compacteur = new GererCompacteur(boutonClient,boutonOperateur,digits,lcd,sens,transaction);
  serv = new ServeurCompacteur(compacteur,ssid,password,url);
  actionTraitezCanettes = new ActionTraiterCanettes(compacteur);
  actionInitialiserCanettes = new ActionEtatCompacteur(compacteur);
  actionTerminezTransaction = new ActionTerminezTransaction(compacteur);
  sens->AffectezAction(actionTraitezCanettes);
  boutonOperateur->AffectezAction(actionInitialiserCanettes);
  boutonClient->AffectezAction(actionTerminezTransaction);
}

void loop()
{
  //serv->Ecoutes();
  compacteur->Geres();
}

