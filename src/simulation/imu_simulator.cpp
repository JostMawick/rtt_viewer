#include "imu_simulator.hpp"
#include <cmath>
#include <array>

typedef struct
{
    double time;
    std::array<double, 3> accel;
    std::array<double, 3> gyro;
} ImuData;

class ImuSimulation
{
protected:
    ImuData m_imu_data;

public:
    ImuSimulation() : m_imu_data{0.0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}} {};
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
    SinusSimulation() : m_amplitude(0.0), m_frequency(0.0), m_chanel(0) {};
    ~SinusSimulation() = default;
    void set_parameter(double amp, double freq, int ch)
    {
        m_amplitude = amp;
        m_frequency = freq;
        m_chanel = ch;
    }
    void update(double time)
    {
        m_imu_data.time = time;

        m_imu_data.accel[m_chanel] = m_amplitude * std::sin(2 * M_PI * m_frequency * time);
    }
};