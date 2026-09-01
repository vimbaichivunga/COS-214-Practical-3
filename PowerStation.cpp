#include "PowerStation.h"

#include "Notice.h"

#include <iostream>
#include <string>


PowerStation::PowerStation(const std::string& name, int capacity,
                           int generators)
    : EventUnit(name, capacity, true),
      generators(generators),
      lowPower(false) {}

PowerStation::~PowerStation() {}

void PowerStation::update(const Notice& notice)
{
    if (notice.isWeatherNotice())
    {
        lowPower = true;
        std::cout << "    [Power] " << getName()
                  << " enters low-power mode (" << generators
                  << " generators shed to essential loads)."
                  << std::endl;
        recordNotice(notice);
        return;
    }
    EventUnit::update(notice);
    if (notice.isResumeNotice())
    {
        lowPower = false;
    }
}

int PowerStation::getActiveGenerators() const
{
    return generators;
}

bool PowerStation::isLowPowerMode() const
{
    return lowPower;
}