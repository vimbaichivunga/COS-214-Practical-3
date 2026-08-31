#include "EventGroup.h"

#include "EventComponent.h"
#include "Notice.h"

#include <iostream>
#include <string>
#include <vector>

EventGroup::EventGroup(const std::string& name, int baseCapacity,
                       int alertThreshold)
    : name(name),
      baseCapacity(baseCapacity),
      alertThreshold(alertThreshold),
      isAreaOpen(true) {}


EventGroup::~EventGroup()
{
    for (std::vector<EventComponent*>::iterator it = children.begin();
         it != children.end(); ++it)
    {
        delete *it;
    }
}

std::string EventGroup::getName() const
{
    return name;
}

void EventGroup::open()
{
    isAreaOpen = true;
    for (std::vector<EventComponent*>::iterator it = children.begin();
         it != children.end(); ++it)
    {
        (*it)->open();
    }
}

void EventGroup::close()
{
    isAreaOpen = false;
    for (std::vector<EventComponent*>::iterator it = children.begin();
         it != children.end(); ++it)
    {
        (*it)->close();
    }
}

void EventGroup::reportStatus() const
{
    std::cout << "  [Area] " << name << ": aggregate capacity "
              << getCapacity() << (isAreaOpen ? " (open)" : " (closed)");
    if (!lastNoticeName.empty())
    {
        std::cout << ", last notice: " << lastNoticeName;
    }
    std::cout << std::endl;
    for (std::vector<EventComponent*>::const_iterator it = children.begin();
         it != children.end(); ++it)
    {
        (*it)->reportStatus();
    }
}

int EventGroup::getCapacity() const
{
    int total = baseCapacity;
    for (std::vector<EventComponent*>::const_iterator it = children.begin();
         it != children.end(); ++it)
    {
        total += (*it)->getCapacity();
    }
    return total;
}


void EventGroup::add(EventComponent* child)
{
    if (!child)
    {
        return;
    }
    Observer* asObserver = dynamic_cast<Observer*>(child);
    if (asObserver)
    {
        attach(asObserver);
    }
    children.push_back(child);
}

void EventGroup::remove(EventComponent* child)
{
    Observer* asObserver = dynamic_cast<Observer*>(child);
    if (asObserver)
    {
        detach(asObserver);
    }
    for (std::vector<EventComponent*>::iterator it = children.begin();
         it != children.end(); ++it)
    {
        if (*it == child)
        {
            children.erase(it);
            delete child;
            return;
        }
    }
}

EventComponent* EventGroup::release(EventComponent* child)
{
    Observer* asObserver = dynamic_cast<Observer*>(child);
    if (asObserver)
    {
        detach(asObserver);
    }
    for (std::vector<EventComponent*>::iterator it = children.begin();
         it != children.end(); ++it)
    {
        if (*it == child)
        {
            children.erase(it);
            return child;
        }
    }
    return 0;
}

void EventGroup::transfer(EventGroup* destination, EventComponent* child)
{
    if (!destination)
    {
        return;
    }
    EventComponent* moved = release(child);
    if (moved)
    {
        destination->add(moved);
    }
}

int EventGroup::childCount() const
{
    return static_cast<int>(children.size());
}

std::vector<EventComponent*> EventGroup::getChildren() const
{
    return children;
}

bool EventGroup::isOpen() const
{
    return isAreaOpen;
}

int EventGroup::getAlertThreshold() const
{
    return alertThreshold;
}


void EventGroup::update(const Notice& notice)
{
    lastNoticeName = notice.getName();

    std::cout << "  [Area] " << name << " received \"" << notice.getName()
              << "\" (" << notice.getMessage() << "), forwarding to "
              << observerCount() << " observer(s)" << std::endl;

    if (notice.isCapacityRelated() && getCapacity() >= alertThreshold)
    {

        std::cout << "  [Area] " << name << " is at/over capacity "
                  << alertThreshold << " - crowd to be held at gates."
                  << std::endl;
    }

    notify(notice);
}