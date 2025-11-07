#include "TramaLoad.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include <stdio.h>

TramaLoad::TramaLoad(char c) : crudo(c) {}
TramaLoad::~TramaLoad() {}

void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char dec = rotor->getMapeo(crudo);
    if (crudo == ' ')
        printf(" -> Fragmento 'Space' decodificado como ' '.");
    else
        printf(" -> Fragmento '%c' decodificado como '%c'.", crudo, dec);
    carga->insertarAlFinal(dec);
}
