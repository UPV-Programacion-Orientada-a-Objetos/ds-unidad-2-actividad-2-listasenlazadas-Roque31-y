#include "TramaMap.h"
#include "RotorDeMapeo.h"
#include "ListaDeCarga.h"
#include <stdio.h>

TramaMap::TramaMap(int d) : delta(d) {}
TramaMap::~TramaMap() {}

void TramaMap::procesar(ListaDeCarga* /*carga*/, RotorDeMapeo* rotor) {
    rotor->rotar(delta);
    if (delta >= 0)
        printf(" -> ROTANDO ROTOR +%d.", delta);
    else
        printf(" -> ROTANDO ROTOR %d.", delta);
}
