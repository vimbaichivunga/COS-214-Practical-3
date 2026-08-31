#include "Vendor.h"

#include "Notice.h"

#include <iostream>
#include <string>


Vendor::Vendor(const std::string& name, int capacity,
               const std::string& menuShort)
    : EventUnit(name, capacity, true), menu(menuShort) {}

Vendor::~Vendor() {}


void Vendor::update(const Notice& notice)
{
    if (notice.isSafetyRelated() || notice.isCapacityRelated())
    {
        setPaused(true);
        std::cout << "    [Vendor] " << getName()
                  << " suspends service (" << menu << ")."
                  << std::endl;
        recordNotice(notice);
        return;
    }
    EventUnit::update(notice);
}

std::string Vendor::getMenu() const
{
    return menu;
}