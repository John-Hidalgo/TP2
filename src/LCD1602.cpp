#include "LCD1602.h"

#include "LCD1602ProxyI2C.h"

LCD1602::LCD1602(LCD1602ProxyI2C* p_proxy) : m_proxy(p_proxy) { ; }

const LCD1602& LCD1602::definirPositionCurseur(int p_colonne, int p_ligne) const 
{
  this->m_proxy->definirPositionCurseur(p_colonne, p_ligne);
  return *this;
}
const LCD1602& LCD1602::afficher(const String& p_texte) const 
{
  this->m_proxy->afficher(p_texte);
  return *this;
}
const LCD1602& LCD1602::afficherEnInterval(const String& p_texte,unsigned long p_interval) const 
{
  this->m_proxy->afficherEnInterval(p_texte);
  return *this;
}

const LCD1602& LCD1602::effacer() const { this->m_proxy->effacer(); return *this;}