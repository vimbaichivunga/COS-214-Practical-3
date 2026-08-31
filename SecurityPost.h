#ifndef SECURITY_POST_H
#define SECURITY_POST_H

#include "EventUnit.h"
#include <string>

/**
 * @brief Security post monitoring a specific sector.
 */
class SecurityPost : public EventUnit
{
public:
    /**
     * @brief Constructs a SecurityPost unit.
     * @param name Name of the post.
     * @param capacity Number of active officers.
     * @param sectorDescription Description of the patrolled zone.
     */
    SecurityPost(const std::string& name, int capacity, const std::string& sectorDescription);

    ~SecurityPost() override;

    /**
     * @brief Logs all incoming notices and raises alerts on safety hazards.
     * @param notice Incoming notification.
     */
    void update(const Notice& notice) override;

    std::string getSector() const;

private:
    std::string sector;
};

#endif