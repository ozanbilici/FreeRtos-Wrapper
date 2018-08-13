/* Include guard start ------------------------------------------------------ */

#ifndef ITASK_HPP
#define ITASK_HPP


/* Interface class definitions ---------------------------------------------- */

class ITask
{
public:
    /**
     * @brief Constructor
     */
    ITask() = default;

    /**
     * @brief Destructor
     */
    virtual ~ITask() = default;

    /**
     * @brief Open task
     */
    virtual void Open()
    {
        // Do nothing
    }

    /**
     * @brief Close task
     */
    virtual void Close()
    {
        // Do nothing
    }

    /**
     * @brief Suspend task
     */
    virtual void Suspend()
    {
        // Do nothing
    }

    /**
     * @brief Resume task
     */
    virtual void Resume()
    {
        // Do nothing
    }

    /**
     * @brief Initialize task
     */
    virtual void Initialize()
    {
        // Do nothing
    }

    /**
     * @brief Run task
     *
     * @note Every task must be run periodically, that's why they must implement Run()
     */
    virtual void Run() = 0;
};

/* Include guard end -------------------------------------------------------- */

#endif
