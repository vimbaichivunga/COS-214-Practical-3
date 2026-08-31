#ifndef EVENT_UNIT_H
#define EVENT_UNIT_H

#include "EventComponent.h"
#include "Observer.h"

#include <string>

class Notice;

/**
 * @brief Base class for every concrete leaf (GoF Leaf).
 *
 * An EventUnit is a single operational unit: a stage, a gate, a vendor, an
 * information desk, a shuttle stop, a medical team, and so on. Because it sits
 * inside an EventGroup tree, it also implements Observer so it can react to
 * notices that cascade down from its parent.
 *
 * A leaf reacts to notices through its own update() implementation. The base
 * class provides the generic state machine (open/closed/paused) plus a record
 * of the most recent notice; concrete leaves override update() to add their
 * event-specific rule without any type switching.
 */
class EventUnit : public EventComponent, public Observer
{
private:
    std::string name;
    int baseCapacity;
    bool isOperational;
    bool isPaused;
    std::string lastNoticeName;
    std::string lastNoticeMessage;

public:
    /**
     * @brief Constructs a leaf unit.
     *
     * @param name Display name of the unit.
     * @param baseCapacity Nominal capacity of this unit.
     * @param initiallyOpen Starts opened when true, closed otherwise.
     */
    EventUnit(const std::string& name, int baseCapacity, bool initiallyOpen = true);

    ~EventUnit() override;

    std::string getName() const override;

    int getCapacity() const override;

    void open() override;

    void close() override;

    void reportStatus() const override;

    /** @return True when the unit is open and not paused. */
    bool isOpen() const;

    /** @return True when the unit is currently paused. */
    bool isPausedFlag() const;

    /** @return The name of the most recent notice that reached this unit. */
    const std::string& getLastNoticeName() const;

    /** @return The message of the most recent notice that reached this unit. */
    const std::string& getLastNoticeMessage() const;

    /**
     * @brief Generic reaction to a pushed notice.
     *
     * Records the notice and applies the default state machine using the
     * notice category predicates. Concrete leaves call this from their own
     * update() to keep the generic behaviour, then specialise.
     *
     * @param notice The notice that was pushed to this unit.
     */
    void update(const Notice& notice) override;

protected:
    /** @brief Sets whether the unit is operational (open). */
    void setOperational(bool value);

    /** @brief Sets whether the unit is paused. */
    void setPaused(bool value);

    /**
     * @brief Stores a copy of a notice as the latest push received.
     *
     * Only the name and message are copied: a Notice is typically passed by
     * const reference and may be a temporary, so the unit must never keep a
     * pointer into it.
     *
     * @param notice The notice to remember.
     */
    void recordNotice(const Notice& notice);
};

#endif