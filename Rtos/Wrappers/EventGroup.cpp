/* Custom header includes --------------------------------------------------- */

#include "EventGroup.hpp"


/* Public class functions --------------------------------------------------- */

/**
 * @brief Create event group
 */
void EventGroup::CreateEventGroup()
{
    m_pEventGroup = xEventGroupCreateStatic(&m_EventGroupHoldingReg);

    System_n::Assert(m_pEventGroup);
}

/**
 * @brief Set event bits
 *
 * @param [in] bits
 *  Bits that are going to be set
 */
void EventGroup::SetEventBits(const uint32_t bits)
{
    xEventGroupSetBits(m_pEventGroup, bits);
}

/**
 * @brief Set event bits from interrupt service routine
 *
 * @param [in] bits
 *  Bits that are going to be set
 * @param taskWoken
 *  Task woken
 */
void EventGroup::SetEventBitsFromISR(const uint32_t bits, bool taskWoken)
{
    /*BaseType_t xHigherPriorityTaskWoken = (taskWoken) ? pdTRUE : pdFALSE;

    BaseType_t result = xEventGroupSetBitsFromISR(m_pEventGroup,
            bits,
            &xHigherPriorityTaskWoken);

    if (pdPASS != result)
    {
        DefaultHandler::FatalError();
    }*/
}

/**
 * @brief Get event bits
 *
 * @return
 *  Returns all bits
 */
uint32_t EventGroup::GetEventBits()
{
    return xEventGroupGetBits(m_pEventGroup);
}

/**
 * @brief Get event bits from interrupt service routine
 *
 * @return
 *  Returns all bits
 */
uint32_t EventGroup::GetEventBitsFromISR()
{
    return xEventGroupGetBitsFromISR(m_pEventGroup);
}

/**
 * @brief Clear event bits
 *
 * @param [in] bits
 * Bits that are going to be cleared
 * @return
 *  Returns all bits
 */
uint32_t EventGroup::ClearEventBits(const uint32_t bits)
{
    return xEventGroupClearBits(m_pEventGroup, bits);
}

/**
 * @brief Wait even group bits
 *
 * @param [in] bits
 *  Bits that are going to be waited to be set
 * @param [in] allBits
 *  Wait for all bits, or just one
 * @param [in] waitTime
 *  Time value for waiting
 * @return
 *  Returns all bits
 */
uint32_t EventGroup::WaitEventGroupBits(const uint32_t bits, bool allBits, uint32_t waitTime)
{
    return xEventGroupWaitBits(m_pEventGroup, bits, pdTRUE, (allBits) ? pdTRUE : pdFALSE, waitTime);
}
