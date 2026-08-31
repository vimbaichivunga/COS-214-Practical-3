#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;
class Notice;

/**
 * @brief Base subject managing dynamic observer registrations.
 */
class Subject
{
private:
    std::vector<Observer*> observers;

public:
    Subject();
    virtual ~Subject();

    /**
     * @brief Attaches an observer if it is not already registered.
     * @param observer Pointer to the observer instance.
     * @return True if attached, false if already present.
     */
    bool attach(Observer* observer);

    /**
     * @brief Detaches an observer if registered.
     * @param observer Pointer to the observer to remove.
     */
    void detach(Observer* observer);

    /**
     * @brief Broadcasts a notice to all currently attached observers.
     * @param notice The notice object to send.
     */
    void notify(const Notice& notice);

    int observerCount() const;
    bool isRegistered(const Observer* observer) const;
};

#endif