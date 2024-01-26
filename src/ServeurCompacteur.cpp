#include "ServeurCompacteur.h"


ServeurCompacteur::ServeurCompacteur(GererCompacteur* p_compacteur,const char* p_ssid, const char* p_motPasse,const char* p_url)
{
    this->m_compacteur = p_compacteur;
    Serial.begin(115200);
    // pinMode(25, OUTPUT);
    // WiFi.begin(p_ssid, p_motPasse);
    // Serial.print("Connecting to Wi-Fi");
    // int essai = 0;
    // while (WiFi.status() != WL_CONNECTED && essai < 20) 
    // {
    //     delay(500);
    //     Serial.print(".");
    //     essai++;
    // }
    // Serial.println(WiFi.localIP());

    WiFi.softAP(p_ssid, p_motPasse);
    Serial.print("Access Point started. IP Address: ");
    Serial.println(WiFi.softAPIP());
    delay(5000);
    if(!LittleFS.begin())
    {
        Serial.println("An error occurred while mounting LittleFS");
        return;
    }
    this->m_webServer = new WebServer(80);
    m_webServer->serveStatic("/css", LittleFS, "/css");
    Serial.println(LittleFS.exists("/index.html") ? "index.html file present" : "index.html file not found");
    Serial.println(LittleFS.exists("/pages/adresseEmplacement.html") ? "adresseEmplacement.html file present" : "adresseEmplacement.html file not found");
    Serial.println(LittleFS.exists("/Compacteur.json") ? "Compacteur.json file present" : "Compacteur.json file not found");
    Serial.println(LittleFS.exists("/css/styleIndex.css") ? "styleIndex.css file present" : "style.css file not found");
    this->RegistrezLesFunctions();
    this->m_webServer->begin();
    Serial.println("HTTP server started");
}

