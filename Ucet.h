#pragma once
#include <iostream>
#include <string>
#include <vector>

// Bázová (rodičovská) abstraktní třída
class Ucet {
protected:
    // Protected znamená, že k těmto proměnným mají přístup i odvozené třídy (Sporici, Bezny)
    std::string cisloUctu;
    std::vector<double> historieTransakci;
    
    // Statická proměnná je sdílená pro všechny objekty této třídy (počítá všechny existující účty)
    static int citac;
        
public:
    Ucet(const std::string& cislo);
    
    // Virtuální destruktor je klíčový pro správné smazání odvozených tříd přes bázový ukazatel
    virtual ~Ucet();
    
    static int getCitac();
    void pridejTransakci(double hodnota);
    void pridejTransakci(const std::vector<double>& hodnota); 
    
    // Vrací klasickou referenci (bez const), abychom mohli vektor v main.cpp upravovat (mazat z něj)
    std::vector<double>& getHistorie();

    // Čistě virtuální metoda (= 0). Dělá z této třídy abstraktní třídu. 
    // Každý potomek ji MUSÍ povinně implementovat po svém.
    virtual void analyzujUcet() const = 0;
    
    // Běžná virtuální metoda – potomci ji mohou přepsat, ale mají už nějaký základ
    virtual void vypisInfo() const;
};
