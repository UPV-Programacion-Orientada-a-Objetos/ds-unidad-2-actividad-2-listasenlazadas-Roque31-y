/**
 * @file SerialPort.h
 * @brief Abstracción mínima para lectura de puerto serial (Win32/POSIX).
 *
 * Cumple con el requerimiento de usar APIs del SO en ausencia de STL.
 */
#ifndef PRT7_SERIALPORT_H
#define PRT7_SERIALPORT_H

#include <stddef.h>

class SerialPort {
private:
    void* handle; ///< Descriptor/handle de archivo (reinterpretado según plataforma).
public:
    SerialPort();
    ~SerialPort();

    bool open(const char* device, int baud);
    int  readByte();        ///< Lee un byte, regresa -1 si no hay más/errores.
    void close();
};

#endif // PRT7_SERIALPORT_H
