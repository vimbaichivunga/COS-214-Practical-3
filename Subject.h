#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;
class Notice;

/**
 * @brief Abstract participant of the Observer collaboration (GoF Subject).
 *
 * The Subject owns NO observers: registration is non-owning, so an observer
 * outlives its registration time and must be detached before destruction.
 * Registration policy: duplicate attach() requests are ignored; detach() of an
 * observer that is not registered is a silent no-op. notify() iterates a
 * snapshot of the list so observers may attach/detach mid-notification.
 */
class Subject
{
private:
    std::vector<Observer*> observers;

public:
    Subject();
    virtual ~Subject();

    /**
     * @brief Registers an observer to receive future notifications.
     *
     * @param observer Observer to register. Must be non-null.
     * @return True if the observer was newly added, false if already registered.
     */
    bool attach(Observer* observer);

    /**
     * @brief Deregisters an observer.
     *
     * @param observer Observer to remove. Ignored if not registered.
     */
    void detach(Observer* observer);

    /**
     * @brief Pushes a notice to every currently-registered observer.
     *
     * @param notice The notice to broadcast. Pushed, not pulled.
     */
    void notify(const Notice& notice);

    /** @return Number of currently-registered observers. */
    int observerCount() const;

    /** @return True if the observer is currently registered here. */
    bool isRegistered(const Observer* observer) const;
};

#endif