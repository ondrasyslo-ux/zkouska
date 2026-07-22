#include "BeznyUcet.h"
#include <iostream>

BeznyUcet::BeznyUcet(const std::string& cislo, double poplatek)
: Ucet(cislo), poplatek(poplatek) {
}

void BeznyUcet::vypisInfo() const {
    Ucet::vypisInfo();
    std::cout << " | Typ: Bezny | Poplatek: " << poplatek << " Kc" << std::endl;
}

void BeznyUcet::analyzujUcet() const {
    int pocetVyberu = 0;
    
    // Analýza běžného účtu řeší jen počty výběrů (záporných čísel)
    for (double transakce : historieTransakci) {
        if (transakce < 0) {
            pocetVyberu++;
        }
    }
    std::cout << "analyza (" << cisloUctu 
              << ") Pocet vyberu je: " << pocetVyberu << std::endl;
}

bool BeznyUcet::operator==(const BeznyUcet& A) const {
    return this->poplatek == A.poplatek;
}

BeznyUcet& BeznyUcet::operator+=(double hodnota) {
    pridejTransakci(hodnota);
    return *this; // Vracíme samotný objekt, aby šlo operátory řetězit (např. u += 10 += 20)
}

// U friend funkce se do cpp souboru nepíše BeznyUcet::, protože funkce formálně nepatří třídě
std::ostream& operator<<(std::ostream& os, const BeznyUcet& ucet) {
    os << "BeznyUcet " << ucet.cisloUctu
       << ", transakci: " << ucet.historieTransakci.size();
    return os;
}
