#include "LCD1602ProxyI2C.h"
#include <LiquidCrystal_I2C.h>

LCD1602ProxyI2C::LCD1602ProxyI2C() 
{
    this->m_lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    this->m_lcd->init();
    this->m_lcd->backlight();
}
void LCD1602ProxyI2C::definirPositionCurseur(int p_colonne, int p_ligne) const 
{
    this->m_lcd->setCursor(p_colonne, p_ligne);
}
void LCD1602ProxyI2C::afficher(const String& p_texte) const 
{
    //this->m_lcd->createChar();
    this->m_lcd->print(p_texte);
}

void LCD1602ProxyI2C::afficherEnInterval(const String& p_texte, unsigned long p_inteval) const
{
    if(millis() - m_dernierTempsAfficher >= p_inteval)
    {
        this->afficherEnInterval(p_texte,p_inteval);
        m_dernierTempsAfficher = millis();
    }
}

void LCD1602ProxyI2C::effacer() const 
{
    this->m_lcd->clear();
}

