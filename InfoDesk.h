#ifndef INFO_DESK_H
#define INFO_DESK_H

#include "EventUnit.h"

#include <string>

/**
 * @brief An information desk (concrete Leaf).
 *
 * Information desks remain operational during safety notices: the public still
 * needs guidance through an evacuation or a pause. They only close on an
 * explicit closing notice.
 */
class InfoDesk : public EventUnit
{
public:
    /**
     * @brief Constructs an information desk.
     *
     * @param name Display name of the desk.
     * @param capacity Number of staff at the desk.
     * @param areaServed Description of what this desk covers.
     */
    InfoDesk(const std::string& name, int capacity,
             const std::string& areaServed);

    ~InfoDesk() override;

    /**
     * @brief InfoDesk-specific reaction: stays open during safety notices.
     *
     * @param notice The notice pushed by the parent group.
     */
    void update(const Notice& notice) override;

    /** @return Description of the area served by this desk. */
    std::string getAreaServed() const;

private:
    std::string areaServed;
};

#endif