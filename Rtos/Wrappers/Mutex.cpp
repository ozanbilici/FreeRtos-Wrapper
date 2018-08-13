/* Custom header includes --------------------------------------------------- */

#include "System.hpp"
#include "Mutex.hpp"


/* Public class functions --------------------------------------------------- */

/**
 * @brief Create mutex
 */
void Mutex::Create()
{
    m_MutexHandle = xSemaphoreCreateMutexStatic(&m_StaticMutex);

    System_n::Assert(m_MutexHandle);
}

/**
 * @brief Give mutex from interrupt service routine
 *
 * @param [in] taskWoken
 *  Task woken value
 * @return
 *  Returns true in success, otherwise false
 */
bool Mutex::GiveFromISR(bool taskWoken)
{
    System_n::Assert(m_MutexHandle);

    BaseType_t xHigherPriorityTaskWoken = (taskWoken) ? pdTRUE : pdFALSE;

    BaseType_t result = xSemaphoreGiveFromISR(m_MutexHandle, &xHigherPriorityTaskWoken);

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
 * @brief Give mutex
 *
 * @return
 *  Returns true in success, otherwise false
 */
bool Mutex::Give()
{
    System_n::Assert(m_MutexHandle);

    BaseType_t result = xSemaphoreGive(m_MutexHandle);

    if(pdTRUE == result)
    {
        return true;
    }

    return false;
}

/**
 * @brief Take mutex
 *
 * @param [in] timeout
 *  Try to take it till timeout occurs
 * @return
 *  Returns true in success, otherwise false
 */
bool Mutex::Take(TickType_t timeout)
{
    System_n::Assert(m_MutexHandle);

    BaseType_t result = xSemaphoreTake(m_MutexHandle, timeout);

    if(pdTRUE == result)
    {
        return true;
    }

    return false;
}

