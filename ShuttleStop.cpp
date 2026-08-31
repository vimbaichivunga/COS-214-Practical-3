#include "ShuttleStop.h"
#include "Notice.h"

#include <iostream>
#include <string>

ShuttleStop::ShuttleStop(const std::string& name, int capacity, const std::string& routeName)
    : EventUnit(name, capacity, true), route(routeName) {}

ShuttleStop::~ShuttleStop() {}

void ShuttleStop::update(const Notice& notice)
{
    if (notice.isWeatherNotice())
    {
        route = "Inland detour - " + route;
        std::cout << "    [Shuttle] " << getName() << " reroutes to \"" << route << "\"."
        << std::endl;
        recordNotice(notice);
        return;
    }

    EventUnit::update(notice);
}

std::string ShuttleStop::getRoute() const
{
    return route;
}