#include <WProgram.h>
#include <LibHumidity.h>
#include <i2c_t3.h>

extern "C" int __attribute__ ((noinline)) main(void)
{
    pinMode(15, OUTPUT);
    digitalWriteFast(15, LOW);
    pinMode(14, OUTPUT);
    digitalWriteFast(14, HIGH);

    LibHumidity humidity(eSensorHTU21, I2C_PINS_16_17, I2C_RATE_400);

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

