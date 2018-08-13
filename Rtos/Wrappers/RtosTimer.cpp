/* Custom header includes --------------------------------------------------- */

#include "FreeRTOS.h"
#include "System.hpp"
#include "DefaultHandler.hpp"
#include "RtosTimer.hpp"


/* Private functions -------------------------------------------------------- */

static void FreeRtosTimerCallback(TimerHandle_t xTimer)
{
    void* pTimerId = pvTimerGetTimerID(xTimer);

    ITimer* timer = reinterpret_cast<ITimer*>(pTimerId);

    if(nullptr == timer)
    {
        FATAL_ERROR();
    }

    timer->TimerCallback();
}

/* Public class functions --------------------------------------------------- */

/**
 * @brief Create timer
 *
 * @param [in] pcTimerName
 *  Character array of timer name
 * @param [in] timerPeriodInTicks
 *  Timer period in ticks - 1 tick is 1 ms
 */
void RtosTimer::CreateTimer(const char * const pcTimerName,
        uint32_t timerPeriodInTicks)
{
    m_Timer = xTimerCreateStatic(
            pcTimerName,
            timerPeriodInTicks,
            pdTRUE,
            this,
            FreeRtosTimerCallback,
            &m_TimerBuffer);

    System_n::Assert(m_Timer);
}

/**
 * @brief Start timer
 */
bool RtosTimer::StartTimer()
{
    System_n::Assert(m_Timer);

    BaseType_t result = xTimerStart(m_Timer, 0);

    if (pdTRUE != result)
    {
        FATAL_ERROR();
    }

    return true;
}

/**
 * @brief Stop timer
 */
bool RtosTimer::StopTimer()
{
    System_n::Assert(m_Timer);

    BaseType_t result = xTimerStop(m_Timer, 0);

    if (pdTRUE != result)
    {
        FATAL_ERROR();
    }

    return true;
}
