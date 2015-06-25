class sensor
{
    int fd;

public:
    sensor(const char *device);
    ~sensor();

    void take_reading(float &temperature, float &humidity);
};

