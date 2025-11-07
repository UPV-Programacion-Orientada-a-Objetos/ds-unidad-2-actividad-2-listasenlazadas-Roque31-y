/**
 * @file TramaLoad.h
 * @brief Trama concreta de tipo LOAD (L,X).
 */
#ifndef PRT7_TRAMALOAD_H
#define PRT7_TRAMALOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Representa una trama L,X (X en A..Z o Space).
 */
class TramaLoad : public TramaBase {
private:
    char crudo; ///< Carácter recibido (ya normalizado a mayúscula). Puede ser ' '.
public:
    explicit TramaLoad(char c);
    virtual ~TramaLoad();

    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // PRT7_TRAMALOAD_H
