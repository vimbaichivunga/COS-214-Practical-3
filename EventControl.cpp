#include "EventControl.h"

#include "EventGroup.h"
#include "EventComponent.h"
#include "Notice.h"

#include <iostream>
#include <string>


EventControl::EventControl(const std::string& name, EventGroup* root)
    : name(name), root(root) {}

EventControl::~EventControl() {}

std::string EventControl::getName() const
{
    return name;
}

void EventControl::broadcast(const Notice& notice)
{
    std::cout << std::endl << ">>> [" << name << "] broadcasts \""
    << notice.getName() << "\": " << notice.getMessage() << std::endl;
    notify(notice);
}

EventGroup* EventControl::getRoot() const
{
    return root;
}

void EventControl::printAggregateCapacity() const
{
    if (root)
    {
        std::cout << "Aggregate capacity of the whole event: "
        << root->getCapacity() << " attendees" << std::endl;
    }
}

void EventControl::printEventStatus() const
{
    if (root)
    {
        root->reportStatus();
    }
}