/* Include guard start ------------------------------------------------------ */

#ifndef QUEUE_HPP
#define QUEUE_HPP


/* RTOS header includes ----------------------------------------------------- */

#include "FreeRTOS.h"
#include "queue.h"


/* Custom header includes --------------------------------------------------- */

#include "System.hpp"
#include "IQueue.hpp"


/* Class declarations ------------------------------------------------------- */

class Queue : public IQueue
{
public:
    Queue() :
        m_QueueHandle(nullptr)
    { }

    void CreateQueue(uint8_t* pQueueStorageArea, size_t queueSize, size_t itemSize) override;

    bool SendFromISR(const void* data, bool taskWoken, bool fatalError = false) override;
    bool Send(const void* data, TickType_t timeout, bool fatalError = false) override;
    bool Receive(void* data, TickType_t timeout) override;

    void Reset() override;

private:
    StaticQueue_t m_StaticQueue;
    QueueHandle_t m_QueueHandle;
};


/* Include guard end -------------------------------------------------------- */

#endif
