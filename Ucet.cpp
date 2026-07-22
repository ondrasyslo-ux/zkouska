#include "Ucet.h"

// Inicializace statické proměnné (musí se dělat mimo hlavičkový soubor)
int Ucet::citac = 0;

Ucet::Ucet(const std::string& cislo) : cisloUctu(cislo) {
    // Při každém vytvoření nového účtu zvedneme čítač o 1
    citac++;
}

Ucet::~Ucet() {
    // Při smazání účtu čítač o 1 snížíme
    citac--;
}

int Ucet::getCitac() {
    return citac;
}

// Přidání jedné transakce nakonec vektoru
void Ucet::pridejTransakci(double hodnota) {
    historieTransakci.push_back(hodnota);
}

// Přetížení metody pro přidání celého seznamu transakcí najednou
void Ucet::pridejTransakci(const std::vector<double>& hodnota) {
    historieTransakci.insert(historieTransakci.end(), hodnota.begin(), hodnota.end());
}

std::vector<double>& Ucet::getHistorie() {
    return historieTransakci;
}

void Ucet::vypisInfo() const {
    std::cout << "Ucet: " << cisloUctu 
              << " | Pocet transakci: " << historieTransakci.size();
}
