#include "RotorDeMapeo.h"

RotorDeMapeo::RotorDeMapeo() : cabeza(NULL) {
    // Crear 26 nodos A..Z y enlazarlos circularmente
    Nodo* prev = NULL;
    for (int i = 0; i < 26; ++i) {
        Nodo* nd = new Nodo;
        nd->val = (char)('A' + i);
        nd->prev = prev;
        nd->next = NULL;
        if (prev) prev->next = nd;
        index[i] = nd;
        if (i == 0) cabeza = nd;
        prev = nd;
    }
    // Cerrar el círculo
    cabeza->prev = prev;
    prev->next = cabeza;
}

RotorDeMapeo::~RotorDeMapeo() {
    // Romper el círculo y borrar todos
    if (!cabeza) return;
    RotorDeMapeo::Nodo* cur = cabeza->next;
    cabeza->prev->next = NULL; // romper ciclo

    while (cur) {
        Nodo* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    delete cabeza;
    cabeza = NULL;
}

void RotorDeMapeo::rotar(int n) {
    if (!cabeza) return;
    int k = n % 26;
    if (k == 0) return;
    if (k > 0) {
        while (k--) cabeza = cabeza->next;
    } else {
        while (k++) cabeza = cabeza->prev;
    }
}

char RotorDeMapeo::getMapeo(char in) const {
    if (in == ' ') return ' ';
    if (in < 'A' || in > 'Z') return in; // robustez básica

    // Distancia desde 'A' hasta 'in'
    int dist = (int)(in - 'A');

    // Avanzar dist pasos desde cabeza
    const Nodo* cur = cabeza;
    for (int i = 0; i < dist; ++i) cur = cur->next;

    return cur->val;
}
