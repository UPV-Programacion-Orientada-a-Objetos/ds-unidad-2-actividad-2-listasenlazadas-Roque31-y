/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para almacenar caracteres decodificados.
 */
#ifndef PRT7_LISTADECARGA_H
#define PRT7_LISTADECARGA_H

#include <stddef.h>

/**
 * @class ListaDeCarga
 * @brief Implementa una lista doblemente enlazada de chars con inserción al final.
 */
class ListaDeCarga {
private:
    struct Nodo {
        char val;
        Nodo* prev;
        Nodo* next;
    };
    Nodo* cabeza;
    Nodo* cola;

    // Evitar copia
    ListaDeCarga(const ListaDeCarga&);
    ListaDeCarga& operator=(const ListaDeCarga&);

public:
    ListaDeCarga();
    ~ListaDeCarga();

    void insertarAlFinal(char c);
    void imprimirMensaje() const;
};

#endif // PRT7_LISTADECARGA_H
