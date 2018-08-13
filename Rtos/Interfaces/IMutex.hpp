/* Include guard start ------------------------------------------------------ */

#ifndef IMUTEX_HPP
#define IMUTEX_HPP


/* System header includes --------------------------------------------------- */

#include <cstdint>


/* Interrupt class definitions ---------------------------------------------- */

class IMutex
{
public:
    IMutex() = default;
    virtual ~IMutex() = default;

    virtual void Create() = 0;

    virtual bool GiveFromISR(bool taskWoken) = 0;
    virtual bool Give() = 0;

    virtual bool Take(uint32_t timeout) = 0;
};


/* Include guard end -------------------------------------------------------- */

#endif
