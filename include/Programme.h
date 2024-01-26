#pragma once
#include <Arduino.h>
#include "SenseurDistance.h"
#include "ServeurCompacteur.h"
#include "ActionTraiterCanettes.h"
#include "ActionEtatCompacteur.h"
#include "ActionTerminezTransaction.h"
#include "LCD1602.h"
#include "Affichage4Digits.h"

class Programme
{
private:
    
public:
    Programme();
    void Setup();
    void Loop();
};
