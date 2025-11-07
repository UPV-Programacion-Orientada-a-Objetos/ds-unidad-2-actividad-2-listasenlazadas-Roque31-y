/**
 * @file TramaMap.h
 * @brief Trama concreta de tipo MAP (M,N).
 */
#ifndef PRT7_TRAMAMAP_H
#define PRT7_TRAMAMAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Representa una trama M,N (N entero, positivo/negativo).
 */
class TramaMap : public TramaBase {
private:
    int delta; ///< Cantidad de rotación del rotor.
public:
    explicit TramaMap(int d);
    virtual ~TramaMap();

    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // PRT7_TRAMAMAP_H
