/* Include guard start ------------------------------------------------------ */

#ifndef RTOS_TIMER_HPP
#define RTOS_TIMER_HPP


/* Custom header includes --------------------------------------------------- */

#include "ITimer.hpp"
#include "timers.h"

/* Class definitions -------------------------------------------------------- */

class RtosTimer : public ITimer
{
public:
    RtosTimer() :
        m_Timer(nullptr)
    { }

    virtual ~RtosTimer() = default;

    void CreateTimer(const char * const pcTimerName,
            uint32_t timerPeriodInTicks) override;

    bool StopTimer() override;
    bool StartTimer() override;

private:
    StaticTimer_t m_TimerBuffer;
    TimerHandle_t m_Timer;
};

/* Include guard end -------------------------------------------------------- */

#endif
