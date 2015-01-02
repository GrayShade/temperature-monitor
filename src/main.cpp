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

    while (true)
    {
        if (Serial.available() > 0)
        {
            int cmd = Serial.read();

            switch (cmd)
            {
                case 'M':
                {
                    float hum = humidity.GetHumidity();
                    float temp = humidity.GetTemperatureC();

                    Serial.print(hum);
                    Serial.print(' ');
                    Serial.println(temp);
                    break;
                }
                default:
                {
                    Serial.println("Unknown command");
                    break;
                }
            }
        }

        yield();
    }
}

