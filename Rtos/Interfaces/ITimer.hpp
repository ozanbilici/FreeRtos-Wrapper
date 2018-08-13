/* Include guard start ------------------------------------------------------ */

#ifndef ITIMER_HPP
#define ITIMER_HPP


/* System header includes --------------------------------------------------- */

#include <cstdint>


/* Interface class definitions ---------------------------------------------- */

class ITimer
{
public:
    ITimer() = default;
    virtual ~ITimer() = default;

    virtual void CreateTimer(const char * const pcTimerName,
            uint32_t timerPeriodInTicks) = 0;

    virtual bool StartTimer();
    virtual bool StopTimer();

    virtual void TimerCallback() = 0;
};


/* Include guard end -------------------------------------------------------- */

#endif
