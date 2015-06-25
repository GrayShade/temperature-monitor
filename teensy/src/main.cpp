#include <WProgram.h>
#include <LibHumidity.h>
#include <i2c_t3.h>
#include <Snooze.h>


#include <SPI.h>
#include <ILI9341_t3.h>

#define TFT_DC  9
#define TFT_CS 10

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

#define BACKGROUND ILI9341_BLUE

static float HueToRgb(float p, float q, float t)
{
    if (t < 0.0f) t += 1.0f;
    if (t > 1.0f) t -= 1.0f;
    if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
    if (t < 1.0f / 2.0f) return q;
    if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
    return p;
}

static uint16_t HslToRgb(float h, float s, float l)
{
    float r, g, b;

    if (s == 0.0f)
        r = g = b = l;

    else
    {
        float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
        float p = 2.0f * l - q;
        r = HueToRgb(p, q, h + 1.0f / 3.0f);
        g = HueToRgb(p, q, h);
        b = HueToRgb(p, q, h - 1.0f / 3.0f);
    }

    return ILI9341_t3::color565(r * 255, g * 255, b * 255);
}

static void mandelbrot()
{
    tft.setRotation(3);
    tft.setAddrWindow(0, 0, 320, 240);

    for (int r = 0; r < 240; r++)
    {
        for (int c = 0; c < 320; c++)
        {
            float x0 = c / 320.0f * 3.5f - 2.5f;
            float y0 = r / 240.0f * 2.0f - 1.0f;
            float x = 0.0f;
            float y = 0.0f;
	    int iteration = 0;
	    int max_iteration = 16;
	    while (iteration < max_iteration)
	    {
	        float xs = x * x;
		float ys = y * y;
                if (xs + ys > 4)
		    break;
		
	        float xtemp = xs - ys + x0;
		y = 2 * x * y + y0;

		x = xtemp;
		iteration++;
	    }

	    if (iteration < max_iteration)
	    {/*
	        float zn = x * x + y * y;
		float nu = log(log(zn) / 2.0f / log(2)) / log(2);
		float it = iteration + 1 - nu;
*/
                /*
		float color1 = it * 1.0f / max_iteration;
		float color2 = color1 + 1.0f / max_iteration;

		float t = fmod(it, 1.0f);
		float color = (1.0f - t) * color1 + t * color2;
		*/
		/*
		int r = color * 255;
	        int g = color * 255;
	        int b = color * 255;
	        tft.pushColor(ILI9341_t3::color565(r, g, b));
                */
	        //tft.pushColor(HslToRgb(0.55f + 1 * it/max_iteration, 0.6f, 0.5f));
	        tft.pushColor(HslToRgb(1.0f * iteration/max_iteration, 0.6f, 0.5f));

            }
	    else
	        tft.pushColor(ILI9341_t3::color565(0, 0, 0));
        }
    }
}

extern "C" int __attribute__ ((noinline)) main(void)
{
    pinMode(20, OUTPUT);
    digitalWriteFast(20, LOW);
    pinMode(21, OUTPUT);
    digitalWriteFast(21, HIGH);

    LibHumidity humidity(eSensorHTU21, I2C_PINS_18_19, I2C_RATE_400);

    Serial.begin(9600);
    humidity.ResetSensor();

    tft.begin();
    tft.fillScreen(BACKGROUND);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.println("Hello");

    mandelbrot();
    int line = 0;
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

        float temp = humidity.GetTemperatureC();
        //tft.println(temp);
        if (line++ == 12) {
            //tft.fillScreen(BACKGROUND);
            tft.setCursor(0, 0);
            line = 0;
        }

	delay(5000);

        yield();
        Snooze.idle();
    }
}

