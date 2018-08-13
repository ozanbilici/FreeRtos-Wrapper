/* Include guard start ------------------------------------------------------ */

#ifndef ISEMAPHORE_HPP
#define ISEMAPHORE_HPP


/* System header includes --------------------------------------------------- */

#include <cstdint>


/* Interrupt class definitions ---------------------------------------------- */

class ISemaphore
{
public:
    ISemaphore() = default;
    virtual ~ISemaphore() = default;

    virtual void Create() = 0;

    virtual bool GiveFromISR(bool taskWoken) = 0;
    virtual bool Give() = 0;

    virtual bool Take(uint32_t timeout) = 0;
};


/* Include guard end -------------------------------------------------------- */

#endif
