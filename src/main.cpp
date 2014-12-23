#include "WProgram.h"

//#include <Wire.h>
#include <LibHumidity.h>

extern "C" int __attribute__ ((noinline)) main(void)
{
    LibHumidity humidity(eSensorHTU21);

    Serial.begin(9600);
    humidity.ResetSensor();
    delay(5000);

    while (true)
    {
        Serial.print("RH: ");
        Serial.print(humidity.GetHumidity());
        Serial.print(" Temp: ");
        Serial.println(humidity.GetTemperatureC());
        delay(2000);
    }
}

