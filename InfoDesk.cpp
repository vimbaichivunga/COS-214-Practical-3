#include "InfoDesk.h"

#include "Notice.h"

#include <iostream>
#include <string>


InfoDesk::InfoDesk(const std::string& name, int capacity,
                   const std::string& areaServed)
    : EventUnit(name, capacity, true), areaServed(areaServed) {}

InfoDesk::~InfoDesk() {}


void InfoDesk::update(const Notice& notice)
{
    if (notice.isSafetyRelated())
    {
        std::cout << "    [InfoDesk] " << getName()
                  << " keeps guiding visitors (" << areaServed
                  << ") during \"" << notice.getName() << "\"."
                  << std::endl;
        recordNotice(notice);
        return;
    }
    EventUnit::update(notice);
}

std::string InfoDesk::getAreaServed() const
{
    return areaServed;
}