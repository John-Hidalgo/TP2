#pragma once

#include "LCD1602ProxyI2C.h"

class LCD1602 
{
 public:
  LCD1602(LCD1602ProxyI2C* p_proxy);
  const LCD1602& definirPositionCurseur(int p_colonne, int p_ligne) const;
  const LCD1602& afficher(const String& p_texte) const;
  const LCD1602& effacer() const;
  const LCD1602& afficherEnInterval(const String& p_texte, unsigned long p_inteval = 1000) const;

 private:
  LCD1602ProxyI2C* m_proxy;
};
