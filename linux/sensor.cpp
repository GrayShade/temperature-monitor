#include <cstdio>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include "sensor.h"

sensor::sensor(const char *device)
{
    fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        perror("open");
    }

    if (fcntl(fd, F_SETFL, 0) < 0) {
        perror("fcntl");
    }

    termios options;
    tcgetattr(fd, &options);
    cfsetspeed(&options, B460800);
    cfmakeraw(&options);

    options.c_lflag &= ~NOFLSH;

    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CLOCAL | CREAD;

    options.c_iflag &= ~IMAXBEL;
    options.c_iflag |= IGNBRK;

    options.c_oflag &= ~ONLCR;

    tcsetattr(fd, TCSANOW, &options);

    tcflush(fd, TCIOFLUSH);
}

sensor::~sensor()
{
    close(fd);
}

void sensor::take_reading(float &temperature, float &humidity)
{
    char buf[256];
    buf[0] = 'M';
    ssize_t len = write(fd, buf, 1);
    if (len < 0) {
        perror("write");
        return;
    }

    len = read(fd, buf, sizeof(buf));
    if (len < 0) {
        perror("read");
        return;
    }

    sscanf(buf, "%f %f", &humidity, &temperature);
}

