#ifndef GATE_H
#define GATE_H

#include "EventUnit.h"

#include <string>

/**
 * @brief An entry gate (concrete Leaf).
 *
 * A gate stops admitting attendees on a safety or closing notice and reopens
 * on an operational notice. It tracks how many attendees it has admitted.
 */
class Gate : public EventUnit
{
public:
    /**
     * @brief Constructs a gate.
     *
     * @param name Display name of the gate.
     * @param capacity Maximum admissions.
     * @param ticketKind Type of ticket checked at this gate.
     */
    Gate(const std::string& name, int capacity, const std::string& ticketKind);

    ~Gate() override;

    /**
     * @brief Gate-specific reaction: admitting is halted on safety notices.
     *
     * @param notice The notice pushed by the parent group.
     */
    void update(const Notice& notice) override;

    /** @return Total number of attendees admitted so far. */
    int getAdmissions() const;

    /** @brief Increments the admission counter (simulated attendee). */
    void admitOne();

    /** @return The ticket type handled by this gate. */
    std::string getTicketKind() const;

private:
    int admissions;
    std::string ticketKind;
};

#endif