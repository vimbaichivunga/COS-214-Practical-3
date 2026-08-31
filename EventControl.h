#ifndef EVENT_CONTROL_H
#define EVENT_CONTROL_H

#include "Subject.h"
#include <string>

class Notice;
class EventGroup;
class EventComponent;

/**
 * @brief Central control room managing event-wide broadcasts.
 *
 * Dispatches notices to registered observers via broadcast(). Maintains
 * a reference to the root EventGroup to query aggregate statistics.
 */
class EventControl : public Subject
{
private:
    std::string name;
    EventGroup* root;

public:
    /**
     * @brief Constructs the EventControl manager.
     * @param name Name of the control room.
     * @param root Pointer to the root EventGroup tree.
     */
    EventControl(const std::string& name, EventGroup* root);

    ~EventControl() override;

    std::string getName() const;

    /**
     * @brief Sends a notice to all currently attached observers.
     * @param notice The notice object to broadcast.
     */
    void broadcast(const Notice& notice);

    EventGroup* getRoot() const;

    /**
     * @brief Calculates and prints overall capacity across the component hierarchy.
     */
    void printAggregateCapacity() const;

    /**
     * @brief Triggers a status report for the entire tree structure.
     */
    void printEventStatus() const;
};

#endif