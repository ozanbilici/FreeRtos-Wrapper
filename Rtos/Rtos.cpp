/* RTOS header includes ----------------------------------------------------- */

#include "FreeRTOS.h"
#include "task.h"


/* Custom header includes --------------------------------------------------- */

#include "Rtos.hpp"


/* Public class functions --------------------------------------------------- */

/**
 * @brief Run task scheduler
 */
void Rtos::Run()
{
    vTaskStartScheduler();
}

/**
 * @brief Enter critical mode
 *
 * Critical mode will disable the interrupts.
 */
void Rtos::EnterCriticalMode()
{
    taskENTER_CRITICAL();
}

/**
 * @brief Exit critical mode
 *
 * Critical mode will disable the interrupts.
 */
void Rtos::ExitCriticalMode()
{
    taskEXIT_CRITICAL();
}

/**
 * @brief Delay the task
 *
 * @param [in] delay
 *  Delay in ms
 */
void Rtos::Sleep(uint32_t delay)
{
    vTaskDelay(delay / portTICK_PERIOD_MS);
}

/**
 * @brief Get system time
 *
 * @return
 *  Returns system time since task scheduler starts
 */
uint32_t Rtos::GetSystemTime()
{
    return xTaskGetTickCount();
}

/**
 * @brief Get registers from stack
 *
 * @param [in] pHardFaultStackAddress
 *  Pointer to last stack memory address
 */
Rtos::Registers Rtos::GetRegistersFromStack()
{
    Registers mcuRegister;

    uint32_t* pHardFaultStackAddress = GetLastRunningTaskStackAddress();

    if(pHardFaultStackAddress != nullptr)
    {
        mcuRegister.r0 = pHardFaultStackAddress[0];
        mcuRegister.r1 = pHardFaultStackAddress[1];
        mcuRegister.r2 = pHardFaultStackAddress[2];
        mcuRegister.r3 = pHardFaultStackAddress[3];

        mcuRegister.r12 = pHardFaultStackAddress[4];
        mcuRegister.lr = pHardFaultStackAddress[5];
        mcuRegister.pc = pHardFaultStackAddress[6];
        mcuRegister.psr = pHardFaultStackAddress[7];
    }

    return mcuRegister;

}


/* Private class functions -------------------------------------------------- */

/**
 * @brief Get last runnng task stack address for storing
 *
 * @return
 *  Returns last running task stack address
 */
uint32_t* Rtos::GetLastRunningTaskStackAddress()
{
    uint32_t* pHardFaultStackAddress = nullptr;

    asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
    );

    asm volatile ("LDR %0, [r0, #24]" : "=r" (*pHardFaultStackAddress));

    return pHardFaultStackAddress;
}
