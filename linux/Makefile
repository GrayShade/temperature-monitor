CFLAGS = -DNDEBUG -O2 -march=native -pipe -fwhole-program -fvisibility=hidden -std=c++11 -Wall -s -flto -I/usr/include/dbus-c++-1/ -pthread -Ibuild/
LDFLAGS = -ldbus-c++-1

#BUILDDIR = $(abspath $(CURDIR)/build)
BUILDDIR = build

all: $(BUILDDIR)/read-temperature $(BUILDDIR)/dbus-read $(BUILDDIR)/read-standalone

glue: temperature-monitor-introspect.xml
	mkdir -p $(BUILDDIR)
	dbusxx-xml2cpp temperature-monitor-introspect.xml --adaptor=$(BUILDDIR)/temperature-monitor-server-glue.h --proxy=$(BUILDDIR)/temperature-monitor-client-glue.h

$(BUILDDIR)/temperature-monitor-server-glue.h: glue

$(BUILDDIR)/temperature-monitor-client-glue.h: glue

$(BUILDDIR)/read-temperature: read-temperature.cpp temperature-monitor-server.h sensor.h sensor.cpp paths.h paths.cpp $(BUILDDIR)/temperature-monitor-server-glue.h
	$(CXX) -o $@ read-temperature.cpp sensor.cpp paths.cpp $(CFLAGS) $(LDFLAGS)

$(BUILDDIR)/dbus-read: dbus-read.cpp temperature-monitor-client.h paths.h paths.cpp $(BUILDDIR)/temperature-monitor-client-glue.h
	$(CXX) -o $@ dbus-read.cpp paths.cpp $(CFLAGS) $(LDFLAGS)

$(BUILDDIR)/read-standalone: read-standalone.cpp
	$(CXX) -o $@ read-standalone.cpp $(CFLAGS) $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR)

