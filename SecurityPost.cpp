#include "SecurityPost.h"
#include "Notice.h"

#include <iostream>
#include <string>

SecurityPost::SecurityPost(const std::string& name, int capacity, const std::string& sectorDescription)
    : EventUnit(name, capacity, true), sector(sectorDescription) {}

SecurityPost::~SecurityPost() {}

void SecurityPost::update(const Notice& notice)
{
    recordNotice(notice);

    if (notice.isSafetyRelated())
    {
        std::cout << "    [Security] " << getName() << " raises alert for " << sector
        << " (\"" << notice.getName() << "\")." << std::endl;
        return;
    }

    std::cout << "    [Security] " << getName() << " notes \""
    << notice.getName() << "\"." << std::endl;
}

std::string SecurityPost::getSector() const
{
    return sector;
}