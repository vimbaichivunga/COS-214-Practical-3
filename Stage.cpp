#include "Stage.h"
#include "Notice.h"

#include <iostream>
#include <string>

Stage::Stage(const std::string& name, int capacity, const std::string& currentLineUp)
    : EventUnit(name, capacity, true), lineUp(currentLineUp) {}

Stage::~Stage() {}

void Stage::update(const Notice& notice)
{
    if (notice.isSafetyRelated())
    {
        setPaused(true);
        std::cout << "    [Stage] " << getName() << " halts \"" << lineUp << "\" pending instructions."
        << std::endl;
        recordNotice(notice);
        return;
    }

    EventUnit::update(notice);

    if (notice.getName() == "ScheduleChange")
    {
        std::cout << "    [Stage] " << getName() << " updates its running order for \""
        << lineUp << "\"." << std::endl;
    }
}

std::string Stage::getLineUp() const
{
    return lineUp;
}