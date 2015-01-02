CFLAGS = -DNDEBUG -O2 -march=native -pipe -fvisibility=hidden -std=c++11 -Wall
LDFLAGS = 

BUILDDIR = $(abspath $(CURDIR)/build)

SRC = read-temperature.cpp

all: $(BUILDDIR)/read-temperature

$(BUILDDIR)/read-temperature: $(SRC)
	$(CC) -o $@ $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(BUILDDIR)/read-temperature

