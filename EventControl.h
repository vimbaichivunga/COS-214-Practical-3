#ifndef EVENT_CONTROL_H
#define EVENT_CONTROL_H

#include "Subject.h"

#include <string>

class Notice;
class EventGroup;
class EventComponent;

/**
 * @brief Central control room of the event (GoF Concrete Subject).
 *
 * EventControl issues notices by calling broadcast(), which pushes the notice
 * to every registered observer. It holds a non-owning association to the root
 * EventGroup so it can report aggregate statistics; EventControl itself is NOT
 * part of the Composite tree and owns none of the event components.
 *
 * The root group is normally registered here; any leaf can also register here
 * directly (monotask observer) to show that observation is independent of
 * containment.
 */
class EventControl : public Subject
{
private:
    std::string name;
    EventGroup* root;

public:
    /**
     * @brief Constructs the event control room.
     *
     * @param name Display name of the control room.
     * @param root Pointer to the root EventGroup (non-owning). May be null.
     */
    EventControl(const std::string& name, EventGroup* root);

    ~EventControl() override;

    /** @return Display name of the control room. */
    std::string getName() const;

    /**
     * @brief Broadcasts a notice to every registered observer (push model).
     *
     * @param notice The notice to push to all registered observers.
     */
    void broadcast(const Notice& notice);

    /** @return The associated root group (non-owning). */
    EventGroup* getRoot() const;

    /**
     * @brief Prints aggregate capacity of the whole event via the root.
     *
     * Performs a Composite traversal/query through the Component interface.
     */
    void printAggregateCapacity() const;

    /**
     * @brief Prints the full status of the event via the root tree.
     */
    void printEventStatus() const;
};

#endif