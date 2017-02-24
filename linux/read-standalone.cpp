#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>

int main()
{
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        perror("open");
        return errno;
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

    while (true) {
        char buf[256];
        buf[0] = 'M';
        ssize_t len = write(fd, buf, 1);
        if (len < 0) {
            perror("write");
            return errno;
        }

        len = read(fd, buf, sizeof(buf));
        if (len < 0) {
            perror("read");
            return errno;
        }

        ssize_t ret = write(1, buf, len);
        if (ret < 0) {
            perror("write");
            return errno;
        }

        sleep(60);
    }

    close(fd);
}

