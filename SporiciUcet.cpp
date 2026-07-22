#include "SporiciUcet.h"
#include <iostream>

// V konstruktoru musíme nejprve zavolat konstruktor bázové třídy Ucet a předat mu číslo
SporiciUcet::SporiciUcet(const std::string& cislo, double urok) 
: Ucet(cislo), urokovaSazba(urok) {
}

void SporiciUcet::vypisInfo() const {
    // Nejprve zavoláme původní výpis z bázové třídy (vypíše číslo účtu a počet transakcí)
    Ucet::vypisInfo();

    // A následně k tomu na stejný řádek přidáme specifika spořicího účtu
    std::cout << " | Typ: Sporici | Urok: " << urokovaSazba << " %" << std::endl;
}

void SporiciUcet::analyzujUcet() const {
    double sumaVkladu = 0.0;
    int pocetVkladu = 0;

    // Speciální analýza pro spořicí účet: počítá průměrnou výši všech vkladů (kladných čísel)
    for (double transakce : historieTransakci) {
        if (transakce > 0) {
            sumaVkladu += transakce;
            pocetVkladu++;
        }
    }
    
    // Ošetření dělení nulou pro případ, že účet nemá žádné vklady
    double prumer = (pocetVkladu > 0) ? (sumaVkladu / pocetVkladu) : 0.0;

    std::cout << "analyza (" << cisloUctu 
              << ") Prumerna vyse vkladu je: " << prumer << " Kc" << std::endl;
}
