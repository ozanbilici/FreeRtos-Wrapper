/* Include guard start ------------------------------------------------------ */

#ifndef EVENT_GROUP_HPP
#define EVENT_GROUP_HPP


/* RTOS header includes ----------------------------------------------------- */

#include "FreeRTOS.h"
#include "event_groups.h"


/* Custom header includes --------------------------------------------------- */

#include "System.hpp"
#include "DefaultHandler.hpp"
#include "IEventGroup.hpp"


/* Class declarations ------------------------------------------------------- */

class EventGroup : public IEventGroup
{
public:
    EventGroup() :
        m_pEventGroup(nullptr)
    { }

    void CreateEventGroup() override;

    void SetEventBits(const uint32_t bits) override;
    void SetEventBitsFromISR(const uint32_t bits, bool taskWoken) override;

    uint32_t GetEventBits() override;
    uint32_t GetEventBitsFromISR() override;
    uint32_t ClearEventBits(const uint32_t bits) override;
    uint32_t WaitEventGroupBits(const uint32_t bits, bool allBits, uint32_t waitTime) override;

private:
    StaticEventGroup_t m_EventGroupHoldingReg;
    EventGroupHandle_t m_pEventGroup;
};


/* Include guard end -------------------------------------------------------- */

#endif
