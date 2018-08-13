/* Include guard start ------------------------------------------------------ */

#ifndef RTOS_HPP
#define RTOS_HPP


/* System header includes --------------------------------------------------- */

#include <cstdint>


/* Class definitions -------------------------------------------------------- */

class Rtos
{
public:
    /**
     * @brief Mcu register structure for analysis HardFaultError
     */
    struct Registers
    {
        uint32_t r0;
        uint32_t r1;
        uint32_t r2;
        uint32_t r3;
        uint32_t r12;
        uint32_t lr;
        uint32_t pc;
        uint32_t psr;
    };
public:
    Rtos() = default;

    static void EnterCriticalMode();
    static void ExitCriticalMode();
    static void Sleep(uint32_t delay);

    static void Run();

    static uint32_t GetSystemTime();
    static Registers GetRegistersFromStack();

private:
    static uint32_t* GetLastRunningTaskStackAddress();
};


/* Include guard end -------------------------------------------------------- */

#endif
