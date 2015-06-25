#pragma once

#include <dbus-c++/dbus.h>

#include "temperature-monitor-server-glue.h"
#include "sensor.h"

class EchoServer
  : public ro::dend::TemperatureMonitor_adaptor,
  public DBus::IntrospectableAdaptor,
  public DBus::ObjectAdaptor
{
    sensor s;

public:

  EchoServer(DBus::Connection &connection, sensor &s);

  void ReadTemperature(double &temperature, double &humidity);
};

