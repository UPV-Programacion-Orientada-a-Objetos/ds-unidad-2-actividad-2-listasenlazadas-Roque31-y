/**
 * @file main.cpp
 * @brief Punto de entrada del decodificador PRT-7.
 *
 * Requisitos clave:
 * - POO (TramaBase, TramaLoad, TramaMap)
 * - RotorDeMapeo: lista circular doblemente enlazada (A-Z)
 * - ListaDeCarga: lista doblemente enlazada para mensaje
 * - Sin STL: parseo manual con C-style
 * - Lectura serial (o simulación por archivo)
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "SerialPort.h"

// --- Utilidades de parseo C-style ---
static void chomp(char* s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) { s[n-1] = '\0'; --n; }
}

static char normalize_char(const char* token) {
    if (!token) return '\0';
    if (strcmp(token, "Space") == 0) return ' ';
    if (token[0] == '\0') return '\0';
    char c = token[0];
    if (c >= 'a' && c <= 'z') c = (char)(c - 'a' + 'A');
    return c;
}

static void log_mensaje_prefix(const char* raw) {
    printf("Trama recibida: [%s] -> Procesando...", raw);
}

// Lee una línea del serial en buffer (sin STL). Retorna true si logró leer algo.
static bool serial_readline(SerialPort& sp, char* out, size_t cap) {
    size_t pos = 0;
    while (pos + 1 < cap) {
        int b = sp.readByte();
        if (b < 0) {
            // No hay más por ahora
            if (pos == 0) return false;
            break;
        }
        char ch = (char)b;
        out[pos++] = ch;
        if (ch == '\n') break;
    }
    out[pos] = '\0';
    return pos > 0;
}

// Lee línea de archivo (C stdio) sin STL
static bool file_readline(FILE* f, char* out, size_t cap) {
    if (!f) return false;
    if (!fgets(out, (int)cap, f)) return false;
    return true;
}

int main(int argc, char** argv) {
    printf("Iniciando Decodificador PRT-7.\n");

    const char* port = NULL;
    int baud = 9600;
    const char* filename = NULL;

#ifdef PRT7_SIMULATION
    // Simulación por defecto
    filename = "../sample_input.txt";
#endif

    // Parseo muy simple de argumentos
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--port") == 0 && i+1 < argc) { port = argv[++i]; continue; }
        if (strcmp(argv[i], "--baud") == 0 && i+1 < argc) { baud = atoi(argv[++i]); continue; }
        if (strcmp(argv[i], "--file") == 0 && i+1 < argc) { filename = argv[++i]; continue; }
    }

    ListaDeCarga carga;
    RotorDeMapeo rotor;

#ifndef PRT7_SIMULATION
    if (!port) {
        printf("Conectando a puerto COM... (use --port)\n");
        return 1;
    }
#else
    if (!filename && !port) {
        printf("Modo simulación: use --file <ruta>, se intentará '../sample_input.txt'.\n");
    }
#endif

    FILE* fin = NULL;
    SerialPort sp;
    bool usar_serial = false;

    if (port) {
        printf("Conectando a puerto %s ...\n", port);
        if (!sp.open(port, baud)) {
            printf("ERROR: No se pudo abrir el puerto serial.\n");
            return 1;
        }
        usar_serial = true;
        printf("Conexión establecida. Esperando tramas...\n\n");
    } else {
        if (!filename) {
            printf("ERROR: No se especificó archivo (--file).\n");
            return 1;
        }
        fin = fopen(filename, "rb");
        if (!fin) {
            printf("ERROR: No se pudo abrir archivo '%s'\n", filename);
            return 1;
        }
        printf("Leyendo tramas desde archivo '%s'...\n\n", filename);
    }

    char line[128];
    while (1) {
        bool ok = usar_serial ? serial_readline(sp, line, sizeof(line))
                              : file_readline(fin, line, sizeof(line));
        if (!ok) break;

        chomp(line);
        if (line[0] == '\0') continue;

        // Copia local para mostrar en logs (sin modificar por strtok)
        char raw[128];
        strncpy(raw, line, sizeof(raw)-1);
        raw[sizeof(raw)-1] = '\0';

        // Parseo: "L,X" o "M,N"
        char local[128];
        strncpy(local, line, sizeof(local)-1);
        local[sizeof(local)-1] = '\0';

        char* saveptr = NULL;
        char* t0 = strtok_r(local, ",", &saveptr);
        char* t1 = strtok_r(NULL, ",", &saveptr);

        if (!t0) continue;
        char tipo = t0[0];

        // Normalizar tipo a mayúscula
        if (tipo >= 'a' && tipo <= 'z') tipo = (char)(tipo - 'a' + 'A');

        TramaBase* trama = NULL;

        if (tipo == 'L') {
            char c = normalize_char(t1);
            if (c == '\0') {
                printf("Trama inválida: [%s]\n", raw);
                continue;
            }
            trama = new TramaLoad(c);
            log_mensaje_prefix(raw);
            trama->procesar(&carga, &rotor);
            printf(" Mensaje: ");
            carga.imprimirMensaje();
            delete trama;
        } else if (tipo == 'M') {
            int d = 0;
            if (t1) d = atoi(t1);
            trama = new TramaMap(d);
            log_mensaje_prefix(raw);
            trama->procesar(&carga, &rotor);
            if (d >= 0) {
                // Informativo: nuevo mapeo de 'A'
                printf(" (Ahora 'A' se mapea a '%c')\n", rotor.getMapeo('A'));
            } else {
                printf(" (Ahora 'A' se mapea a '%c')\n", rotor.getMapeo('A'));
            }
            delete trama;
        } else {
            printf("Trama inválida: [%s]\n", raw);
        }
    }

    printf("\n---\nFlujo de datos terminado.\n");
    carga.imprimirMensaje();
    printf("---\nLiberando memoria... Sistema apagado.\n");

    if (fin) fclose(fin);
    if (usar_serial) sp.close();
    return 0;
}
