/* Custom header includes --------------------------------------------------- */

#include "System.hpp"
#include "Semaphore.hpp"


/* Public class functions --------------------------------------------------- */

/**
 * @brief Create binary semaphore
 */
void Semaphore::Create()
{
    m_SemaphoreHandle = xSemaphoreCreateBinaryStatic(&m_StaticSemaphore);

    System_n::Assert(m_SemaphoreHandle);
}

/**
 * @brief Give semaphore from interrupt service routine
 *
 * @param [in] taskWoken
 *  Task woken value
 * @return
 *  Returns true in success, otherwise false
 */
bool Semaphore::GiveFromISR(bool taskWoken)
{
    System_n::Assert(m_SemaphoreHandle);

    BaseType_t xHigherPriorityTaskWoken = (taskWoken) ? pdTRUE : pdFALSE;

    BaseType_t result = xSemaphoreGiveFromISR(m_SemaphoreHandle, &xHigherPriorityTaskWoken);

    if(!taskWoken)
    {
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    if(result == pdTRUE)
    {
        return true;
    }

    return false;
}

/**
 * @brief Give semaphore
 *
 * @return
 *  Returns true in success, otherwise false
 */
bool Semaphore::Give()
{
    System_n::Assert(m_SemaphoreHandle);

    BaseType_t result = xSemaphoreGive(m_SemaphoreHandle);

    if(pdTRUE == result)
    {
        return true;
    }

    return false;
}

/**
 * @brief Take semaphore
 *
 * @param [in] timeout
 *  Try to take it till timeout occurs
 * @return
 *  Returns true in success, otherwise false
 */
bool Semaphore::Take(TickType_t timeout)
{
    System_n::Assert(m_SemaphoreHandle);

    BaseType_t result = xSemaphoreTake(m_SemaphoreHandle, timeout);

    if(pdTRUE == result)
    {
        return true;
    }

    return false;
}

