#include "MedicalTeam.h"

#include "Notice.h"

#include <iostream>
#include <string>


MedicalTeam::MedicalTeam(const std::string& name, int capacity,
                         const std::string& speciality)
    : EventUnit(name, capacity, true), speciality(speciality) {}

MedicalTeam::~MedicalTeam() {}


void MedicalTeam::update(const Notice& notice)
{
    recordNotice(notice);
    if (notice.isSafetyRelated())
    {
        std::cout << "    [MedicalTeam] " << getName()
                  << " stands ready (" << speciality
                  << ") during \"" << notice.getName() << "\"."
                  << std::endl;
        return;
    }
    EventUnit::update(notice);
}

std::string MedicalTeam::getSpeciality() const
{
    return speciality;
}