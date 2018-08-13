/* Custom header includes --------------------------------------------------- */

#include "AbstractTask.hpp"


/* Public class functions --------------------------------------------------- */

/**
 * @brief Set task handle
 *
 * @param [in] taskHandle
 *  Unique task handle number
 */
void AbstractTask::SetTaskHandle(TaskHandle_t taskHandle)
{
    m_TaskHandle = taskHandle;
}

/**
 * @brief Set task name
 *
 * @param [in] taskname
 *  Task Name
 */
void AbstractTask::SetTaskName(const char* const taskName)
{
    m_Logger.SetPrefix(taskName);
}

/**
 * @brief Following function will help to wrap "suspend the task" method in RTOS.
 */
void AbstractTask::SuspendTask()
{
    vTaskSuspend(m_TaskHandle);
}

/**
 * @brief Following function will help to wrap "resume the task" method in RTOS.
 */
void AbstractTask::ResumeTask()
{
    vTaskResume(m_TaskHandle);
}


/**
 * @brief Set Task Event Bit
 *
 * Every task should have unique event id bit for watchdog timer.
 *
 * @param [in] eventBit
 *  Unique event bit for task
 */
void AbstractTask::SetTaskEventBit(uint32_t eventBit)
{
    m_TaskEventBit = eventBit;
}

/**
 * @brief Register watchdog event group
 *
 * @param [in] pEventGroup
 *  Pointer to watchdog event group
 */
void AbstractTask::RegisterWatchdog(IEventGroup* const pEventGroup)
{
    m_pWatchdogEventGroup = pEventGroup;
}

/**
 * @brief Notify watchdog
 *
 * Task should notify the watchdog periodically in order to prevent
 * system reset.
 */
void AbstractTask::NotifyWatchdog()
{
    if(nullptr != m_pWatchdogEventGroup)
    {
        m_pWatchdogEventGroup->SetEventBits(m_TaskEventBit);
    }
}

/**
 * @brief Get watchdog
 *
 * This function should be only used by Watchdog task in order to get watchdog event
 * group.
 *
 * @return
 *  Returns pointer to watchdog event group
 */
IEventGroup* AbstractTask::GetWatchdog()
{
    return m_pWatchdogEventGroup;
}
