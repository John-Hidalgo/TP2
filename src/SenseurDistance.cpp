#include "SenseurDistance.h"

SenseurDistance::SenseurDistance(int triggerPin, int echoPin)
{
    m_sonar = new NewPing(triggerPin,echoPin);   
}
unsigned int SenseurDistance::MesurezDistance() 
{
    return m_sonar->ping_cm();
}
bool SenseurDistance::ObjetDansPortee(unsigned int maxDistance) 
{
    unsigned int distance = MesurezDistance();
    return (distance > 0 && distance <= maxDistance);
}
void SenseurDistance::AffectezAction(Action<const unsigned int&>* p_action)
{
    this->m_action = p_action;
}
void SenseurDistance::Ecoutez() 
{
    unsigned long tempsCourant = millis();
    if (!m_deuxiemAction && tempsCourant - m_tempsDebut >= m_Interval) 
    {
        unsigned int distance = MesurezDistance();
        if (distance >= m_distanceMinimal && distance <= m_distanceMaximal) 
        {
            Serial.print("Can Accepted : ");
            Serial.println(distance);
            m_action->Executez(0);
        } 
        else if ((distance < m_distanceMaximal || distance > m_distanceMaximal) && distance < m_distanceIgnorer) 
        {
            Serial.print("Can Rejected: ");
            Serial.println(distance);
            m_action->Executez(1);
            m_deuxiemAction = true;
        } 
        else 
        {
            m_action->Executez(3);
        }
        m_tempsDebut = tempsCourant;
    }
    if (m_deuxiemAction && tempsCourant - m_tempsDebut >= m_SecondActionInterval) 
    {
        Serial.println("Do not throw in : ");  
        m_action->Executez(2);
        m_deuxiemAction = false;
    }
}