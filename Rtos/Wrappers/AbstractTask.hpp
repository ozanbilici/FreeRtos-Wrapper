/* Include guard start ------------------------------------------------------ */

#ifndef TASK_BASE_HPP
#define TASK_BASE_HPP


/* System header includes --------------------------------------------------- */

#include <cstdint>


/* RTOS header includes ----------------------------------------------------- */

#include "FreeRTOS.h"
#include "task.h"



/* Custom header includes --------------------------------------------------- */

#include "ITask.hpp"
#include "System.hpp"
#include "EventGroup.hpp"
#include "Logger.hpp"


/* Abstract class definitions ----------------------------------------------- */

class AbstractTask : public ITask
{
public:
    AbstractTask() :
        m_TaskHandle(nullptr),
        m_TaskEventBit(0),
        m_pWatchdogEventGroup(nullptr)
    { }

    virtual ~AbstractTask() = default;

    void SetTaskHandle(TaskHandle_t taskHandle);
    void SetTaskName(const char* const taskName);

    void SetTaskEventBit(uint32_t eventBit);
    void RegisterWatchdog(IEventGroup* const pEventGroup);
    void NotifyWatchdog();

    IEventGroup* GetWatchdog();

    void SuspendTask();
    void ResumeTask();

protected:
    Logger m_Logger;

private:
    TaskHandle_t m_TaskHandle;

    uint32_t m_TaskEventBit;
    IEventGroup* m_pWatchdogEventGroup;
};


/* Include guard end -------------------------------------------------------- */

#endif
