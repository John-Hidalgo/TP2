#pragma once
#include <WebServer.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include "Action.h"

#include "DepotCompacteur.h"
#include "GererCompacteur.h"


class ServeurCompacteur
{
public:
  //ServeurCompacteur();
  ServeurCompacteur(GererCompacteur* p_compacteur,const char* p_ssid, const char* p_motPasse,const char* p_url);
  //void GererReseaux();
  void RegistrezLesFunctions();
  void GererRacine();
  void GererChangerStatusComptacteur();
  void GererConsultezCannettes();
  void GererReinitialisezCannettes();
  void GererConsultezClientMontantRecu();
  //void GererClientMontantRecu();
  void GererConsultezAdresse();
  void GererModifiezAdresse();
  void Ecoutes();
private:
  WebServer* m_webServer;
  GererCompacteur* m_compacteur;
  const char* m_url;
  const char* m_pointTerminaison;

};