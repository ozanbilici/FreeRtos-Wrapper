/* Include guard start ------------------------------------------------------ */

#ifndef MUTEX_HPP
#define MUTEX_HPP


/* RTOS header includes ----------------------------------------------------- */

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"


/* Custom header includes --------------------------------------------------- */

#include "IMutex.hpp"


/* Class declarations ------------------------------------------------------- */

class Mutex : public IMutex
{
public:
    Mutex() :
        m_MutexHandle(nullptr)
    {}

    void Create() override;

    bool GiveFromISR(bool taskWoken) override;
    bool Give() override;

    bool Take(uint32_t timeout) override;

private:
    StaticSemaphore_t m_StaticMutex;
    SemaphoreHandle_t m_MutexHandle;
};


/* Include guard end -------------------------------------------------------- */

#endif
