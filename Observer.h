#ifndef OBSERVER_H
#define OBSERVER_H

class Notice;

/**
 * @brief Abstract participant of the Observer collaboration (GoF Observer).
 *
 * An observer receives notifications pushed by a Subject. This practical uses
 * a push model: the Subject passes the relevant Notice object directly to
 * update(), so a unit never needs to query the Subject back for state.
 *
 * Observer pointers held by a Subject are non-owning. An observer must be
 * detached (or destroyed after the subject) to avoid dangling registrations.
 */
class Observer
{
public:
    virtual ~Observer();

    /**
     * @brief Called by a Subject when something changes.
     *
     * @param notice The pushed notice describing the change.
     */
    virtual void update(const Notice& notice) = 0;
};

#endif