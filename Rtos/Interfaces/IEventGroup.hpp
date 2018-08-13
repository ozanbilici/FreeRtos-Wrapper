/* Include guard start ------------------------------------------------------ */

#ifndef IEVENT_GROUP_HPP
#define IEVENT_GROUP_HPP


/* System header includes --------------------------------------------------- */

#include <cstdint>


/* Interface class definitions ---------------------------------------------- */

class IEventGroup
{
public:
    IEventGroup() = default;
    virtual ~IEventGroup() = default;

    virtual void CreateEventGroup() = 0;

    virtual void SetEventBits(const uint32_t bits) = 0;
    virtual void SetEventBitsFromISR(const uint32_t bits, bool taskWoken) = 0;

    virtual uint32_t GetEventBits() = 0;
    virtual uint32_t GetEventBitsFromISR() = 0;
    virtual uint32_t ClearEventBits(const uint32_t bits) = 0;
    virtual uint32_t WaitEventGroupBits(const uint32_t bits, bool allBits, uint32_t waitTime) = 0;
};


/* Include guard end -------------------------------------------------------- */

#endif
