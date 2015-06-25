#include "temperature-monitor-client.h"
#include "paths.h"

#include <stdio.h>

EchoClient::EchoClient(DBus::Connection &connection, const char *path, const char *name)
    : DBus::ObjectProxy(connection, path, name)
{
}

int main()
{
    DBus::BusDispatcher dispatcher;
    DBus::default_dispatcher = &dispatcher;

    DBus::Connection conn = DBus::Connection::SystemBus();

    EchoClient client(conn, ECHO_SERVER_PATH, ECHO_SERVER_NAME);

    double temp, hum;
    client.ReadTemperature(temp, hum);

    printf("%.2lf %.2lf\n", temp, hum);
}
