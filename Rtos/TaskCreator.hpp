/* Include guard start ------------------------------------------------------ */

#ifndef TASK_CREATOR_HPP
#define TASK_CREATOR_HPP


/* RTOS header includes ----------------------------------------------------- */

#include "FreeRTOS.h"
#include "task.h"


/* Custom header includes --------------------------------------------------- */

#include "System.hpp"
#include "IEventGroup.hpp"


/* Template class definitions ----------------------------------------------- */

template<class TTask, std::size_t TStackSize>
class TaskCreator
{
public:
    /**
     * @brief Constructor
     */
    TaskCreator() :
        m_TaskHandle(nullptr)
    { }

    /**
     * @brief Default destructor
     */
    virtual ~TaskCreator() = default;

    /**
     * @brief Initialization for queues, semaphores etc.
     */
    void Initialize()
    {
        s_Task.Initialize();
    }

    /**
     * @brief Open the necessary things inside the Task
     */
    void Open()
    {
        s_Task.Open();
    }

    /**
     * @brief Following function will help to wrap "create task" method in RTOS.
     *
     * @param [in] taskName
     *  Char array task name
     * @param [in] priority
     *  Priority level of the task
     */
    void CreateTask(const char* const taskName, UBaseType_t priority)
    {
        // Create Tasks
        m_TaskHandle = xTaskCreateStatic(this->Run,
                taskName,
                TStackSize,
                nullptr,
                priority,
                &m_TaskStack[0],
                &m_TaskBuffer);

        System_n::Assert(m_TaskHandle);

        s_Task.SetTaskHandle(m_TaskHandle);
        s_Task.SetTaskName(taskName);
    }

    /**
     * @brief Register watchdog timer for task
     *
     * @param [in] pEventGroup
     *  Pointer to event group that is registered as watchdog
     * @param [in] eventBit
     *  Unique event bit for each task
     */
    void RegisterWatchdog(IEventGroup* pEventGroup, uint32_t eventBit)
    {
        s_Task.SetTaskEventBit(eventBit);
        s_Task.RegisterWatchdog(pEventGroup);
    }

    /**
     * @brief Following function will be the "task" method in RTOS.
     *
     * @param [in] pvParameters
     *  Pointer to FreeRtos parameters
     */
    __attribute__((noreturn))
    static void Run(__attribute__((unused)) void* pvParameters)
    {
        for(;;)
        {
            s_Task.Run();

            s_Task.NotifyWatchdog();
        }
    }

    /**
     * @brief Suspend Task
     *
     * This function call will suspend the task, and set its state is suspended
     */
    void CloseTask()
    {
        vTaskSuspend(m_TaskHandle);
        s_Task.Close();
    }

    /**
     * @brief Suspend Task
     *
     * This function call will suspend the task, and set its state is suspended
     */
    void SuspendTask()
    {
        s_Task.Suspend();
        vTaskSuspend(m_TaskHandle);
    }

    /**
     * @brief Resume Task
     *
     * This function call will resume the task, and set its state into normal task state
     */
    void ResumeTask()
    {
        vTaskResume(m_TaskHandle);
        s_Task.Resume();
    }

private:
    StackType_t m_TaskStack[TStackSize];
    StaticTask_t m_TaskBuffer;
    TaskHandle_t m_TaskHandle;

    static TTask s_Task;
};


/* Private static class variables ------------------------------------------- */

template<class TTask, uint32_t TStackSize>
TTask TaskCreator<TTask, TStackSize>::s_Task;


/* Include guard end -------------------------------------------------------- */

#endif

