#include <WProgram.h>
#include <LibHumidity.h>
#include <Snooze.h>

extern "C" int __attribute__ ((noinline)) main(void)
{
    pinMode(20, OUTPUT);
    digitalWriteFast(20, LOW);
    pinMode(21, OUTPUT);
    digitalWriteFast(21, HIGH);

    LibHumidity humidity(eSensorHTU21, I2C_PINS_18_19, I2C_RATE_400);

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
        Snooze.idle();
    }
}
