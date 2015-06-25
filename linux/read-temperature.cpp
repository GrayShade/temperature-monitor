#include <sys/types.h>
#include <sys/stat.h>

#include "temperature-monitor-server.h"
#include "paths.h"

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>

EchoServer::EchoServer(DBus::Connection &connection, sensor &s)
    : DBus::ObjectAdaptor(connection, ECHO_SERVER_PATH), s(s)
{
}

void EchoServer::ReadTemperature(double &temperature, double &humidity)
{
    float temp;
    float hum;

    s.take_reading(temp, hum);

    temperature = temp;
    humidity = hum;
}

DBus::BusDispatcher dispatcher;

void niam(int sig)
{
    dispatcher.leave();
}

static const char device[] = "/dev/ttyACM0";

int main()
{
    signal(SIGTERM, niam);
    signal(SIGINT, niam);

    DBus::default_dispatcher = &dispatcher;

    DBus::Connection conn = DBus::Connection::SystemBus();
    conn.request_name(ECHO_SERVER_NAME);

    sensor s(device);
    EchoServer server(conn, s);

    dispatcher.enter();
}

