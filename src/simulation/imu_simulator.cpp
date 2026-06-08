typedef struct
{
    double time;
    double accel[3];
    double gyro[3];
} ImuData;

class ImuSimulation
{
protected:
    ImuData m_imu_data;

public:
    ImuSimulation() = default;
    ~ImuSimulation() = default;
    ImuData getImuData() const
    {
        return m_imu_data;
    }
};

class SinusSimulation : public ImuSimulation
{
private:
    double m_amplitude;
    double m_frequency;
    int m_chanel;

public:
    SinusSimulation() = default;
    ~SinusSimulation() = default;
    void set_parameter(double amp, double freq, int ch)
    {
        m_amplitude = amp;
        m_frequency = freq;
        m_chanel = ch;
    }
};