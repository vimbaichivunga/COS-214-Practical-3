#include "EventUnit.h"

#include "Notice.h"

#include <iostream>
#include <string>

EventUnit::EventUnit(const std::string& name, int baseCapacity,
                     bool initiallyOpen)
    : name(name),
      baseCapacity(baseCapacity),
      isOperational(initiallyOpen),
      isPaused(false) {}

EventUnit::~EventUnit() {}

std::string EventUnit::getName() const
{
    return name;
}

int EventUnit::getCapacity() const
{
    return baseCapacity;
}

void EventUnit::open()
{
    isOperational = true;
    isPaused = false;
    std::cout << "    [" << name << "] opens." << std::endl;
}

void EventUnit::close()
{
    isOperational = false;
    isPaused = false;
    std::cout << "    [" << name << "] closes." << std::endl;
}

void EventUnit::reportStatus() const
{
    std::string state = "closed";
    if (isOperational && !isPaused)
    {
        state = "open";
    }
    else if (isOperational && isPaused)
    {
        state = "paused";
    }

    std::cout << "    [" << name << "] " << state
              << ", capacity " << getCapacity();
    if (!lastNoticeName.empty())
    {
        std::cout << ", last notice: " << lastNoticeName
                  << " (\"" << lastNoticeMessage << "\")";
    }
    std::cout << std::endl;
}

bool EventUnit::isOpen() const
{
    return isOperational && !isPaused;
}

bool EventUnit::isPausedFlag() const
{
    return isPaused;
}

const std::string& EventUnit::getLastNoticeName() const
{
    return lastNoticeName;
}

const std::string& EventUnit::getLastNoticeMessage() const
{
    return lastNoticeMessage;
}


void EventUnit::update(const Notice& notice)
{
    recordNotice(notice);

    if (notice.isClosingNotice())
    {
        setOperational(false);
        setPaused(false);
    }
    else if (notice.isPauseNotice())
    {
        setPaused(true);
    }
    else if (notice.isResumeNotice())
    {
        setPaused(false);
        setOperational(true);
    }
    else if (notice.isOperational())
    {
        setOperational(true);
        setPaused(false);
    }
}

void EventUnit::setOperational(bool value)
{
    isOperational = value;
}

void EventUnit::setPaused(bool value)
{
    isPaused = value;
}

void EventUnit::recordNotice(const Notice& notice)
{
    lastNoticeName = notice.getName();
    lastNoticeMessage = notice.getMessage();
}