void ServeurCompacteur::RegistrezLesFunctions()
{
    this->m_webServer->on("/", HTTPMethod::HTTP_GET, [this]() { this->GererRacine(); });
    this->m_webServer->on("/js/index.js", HTTPMethod::HTTP_GET, [this]() {
        File file = LittleFS.open("/js/index.js", "r");
        if (file) 
        {
            this->m_webServer->send(200, "application/javascript", file.readString());
            file.close();
        } 
        else 
        {
            this->m_webServer->send(404, "text/plain", "File not found");
        }
    });
    this->m_webServer->on("/ChangerStatusCompacteur", HTTPMethod::HTTP_PUT, [this]() { this->GererChangerStatusComptacteur(); });
    this->m_webServer->on("/ConsultezCanettes", HTTPMethod::HTTP_GET, [this]() { this->GererConsultezCannettes(); });
    this->m_webServer->on(Uri("/" + String("ConsultezClientMontantRecu")), HTTPMethod::HTTP_GET, [this]() { this->GererConsultezClientMontantRecu(); });
    this->m_webServer->on(Uri("/" + String("ClientMontantRecu")), HTTPMethod::HTTP_PUT, [this]() { this->GererConsultezCannettes(); });
    this->m_webServer->on(Uri("/" + String("ConsultezAdresse")), HTTPMethod::HTTP_GET, [this]() { this->GererConsultezAdresse(); });
    this->m_webServer->on(Uri("/" + String("InitialisezCanettes")), HTTPMethod::HTTP_PUT, [this]() { this->GererReinitialisezCannettes(); });
    this->m_webServer->on(Uri("/" + String("ModifiezAdresse")), HTTPMethod::HTTP_PUT, [this]() { this->GererModifiezAdresse(); });
}
void ServeurCompacteur::GererRacine() 
{
    Serial.println("Handling root request");
    String status = DepotCompacteur::Lire<String>("status");
    File file = LittleFS.open("/index.html", "r");
    if (!file) 
    {
        Serial.println("Impossible d'ouvrir le fichier");
        m_webServer->send(404, "text/plain", "Fichier introuvable");
        return;
    }
    String htmlContent = "";
    while (file.available()) 
    {
        htmlContent += (char)file.read();
    }
    file.close();
    htmlContent.replace("<p></p>", String(status));
    m_webServer->send(200, "text/html", htmlContent);
}
void ServeurCompacteur::GererChangerStatusComptacteur() 
{
    Serial.println("calling PUT");
    String messageReponse;
    int codeReponse = 200;
    try 
    {
        messageReponse = m_compacteur->ActivierDesactiverCompactuer();
        Serial.println(messageReponse);
    } 
    catch (const std::exception &e) 
    {
        codeReponse = 500; 
        messageReponse = "Internal Server Error: " + String(e.what());
    }
    this->m_webServer->send(codeReponse, "text/plain", messageReponse);
}
void ServeurCompacteur::GererConsultezCannettes()
{
    String canettes = m_compacteur->ObtiensCanettes();
    Serial.println("Traitement de la demande ConsulterCannettes");
    Serial.println(canettes);
    File file = LittleFS.open("/pages/cannettes.html", "r");
    if (file) 
    {
        Serial.println("Fichier ouvert avec succès");
        String htmlContent = "";
        while (file.available()) 
        {
            htmlContent += (char)file.read();
        }
        htmlContent.replace("<p></p>", canettes);
        m_webServer->send(200, "text/html", htmlContent);
        file.close();
    } 
    else 
    {
        Serial.println("Impossible d'ouvrir le fichier");
        this->m_webServer->send(404, "text/plain", "Fichier introuvable");
    }
}
void ServeurCompacteur::GererReinitialisezCannettes()
{
    Serial.println("calling PUT");
    String messageReponse;
    int codeReponse = 200;
    if(this->m_webServer->hasArg("plain"))
    {
        Serial.println("arguments found in request from website");
        String jsonData = this->m_webServer->arg("plain");
        DynamicJsonDocument jsonDoc(512);
        DeserializationError erreur = deserializeJson(jsonDoc, jsonData);
        if(erreur)
        {
            Serial.println(erreur.c_str());
            codeReponse = 500;
            messageReponse = erreur.c_str();
        }
        else
        {
            serializeJsonPretty(jsonDoc, Serial);
            Serial.println();
            String canettes = jsonDoc["totalCanettesRecu"];
            Serial.println("Deserialized result JSON data: " + canettes);
            messageReponse = m_compacteur->InitialiserCanettes();
            Serial.print("value revieved from the repository: ");
            Serial.println(messageReponse);
        }
    }
    else
    {
        messageReponse = "No JSON data received.";
        codeReponse = 400; 
    }
    this->m_webServer->send(codeReponse,"text/plain",messageReponse);
}
void ServeurCompacteur::GererConsultezClientMontantRecu()
{
    String recu = m_compacteur->ObtiensClientsRecu();
    Serial.println("Traitement de la demande ConsultezClientMontantRecu");
    Serial.println(recu);
    File file = LittleFS.open("/pages/clientsRecu.html", "r");
    if (file) 
    {
        Serial.println("Fichier ouvert avec succès");
        String htmlContent = "";
        while (file.available()) 
        {
            htmlContent += (char)file.read();
        }
        htmlContent.replace("<p></p>", recu);
        m_webServer->send(200, "text/html", htmlContent);
        file.close();
    } 
    else 
    {
        Serial.println("Impossible d'ouvrir le fichier");
        this->m_webServer->send(404, "text/plain", "Fichier introuvable");
    }
}
void ServeurCompacteur::GererConsultezAdresse()
{
    Serial.println("Traitement de la demande ConsulterModifiezAdresse");
    String adresse = DepotCompacteur::Lire<String>("adresseEmplacement");
    Serial.println(adresse);
    File file = LittleFS.open("/pages/adresseEmplacement.html", "r");
    if (file) 
    {
        Serial.println("Fichier ouvert avec succès");
        String htmlContent = "";
        while (file.available()) 
        {
            htmlContent += (char)file.read();
        }
    
        htmlContent.replace("<p></p>", String(adresse));
        m_webServer->send(200, "text/html", htmlContent);
        file.close();
    } 
    else 
    {
        Serial.println("Impossible d'ouvrir le fichier");
        this->m_webServer->send(404, "text/plain", "Fichier introuvable");
    }
}
void ServeurCompacteur::GererModifiezAdresse()
{
    Serial.println("calling modify address on the server");
    String messageReponse;
    int codeReponse = 200;
    if(this->m_webServer->hasArg("plain"))
    {
        Serial.println("arguments found in request from website");
        String jsonData = this->m_webServer->arg("plain");
        Serial.println("Received JSON data: " + jsonData);
        DynamicJsonDocument jsonDoc(512);
        DeserializationError erreur = deserializeJson(jsonDoc, jsonData);
        if(erreur)
        {
            Serial.println(erreur.c_str());
            codeReponse = 500;
            messageReponse = erreur.c_str();
        }
        else
        {
            //serializeJsonPretty(jsonDoc, Serial);
            //Serial.println();
            String nouvelleAdresse = jsonDoc["address"];
            Serial.println("Deserialized result JSON data: " + nouvelleAdresse);
            messageReponse = m_compacteur->ModifiezAdresse(nouvelleAdresse);
        }
    }
    else
    {
        messageReponse = "No JSON data received.";
        codeReponse = 400; 
    }
    this->m_webServer->send(codeReponse,"text/plain",messageReponse);
}

void ServeurCompacteur::Ecoutes()
{
    m_webServer->handleClient();
    m_compacteur->Geres();
}