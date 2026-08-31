#ifndef EVENT_GROUP_H
#define EVENT_GROUP_H

#include "EventComponent.h"
#include "Observer.h"
#include "Subject.h"

#include <string>
#include <vector>

class Notice;

/**
 * @brief Composite area of the event (GoF Composite).
 *
 * An EventGroup is both an EventComponent (contains children) and an Observer
 * AND a Subject. When it receives a notice from its parent (Observer role) it
 * forwards that same notice to its own registered observers (Subject role).
 * This is the cascading notification behaviour required by the spec. Being
 * both Observer and Subject is not pattern misuse: the two roles describe two
 * different collaborations (receiving change from above, notifying interest
 * below).
 *
 * Ownership: an EventGroup owns every child EventComponent in its list.
 * add() transfers ownership and automatically registers the child as an
 * observer. release() returns ownership to the caller (without deleting) and
 * deregisters it — this is the safe way to transfer a unit between composites.
 */
class EventGroup : public EventComponent, public Observer, public Subject
{
private:
    std::string name;
    int baseCapacity;
    int alertThreshold;
    bool isAreaOpen;
    std::string lastNoticeName;

    std::vector<EventComponent*> children;

public:
    /**
     * @brief Constructs an empty composite area.
     *
     * @param name Display name of the area.
     * @param baseCapacity Base capacity owned directly by the area itself.
     * @param alertThreshold Capacity above which the group prints a warning.
     */
    EventGroup(const std::string& name, int baseCapacity, int alertThreshold);

    ~EventGroup() override;

    std::string getName() const override;

    /** @brief Opens this area and every child recursively. */
    void open() override;

    /** @brief Closes this area and every child recursively. */
    void close() override;

    /** @brief Prints this area and prints every child recursively. */
    void reportStatus() const override;

    /** @return Aggregate capacity = base + sum of all child capacities. */
    int getCapacity() const override;

    /**
     * @brief Takes ownership of a child and auto-registers it as an observer.
     *
     * A child that is added and owned is automatically attached so it receives
     * the notices this group cascades downward.
     *
     * @param child Child EventComponent to take ownership of. Must be non-null.
     */
    void add(EventComponent* child);

    /**
     * @brief Removes and deletes a directly-held child, detaching it first.
     *
     * @param child Child to destroy. Ignored if not a direct child.
     */
    void remove(EventComponent* child);

    /**
     * @brief Releases ownership of a child without destroying it.
     *
     * Detaches the child observer registration and erases the pointer. The
     * caller (or a destination group via transfer) becomes the new owner.
     *
     * @param child Child to release ownership of.
     * @return The released child pointer, so the new owner can adopt it.
     */
    EventComponent* release(EventComponent* child);

    /**
     * @brief Moves a directly-held child into another group.
     *
     * Ownership and observer registrations are both updated: release() from
     * this group, then add() by the destination. No deletion occurs, so no
     * double-free is possible.
     *
     * @param destination The group that will own the child afterwards.
     * @param child The child to move. Must currently be a direct child here.
     */
    void transfer(EventGroup* destination, EventComponent* child);

    /** @return Number of direct children in this group. */
    int childCount() const;

    /** @return The vector of direct children (non-owning view). */
    std::vector<EventComponent*> getChildren() const;

    /** @return True if the group is currently open. */
    bool isOpen() const;

    /** @return Aggregate aggregate capacity threshold used by warning logic. */
    int getAlertThreshold() const;

    /**
     * @brief Receives a notice from above and cascades it to children.
     *
     * The Observer role: record the notice, then act as a Subject and notify
     * every registered child (loop). Any capacity-related notice is checked
     * against the aggregate threshold here (condition used by SD3 alt/opt).
     *
     * @param notice The notice received from the parent/control.
     */
    void update(const Notice& notice) override;
};

#endif