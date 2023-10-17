//pia_trideni.h

#ifndef PIA_TRIDENI_H
#define PIA_TRIDENI_H

#include <vector>
#include <string>

// Vytvoreni aliasu pro dynamické pole celých čísel
typedef std::vector<int> CiselnaRada;

// Deklarace funkce pro načtení hodnot ze souboru
void nactiZeSouboru(CiselnaRada& pole, const std::string& nazevSouboru);

// Deklarace funkce pro určení počtu čísel v poli
int pocet(CiselnaRada& pole);

// Deklarace funkce pro setřídeni cisel pomoci bubble sort
void setrid(CiselnaRada& pole);

//Deklarace funkce ktera zapise retezec do souboru
void ulozDoSouboru(CiselnaRada& pole, const std::string& nazev_souboru);

#endif 
