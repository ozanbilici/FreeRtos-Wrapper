/* Include guard start ------------------------------------------------------ */

#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP


/* RTOS header includes ----------------------------------------------------- */

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"


/* Custom header includes --------------------------------------------------- */

#include "ISemaphore.hpp"


/* Class declarations ------------------------------------------------------- */

class Semaphore : public ISemaphore
{
public:
    Semaphore() :
        m_SemaphoreHandle(nullptr)
    {}

    void Create() override;

    bool GiveFromISR(bool taskWoken) override;
    bool Give() override;

    bool Take(uint32_t timeout) override;

private:
    StaticSemaphore_t m_StaticSemaphore;
    SemaphoreHandle_t m_SemaphoreHandle;
};


/* Include guard end -------------------------------------------------------- */

#endif
