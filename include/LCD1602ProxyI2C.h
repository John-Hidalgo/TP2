#pragma once

#include <LiquidCrystal_I2C.h>

// class LCD1602Proxy 
// {
//  public:
//   virtual void definirPositionCurseur(int p_colonne, int p_ligne) const = 0;
//   virtual void afficher(const String& p_texte) const = 0;
//   virtual void effacer() const = 0;
// };

class LCD1602ProxyI2C
{
 public:
  LCD1602ProxyI2C();
  void definirPositionCurseur(int p_colonne, int p_ligne) const;
  void afficher(const String& p_texte) const;
  void afficherEnInterval(const String& p_texte, unsigned long p_inteval = 1000) const;
  void effacer() const;

 private:
  LiquidCrystal_I2C* m_lcd;
  mutable unsigned long m_dernierTempsAfficher = 0;
};
