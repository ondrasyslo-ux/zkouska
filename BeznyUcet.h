#pragma once
#include "Ucet.h"

class BeznyUcet : public Ucet {
private:
    double poplatek;

public:
    BeznyUcet(const std::string& cislo, double poplatek);
    
    void vypisInfo() const override;
    void analyzujUcet() const override;

    // Přetížení operátoru == pro porovnání dvou běžných účtů (porovnává jejich poplatky)
    bool operator==(const BeznyUcet& A) const;
    
    // Přetížení operátoru += pro snadné přidání transakce k účtu
    BeznyUcet& operator+=(double hodnota);
    
    // Přetížení operátoru << pro výpis. Musí to být friend, aby operátor patřil ostreamu, 
    // ale zároveň viděl na chráněné a privátní proměnné naší třídy.
    friend std::ostream& operator<<(std::ostream& os, const BeznyUcet& ucet);
};
