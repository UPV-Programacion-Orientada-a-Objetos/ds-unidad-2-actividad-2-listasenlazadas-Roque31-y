/**
 * @file RotorDeMapeo.h
 * @brief Lista circular doblemente enlazada para mapeo de A-Z con rotación.
 */
#ifndef PRT7_ROTORDEMAPEO_H
#define PRT7_ROTORDEMAPEO_H

#include <stddef.h>

/**
 * @class RotorDeMapeo
 * @brief Implementa un rotor (lista circular doble) con los caracteres A..Z.
 *
 * La cabeza representa el mapeo de 'A'. getMapeo(c) devuelve el carácter
 * que cae a 'distancia(c)' pasos desde la cabeza. ' ' (espacio) se regresa tal cual.
 */
class RotorDeMapeo {
private:
    struct Nodo {
        char val;
        Nodo* prev;
        Nodo* next;
    };
    Nodo* cabeza;      ///< Nodo que representa actualmente el mapeo de 'A'.
    Nodo* index[26];   ///< Apuntadores directos a nodos 'A'..'Z' para búsqueda O(1).

    RotorDeMapeo(const RotorDeMapeo&);
    RotorDeMapeo& operator=(const RotorDeMapeo&);

public:
    RotorDeMapeo();
    ~RotorDeMapeo();

    void rotar(int n);
    char getMapeo(char in) const;
};

#endif // PRT7_ROTORDEMAPEO_H
