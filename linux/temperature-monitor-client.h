#pragma once

#include <dbus-c++/dbus.h>

#include "temperature-monitor-client-glue.h"

class EchoClient
  : public ro::dend::TemperatureMonitor_proxy,
  public DBus::IntrospectableProxy,
  public DBus::ObjectProxy
{
public:
  EchoClient(DBus::Connection &connection, const char *path, const char *name);
};

