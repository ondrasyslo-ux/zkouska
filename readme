# 📚 Pravidla zápisu v C++ (Co patří kam)

Při psaní objektově orientovaného kódu v C++ se kód vždy rozděluje na dvě hlavní části:

## 1. Hlavičkové soubory (`.h`)
Fungují jako "jídelní lístek". Říkají kompilátoru, co třída umí, ale neříkají jak.

* **Ochrana proti kopírování:** Vždy začínají direktivou `#pragma once`.
* **Tělo třídy:** Definuje se pomocí `class Nazev { ... };` (nezapomeň na středník na konci!).
* **Dědičnost:** Píše se rovnou k názvu, např.: `class BeznyUcet : public Ucet`.
* **Metody:** Píše se sem pouze jejich hlavička (deklarace), např.: `void vypisInfo() const;`.
* **Polymorfismus:** Pokud chceš, aby šla metoda v budoucnu přepsat, musíš sem napsat slovíčko `virtual` (u bázové třídy) a `override` (u odvozené třídy).
* **Friend funkce:** Slovíčko `friend` se píše **pouze** sem.

## 2. Zdrojové soubory (`.cpp`)
Tady se nachází samotná logika (kód) jednotlivých metod.

* **Propojení:** Vždy musíš na začátku vložit hlavičku, např.: `#include "BeznyUcet.h"`.
* **Příslušnost ke třídě:** Před název každé metody musíš napsat jméno třídy a čtyřtečku, např.: `void BeznyUcet::vypisInfo()`. Jinak by si kompilátor myslel, že tvoříš úplně cizí funkci.
* **Klíčová slova:** Zde už se **nepíše** `virtual`, `override`, ani `friend`.
* **Operátory:** 
  * Pokud operátor patří třídě (jako `+=` nebo `==`), píše se normálně s `BeznyUcet::`. 
  * Pokud je to přítel (jako výpis `<<`), čtyřtečka se vynechává.

---

# ⚙️ Jak funguje náš kód (Celkový přehled)

Celý program stojí na třech pilířích: základním účtu, jeho dvou specializovaných verzích a hlavním programu, který to všechno řídí.

## Bázová třída (`Ucet`)
Je to obecná šablona pro všechny účty.
* Každý účet na světě má nějaké číslo a historii transakcí, proto jsou tyto proměnné zde (označené jako `protected`, aby na ně potomci viděli). 
* `static int citac` je sdílená proměnná pro všechny účty – počítá, kolik jich aktuálně existuje. 
* Obsahuje také čistě virtuální metodu (`= 0`) pro analýzu, což z ní dělá **abstraktní třídu** (nemůžeš vytvořit samotný `Ucet`, vždy to musí být konkrétní typ).

## Odvozené třídy (`SporiciUcet` a `BeznyUcet`)
Tyto třídy dědí všechno z bázové třídy a přidávají si vlastní specifika:
* **Spořicí účet** má navíc úrokovou sazbu. Jeho analýza počítá průměrnou výši všech *vkladů* (kladných čísel).
* **Běžný účet** má navíc poplatek za vedení. Jeho analýza počítá prostý počet *výběrů* (záporných čísel). Navíc má definované operátory, aby se daly poplatky porovnávat (`==`), daly se snadno přidávat transakce (`+=`) a účet se dal vypsat rovnou do konzole přes `std::cout <<`.

## Algoritmy
* **Nejdelší řada vkladů:** Prochází vektor. Když vidí plus, přičte 1 k aktuální řadě. Pokud aktuální řada překoná dosavadní rekord, uloží si ho. Jakmile vidí minus, aktuální řadu vynuluje.
* **Odstranění malých výběrů:** Abychom mohli bezpečně mazat z vektoru během jeho procházení, používáme iterátor (chytrou šipku na prvek). Pokud číslo splní podmínku (je mezi -50 a 0), metoda `.erase()` ho bezpečně smaže.

## Hlavní program (`main.cpp`)
1. Vytvoří vektor ukazatelů na obecný typ `Ucet*`. 
2. Přes operátor `new` do něj vloží konkrétní Běžné a Spořicí účty. 
3. Díky **polymorfismu** pak stačí jeden jednoduchý `for` cyklus k tomu, aby se každý účet zachoval podle toho, čím doopravdy je (vypíše svoje specifické info a udělá svou vlastní analýzu). 
4. Na konci program vše pečlivě po sobě uklidí operátorem `delete`.
