#pragma once
#include <NewPing.h>
#include <Action.h>

class SenseurDistance 
{
private:
    NewPing* m_sonar;
    Action<const unsigned int&>* m_action;
    unsigned long m_tempsDebut;
    const int m_distanceMinimal = 5;
    const int m_distanceMaximal = 30;
    const int m_distanceIgnorer = 80;
    const unsigned long m_Interval = 3000;
    const unsigned long m_SecondActionInterval = 1500;
    int m_maxDistance = 100;
    bool m_deuxiemAction = false;
public:
    SenseurDistance(int triggerPin, int echoPin);
    unsigned int MesurezDistance();
    bool ObjetDansPortee(unsigned int maxDistance); 
    void AffectezAction(Action<const unsigned int&>* p_action);
    void Ecoutez();
};
