#include "SerialPort.h"

#ifdef PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#endif

SerialPort::SerialPort() : handle(0) {}
SerialPort::~SerialPort() { close(); }

bool SerialPort::open(const char* device, int baud) {
#ifdef PLATFORM_WINDOWS
    HANDLE h = CreateFileA(device, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (h == INVALID_HANDLE_VALUE) return false;
    DCB dcb = {0};
    dcb.DCBlength = sizeof(DCB);
    if (!GetCommState(h, &dcb)) { CloseHandle(h); return false; }
    dcb.BaudRate = baud;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    if (!SetCommState(h, &dcb)) { CloseHandle(h); return false; }

    COMMTIMEOUTS t;
    t.ReadIntervalTimeout         = 50;
    t.ReadTotalTimeoutMultiplier  = 10;
    t.ReadTotalTimeoutConstant    = 50;
    t.WriteTotalTimeoutMultiplier = 10;
    t.WriteTotalTimeoutConstant   = 50;
    SetCommTimeouts(h, &t);

    handle = h;
    return true;
#else
    int fd = ::open(device, O_RDONLY | O_NOCTTY);
    if (fd < 0) return false;

    struct termios tio;
    if (tcgetattr(fd, &tio) != 0) { ::close(fd); return false; }

    cfmakeraw(&tio);
    cfsetispeed(&tio, B9600);
    cfsetospeed(&tio, B9600);
    tio.c_cflag |= (CLOCAL | CREAD);
    tio.c_cflag &= ~PARENB;
    tio.c_cflag &= ~CSTOPB;
    tio.c_cflag &= ~CSIZE;
    tio.c_cflag |= CS8;

    if (tcsetattr(fd, TCSANOW, &tio) != 0) { ::close(fd); return false; }

    handle = (void*)(long)fd;
    return true;
#endif
}

int SerialPort::readByte() {
#ifdef PLATFORM_WINDOWS
    if (!handle) return -1;
    DWORD read = 0;
    unsigned char ch;
    if (!ReadFile((HANDLE)handle, &ch, 1, &read, NULL) || read == 0) return -1;
    return (int)ch;
#else
    if (!handle) return -1;
    int fd = (int)(long)handle;
    unsigned char ch;
    int n = ::read(fd, &ch, 1);
    if (n <= 0) return -1;
    return (int)ch;
#endif
}

void SerialPort::close() {
#ifdef PLATFORM_WINDOWS
    if (handle) { CloseHandle((HANDLE)handle); handle = 0; }
#else
    if (handle) { ::close((int)(long)handle); handle = 0; }
#endif
}
