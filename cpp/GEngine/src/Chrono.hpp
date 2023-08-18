#ifndef CHRONO_HPP
#define CHRONO_HPP

#include <chrono>
using namespace std::chrono;

namespace GEngine
{
    class Chrono
    {
    private:
        steady_clock::time_point lastTick;
        duration<float> deltaTime = duration<float>(0.0f);

        int frame = 0;
        int frameCount = 0;

    public:
        Chrono()
        {
            Reset();
        }

        inline void Reset()
        {
            lastTick = steady_clock::now();
        }

        double DeltaTime()
        {
            return duration_cast<nanoseconds>(steady_clock::now() - lastTick).count() / 1000000000.0;
        }

        int FramePerSecond()
        {
            deltaTime += (steady_clock::now() - lastTick);
            if ((steady_clock::now() - lastTick) >= duration<float>(1.0f))
            {
                Reset();
                frameCount = frame;
                frame = 0;
            }
            frame++;
            return frameCount;
        }
    };
}

#endif