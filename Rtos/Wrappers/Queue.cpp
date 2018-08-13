/* Custom header includes --------------------------------------------------- */

#include "Queue.hpp"


/* Public class functions --------------------------------------------------- */

/**
 * @brief Create queue
 *
 * @param [in] pQueueStorageArea
 *  Pointer to static queue storage that is used for queue elements
 * @param [in] queueSize
 *  Size of the one element of the queue
 * @param [in] itemSize
 *  Size of the how many elements in the queue
 */
void Queue::CreateQueue(uint8_t* pQueueStorageArea, size_t queueSize, size_t itemSize)
{
    System_n::Assert(pQueueStorageArea);

    m_QueueHandle = xQueueCreateStatic(
            queueSize,
            itemSize,
            pQueueStorageArea,
            &m_StaticQueue);


    System_n::Assert(m_QueueHandle);
}

/**
 * @brief Send to the queue from Interrupt service routine
 *
 * @param [in] pData
 *  Pointer to the data that is going to be written
 * @param [in] taskWoken
 *  Task woken
 * @param [in] fatalError
 *  In failure it will cause the fatal error
 * @return
 */
bool Queue::SendFromISR(const void *pData, bool taskWoken, bool fatalError)
{
    System_n::Assert(m_QueueHandle);
    System_n::Assert(pData);

    BaseType_t xHigherPriorityTaskWoken = (taskWoken) ? pdTRUE : pdFALSE;

    BaseType_t result = xQueueSendFromISR(m_QueueHandle, pData, &xHigherPriorityTaskWoken);

    if(result == pdTRUE)
    {
        return true;
    }

    if(fatalError)
    {
        FATAL_ERROR();
    }

    return false;
}

/**
 * @brief Send to queue
 *
 * @param [in] pData
 *  Pointer to the data that is going to be written
 * @param [in] timeout
 *  Timeout value
 * @return
 *  Returns true in success, otherwise false
 */
bool Queue::Send(const void* pData, TickType_t timeout, bool fatalError)
{
    System_n::Assert(m_QueueHandle);
    System_n::Assert(pData);

    BaseType_t result = xQueueSend(m_QueueHandle, pData, timeout);

    if(result == pdTRUE)
    {
        return true;
    }

    if(fatalError)
    {
        FATAL_ERROR();
    }

    return false;
}

/**
 * @brief Receive from queue
 *
 * @param [in] pData
 *  Pointer to the data that is going to be written
 * @param [in] timeout
 *  Timeout value
 * @return
 *  Returns true in success, otherwise false
 */
bool Queue::Receive(void* pData, TickType_t timeout)
{
    System_n::Assert(m_QueueHandle);
    System_n::Assert(pData);

    BaseType_t result = xQueueReceive(m_QueueHandle, pData, timeout);

    if(result == pdTRUE)
    {
        return true;
    }

    return false;
}

/**
 * @brief Reset the queue
 */
void Queue::Reset()
{
    System_n::Assert(m_QueueHandle);

    xQueueReset(m_QueueHandle);
}
