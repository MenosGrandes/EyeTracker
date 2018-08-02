#include <time.h>

class Clock
{
    public :
        double getTime() const
        {
            struct timespec t;
            clock_gettime(CLOCK_MONOTONIC,  &t);
            return (t.tv_sec * 1000) + (t.tv_nsec * 1e-6);
        }



    private :

        double _avgdur = 0;
        double _fpsstart = 0;
        double _avgfps = 0;
        double _fps1sec = 0;

        double avgdur(double newdur)
        {
            _avgdur = 0.98 * _avgdur + 0.02 * newdur;
            return _avgdur;
        }

        double avgfps()
        {
            if (getTime() - _fpsstart > 1000)
            {
                _fpsstart = getTime();
                _avgfps = 0.7 * _avgfps + 0.3 * _fps1sec;
                _fps1sec = 0;
            }

            _fps1sec++;
            return _avgfps;
        }
};

