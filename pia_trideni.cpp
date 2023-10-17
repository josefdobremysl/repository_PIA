//pia_trideni.cpp

#include "pia_trideni.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


void nactiZeSouboru(CiselnaRada& pole, const std::string& nazevSouboru) {
    std::ifstream soubor(nazevSouboru);

    if (soubor.is_open()) {
        int hodnota;
        while (soubor >> hodnota) {
            pole.push_back(hodnota);
        }
        soubor.close();
    }
    else {
        std::cerr << "Nelze otevřít soubor: " << nazevSouboru << std::endl;
    }
}

int pocet(CiselnaRada& pole) {
    int pocetPrvku = pole.size();

    return pocetPrvku;
}
