#ifndef EVENT_COMPONENT_H
#define EVENT_COMPONENT_H

#include <string>

/**
 * @brief Common interface of the Composite collaboration (GoF Component).
 *
 * Both EventUnit (leaves) and EventGroup (composites) implement this
 * interface so clients can open, close, report or size any part of the event
 * without knowing whether it is a leaf or a whole subtree.
 *
 * Ownership: never store an EventComponent by value; composites own their
 * children. Every polymorphic base has a virtual destructor so deletion of the
 * root releases the whole owned subtree exactly once.
 */
class EventComponent
{
public:
    virtual ~EventComponent();

    /** @return The display name of this component. */
    virtual std::string getName() const = 0;

    /** @brief Opens this component (recursively for composites). */
    virtual void open() = 0;

    /** @brief Closes this component (recursively for composites). */
    virtual void close() = 0;

    /** @brief Prints a status line for this component. */
    virtual void reportStatus() const = 0;

    /** @return Capacity of this component (aggregate capacity for groups). */
    virtual int getCapacity() const = 0;
};

#endif