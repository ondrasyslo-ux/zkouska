#include "Ucet.h"
#include "BeznyUcet.h"
#include "SporiciUcet.h"

#include <vector>
#include <iostream>

// --- ALGORITMUS 1 ---
// Najde nejdelší souvislou řadu kladných transakcí
int nejdelsiRadaVkladu(Ucet* u) {
    int maxRada = 0, aktRada = 0;
    
    for (double t : u->getHistorie()) {
        if (t > 0) {
            aktRada++;
            // Průběžně aktualizujeme rekord, pokud aktuální řada překoná dosavadní maximum
            if (aktRada > maxRada) maxRada = aktRada;
        } else {
            // Při výběru (záporném čísle) se aktuální počítadlo resetuje
            aktRada = 0; 
        }
    }
    return maxRada;
}

// --- ALGORITMUS 2 ---
// Smaže z historie drobné výběry v rozmezí -49.99 až -0.01
void odstranMaleVklady(Ucet* u) {
    // Vytvoříme přímou referenci na vektor, abychom z něj mohli reálně mazat
    std::vector<double>& stareTransakce = u->getHistorie();
    
    // Používáme iterátor (chytrou šipku na prvek) pro bezpečné mazání během procházení cyklu
    for (auto it = stareTransakce.begin(); it != stareTransakce.end(); ) {
        if (*it < 0 && *it > -50.0) {
            // Metoda erase prvek smaže a vrátí iterátor na další prvek v pořadí
            it = stareTransakce.erase(it);
        } else {
            // Pokud prvek nemažeme, musíme iterátor ručně posunout na další
            ++it;
        }
    }
}

int main() {
    // 1. Zkouška statické metody (na začátku je účtů logicky 0)
    int puvodniPocet = Ucet::getCitac();
    std::cout << "Puvodni pocet uctu: " << puvodniPocet << std::endl;

    // 2. Vektor ukazatelů na bázovou třídu (příprava na polymorfismus)
    std::vector<Ucet*> ucty;
    
    // Alokace na haldě pomocí operátoru new
    ucty.push_back(new BeznyUcet("CZ-1111", 50.0));
    ucty.push_back(new BeznyUcet("CZ-2222", 0.0));
    ucty.push_back(new SporiciUcet("CZ-3333", 4.5));

    std::cout << "aktivni ucty:" << Ucet::getCitac() << std::endl << std::endl;

    // Přidání transakcí přes přetíženou metodu (využití std::initializer_list vektoru)
    ucty[0]->pridejTransakci({100, -50, 45, 20, -70, -10, 25, 50});
    ucty[1]->pridejTransakci({-50, 100, -100, -25});
    ucty[2]->pridejTransakci({200, 700, -500, 75});

    // 3. POLYMORFISMUS
    // Kompilátor sám pozná, kterou verzi metod má zavolat podle toho, co reálně v paměti leží
    for (Ucet* u : ucty) {
        u->vypisInfo();
        u->analyzujUcet();
    }

    std::cout << "\nalgoritmus 1\n\n";
    std::cout << "Ucet CZ-1111 ma nejdelsi radu vkladu v delce: " 
              << nejdelsiRadaVkladu(ucty[0]) << " transakci.\n";

    std::cout << "\nalgoritmus 2\n";
    std::cout << "pocet transakci pred smazanim: " << ucty[0]->getHistorie().size() << std::endl;
    odstranMaleVklady(ucty[0]);
    std::cout << "pocet transakci po smazani: " << ucty[0]->getHistorie().size() << "\n\n";

    // 4. TEST PŘETÍŽENÝCH OPERÁTORŮ
    std::cout << "pretizeni operatoru\n";
    
    // Pro test operátorů používáme lokální objekty (alokované na zásobníku, bez operátoru new)
    BeznyUcet lokalA("LOKAL-A", 20);
    BeznyUcet lokalB("LOKAL-B", 20);
    BeznyUcet lokalC("LOKAL-C", 50);

    // Test operátoru +=
    lokalA += 1000;
    
    // Test operátoru <<
    std::cout << lokalA << std::endl;

    // Test operátoru ==
    if (lokalA == lokalB) {
        std::cout << "lokalA a B maji stejny poplatek\n";
    }
    // Negace podmínky pro účty, co se nerovnají
    if (!(lokalA == lokalC)) {
        std::cout << "lokalA a C NEMAJI stejny poplatek\n";
    }

    // 5. ÚKLID PAMĚTI
    std::cout << "\n--- uklid pameti ---\n";
    for (Ucet* u : ucty) {
        // Zavolá správný virtuální destruktor a uvolní místo z haldy
        delete u;
    }

    // Očekávaný výsledek je 3 (protože 3 účty z vektoru jsme smazali, 
    // ale ty 3 lokální se smažou až úplně na konci funkce main)
    std::cout << "pocet uctu ted: " << Ucet::getCitac() << std::endl;
    
    return 0;
}
