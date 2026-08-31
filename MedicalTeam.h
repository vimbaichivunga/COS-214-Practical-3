#ifndef MEDICAL_TEAM_H
#define MEDICAL_TEAM_H

#include "EventUnit.h"
#include <string>

/**
 * @brief First-aid medical team handling emergency responses.
 */
class MedicalTeam : public EventUnit
{
public:
    /**
     * @brief Constructs a MedicalTeam unit.
     * @param name Name of the medical team.
     * @param capacity Available bed/tent capacity.
     * @param speciality Treatment focus of this unit.
     */
    MedicalTeam(const std::string& name, int capacity, const std::string& speciality);

    ~MedicalTeam() override;

    /**
     * @brief Remains fully operational during safety alerts.
     * @param notice Incoming notification.
     */
    void update(const Notice& notice) override;

    std::string getSpeciality() const;

private:
    std::string speciality;
};

#endif