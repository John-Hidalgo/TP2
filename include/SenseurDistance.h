#pragma once
#include <NewPing.h>
#include <Action.h>

class SenseurDistance 
{
private:
  NewPing* m_sonar;
  Action<const unsigned int&>* m_action;
  unsigned long m_tempsDebut;
  const unsigned long m_Interval = 3000;
  const unsigned long m_SecondActionInterval = 1500;
  int m_maxDistance = 100;
  bool m_secondActionStarted = false;
public:

    SenseurDistance(int triggerPin, int echoPin, int maxDistance = 200)
    {
        m_sonar = new NewPing(triggerPin,echoPin);   
    }
    unsigned int mesurerDistance() 
    {
    return m_sonar->ping_cm();
    }

    bool objetDansPortee(unsigned int maxDistance) 
    {
    unsigned int distance = mesurerDistance();
    return (distance > 0 && distance <= maxDistance);
    }
    void AffectezAction(Action<const unsigned int&>* p_action)
    {
        this->m_action = p_action;
    }
    void Ecoutez()
    {
        //Serial.println("sensing");
        unsigned long tempsCourant = millis();
        // if (tempsCourant - m_tempsDebut >= m_Interval)
        // {
        //     unsigned int distance = mesurerDistance();
        //     if (distance >= 5 && distance <= 30)
        //     {
        //         // Serial.print("Can Accepted : ");
        //         // Serial.println(distance); 
        //         m_action->Executez(0);
        //     }
        //     else if((distance < 5 || distance > 30) && distance < 80)
        //     {
        //         // Serial.print("Can Rejected: "); 
        //         // Serial.println(distance); 
        //         m_action->Executez(1);
        //         m_action->Executez(2);
        //     }
        //     else
        //     {
        //         Serial.print("No can Detected: ");
        //         Serial.println(distance); 
        //         //m_action->Executez(3);
        //     }
        //     m_tempsDebut = tempsCourant;
        // }
    }

    void Ecoutez2() 
    {
        //Serial.println("sensor is sensing");
        unsigned long tempsCourant = millis();
        if (!m_secondActionStarted && tempsCourant - m_tempsDebut >= m_Interval) 
        {
            unsigned int distance = mesurerDistance();
            if (distance >= 5 && distance <= 30) 
            {
                Serial.print("Can Accepted : ");
                Serial.println(distance);
                m_action->Executez(0);
            } 
            else if ((distance < 5 || distance > 30) && distance < 80) 
            {
                Serial.print("Can Rejected: ");
                Serial.println(distance);
                m_action->Executez(1);
                m_secondActionStarted = true;
            } 
            else 
            {
                // Serial.print("No can Detected: ");
                // Serial.println(distance);
                m_action->Executez(3);
            }
            m_tempsDebut = tempsCourant;
        }
        if (m_secondActionStarted && tempsCourant - m_tempsDebut >= m_SecondActionInterval) 
        {
            Serial.println("Do not throw in : ");  
            m_action->Executez(2);
            m_secondActionStarted = false;
        }
    }
};
