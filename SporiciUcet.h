#pragma once
#include "Ucet.h"

// Třída dědí (public) všechny vlastnosti a metody z bázové třídy Ucet
class SporiciUcet : public Ucet {
private:
    double urokovaSazba;

public:
    SporiciUcet(const std::string& cislo, double urokovaSazba);
    
    // Klíčové slovo override kompilátoru říká, že vědomě přepisujeme metodu z bázové třídy
    void vypisInfo() const override;
    void analyzujUcet() const override;
};
