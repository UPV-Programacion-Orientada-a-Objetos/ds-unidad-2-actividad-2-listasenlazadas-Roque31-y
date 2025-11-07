#include "ListaDeCarga.h"
#include <stdio.h>

ListaDeCarga::ListaDeCarga() : cabeza(NULL), cola(NULL) {}

ListaDeCarga::~ListaDeCarga() {
    // Liberar todos los nodos
    ListaDeCarga::Nodo* cur = cabeza;
    while (cur) {
        Nodo* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    cabeza = cola = NULL;
}

void ListaDeCarga::insertarAlFinal(char c) {
    Nodo* nd = new Nodo;
    nd->val = c;
    nd->prev = cola;
    nd->next = NULL;
    if (!cabeza) {
        cabeza = cola = nd;
    } else {
        cola->next = nd;
        cola = nd;
    }
}

void ListaDeCarga::imprimirMensaje() const {
    printf("MENSAJE OCULTO ENSAMBLADO:\n");
    const Nodo* cur = cabeza;
    while (cur) {
        putchar(cur->val);
        cur = cur->next;
    }
    putchar('\n');
}
