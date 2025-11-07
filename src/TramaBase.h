/**
 * @file TramaBase.h
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7.
 */
#ifndef PRT7_TRAMABASE_H
#define PRT7_TRAMABASE_H

class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Interfaz común de tramas. Requiere procesamiento polimórfico.
 */
class TramaBase {
public:
    virtual ~TramaBase() {} ///< Destructor virtual obligatorio.
    /**
     * @brief Procesa la trama en función de su tipo.
     * @param carga Lista doblemente enlazada donde se insertan datos ya decodificados.
     * @param rotor Rotor de mapeo (lista circular) para decodificar caracteres.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // PRT7_TRAMABASE_H
