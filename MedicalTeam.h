#ifndef MEDICAL_TEAM_H
#define MEDICAL_TEAM_H

#include "EventUnit.h"

#include <string>

/**
 * @brief A medical team post (concrete Leaf).
 *
 * A medical post is a monotask observer rule example: it stays operational
 * through safety notices such as weather or evacuation, because first aid is
 * most needed while other units are shutting down.
 */
class MedicalTeam : public EventUnit
{
public:
    /**
     * @brief Constructs a medical post.
     *
     * @param name Display name of the post.
     * @param capacity Number of beds/tents available.
     * @param speciality What this post is equipped to treat.
     */
    MedicalTeam(const std::string& name, int capacity,
                const std::string& speciality);

    ~MedicalTeam() override;

    /**
     * @brief MedicalTeam reaction: remains operational on safety notices.
     *
     * @param notice The notice pushed by the parent group.
     */
    void update(const Notice& notice) override;

    /** @return What this post is equipped to treat. */
    std::string getSpeciality() const;

private:
    std::string speciality;
};

#endif