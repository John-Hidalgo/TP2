#pragma once 

#include <ArduinoJson.h>
#include <LittleFS.h>
/// @brief fields you modify "numeroUnique" "etat"(an array) "adresseEmplacement" "totalCanetteseRecu" "totalRecuParClients"
/// "status" "dernierTransaction"
class DepotCompacteur 
{
public:
  static void SauveGarder(const String& key, const String& value) 
  {
    DynamicJsonDocument doc = LireDocument();

    if (doc.containsKey(key)) 
    {
      doc[key] = value;
      EcrireDocument(doc);
    }
  }

  static void SauveGarder(const String& key, int value) 
  {
    DynamicJsonDocument doc = LireDocument();
    if (doc.containsKey(key)) 
    {
      doc[key] = value;
      EcrireDocument(doc);
    }
  }

  static void SauveGarder(const String &key, float value) 
  {
    DynamicJsonDocument doc = LireDocument();
    if (doc.containsKey(key)) {
      doc[key] = value;
      EcrireDocument(doc);
    }
  }

  template <typename T>
  static T Lire(const String& key) {
    DynamicJsonDocument doc = LireDocument();

    if (doc.containsKey(key) && doc[key].is<T>()) {
      return doc[key].as<T>();
    }

    return T(); 
  }


  static String Lire(const String& key, int index) 
  {
    DynamicJsonDocument doc = LireDocument();

    if (doc.containsKey(key) && doc[key].is<JsonArray>() && doc[key].size() > index) 
    {
      return doc[key][index].as<String>();
    }

    return "";
  }

private:
  static DynamicJsonDocument LireDocument() {
    File file = LittleFS.open("/Compacteur.json", "r");
    DynamicJsonDocument doc(1024);

    if (file) 
    {
      DeserializationError error = deserializeJson(doc, file);
      file.close();

      if (error) 
      {
        Serial.println("Failed to deserialize JSON");
      }
    }

    return doc;
  }

  static void EcrireDocument(const DynamicJsonDocument& doc) 
  {
    File file = LittleFS.open("/Compacteur.json", "w");

    if (file) {
      serializeJson(doc, file);
      file.close();
    } else {
      Serial.println("Failed to open JSON file for writing");
    }
  }
};
