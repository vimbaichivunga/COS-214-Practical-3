#include "Gate.h"

#include "Notice.h"

#include <iostream>
#include <string>


Gate::Gate(const std::string& name, int capacity,
           const std::string& ticketKind)
    : EventUnit(name, capacity, true), admissions(0), ticketKind(ticketKind) {}

Gate::~Gate() {}


void Gate::update(const Notice& notice)
{
    if (notice.isSafetyRelated() || notice.isClosingNotice())
    {
        setOperational(false);
        std::cout << "    [Gate] " << getName()
                  << " stops admitting (" << ticketKind
                  << ") with " << admissions << " admitted."
                  << std::endl;
        recordNotice(notice);
        return;
    }
    EventUnit::update(notice);
    if (isOpen())
    {
        std::cout << "    [Gate] " << getName()
                  << " resumes admitting (" << ticketKind << ")."
                  << std::endl;
    }
}

int Gate::getAdmissions() const
{
    return admissions;
}

void Gate::admitOne()
{
    ++admissions;
}

std::string Gate::getTicketKind() const
{
    return ticketKind;
}