#ifndef POWER_STATION_H
#define POWER_STATION_H

#include "EventUnit.h"

#include <string>

/**
 * @brief A portable power station (concrete Leaf, original feature).
 *
 * The power station supplies the grid capacity of the festival. On a capacity
 * alert it recalculates the external load share; on a weather notice it enters
 * low-power mode. This unit is not a copy of the spec examples and shows how a
 * new leaf can be added without touching any controller.
 */
class PowerStation : public EventUnit
{
public:
    /**
     * @brief Constructs a power station.
     *
     * @param name Display name of the station.
     * @param capacity Kilowatts available.
     * @param generators Number of active generators.
     */
    PowerStation(const std::string& name, int capacity, int generators);

    ~PowerStation() override;

    /**
     * @brief PowerStation reaction: low-power mode on weather notices.
     *
     * @param notice The notice pushed by the parent group.
     */
    void update(const Notice& notice) override;

    /** @return Number of active generators. */
    int getActiveGenerators() const;

    /** @return True if the station is in low-power mode. */
    bool isLowPowerMode() const;

private:
    int generators;
    bool lowPower;
};

#endif