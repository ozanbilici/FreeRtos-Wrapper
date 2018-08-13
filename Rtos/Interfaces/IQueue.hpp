/* Include guard start ------------------------------------------------------ */

#ifndef IQUEUE_HPP
#define IQUEUE_HPP


/* System header includes --------------------------------------------------- */

#include <cstdint>


/* Interface class definitions ---------------------------------------------- */

class IQueue
{
public:
    IQueue() = default;
    virtual ~IQueue() = default;

    virtual void CreateQueue(uint8_t* pQueueStorageArea, size_t queueSize, size_t itemSize) = 0;

    virtual bool SendFromISR(const void* data, bool taskWoken, bool fatalError = false) = 0;
    virtual bool Send(const void* data, uint32_t timeout, bool fatalError = false) = 0;
    virtual bool Receive(void* data, uint32_t timeout) = 0;
    virtual void Reset() = 0;
};


/* Include guard end -------------------------------------------------------- */

#endif
