#ifndef OBSERVER_H
#define OBSERVER_H

class Notice;

/**
 * @brief Abstract observer interface for receiving event notifications.
 */
class Observer
{
public:
    virtual ~Observer();

    /**
     * @brief Callback invoked by subjects to push state updates.
     * @param notice Broadcast notice object containing details.
     */
    virtual void update(const Notice& notice) = 0;
};

#endif