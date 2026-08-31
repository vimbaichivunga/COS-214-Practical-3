#ifndef POWER_STATION_H
#define POWER_STATION_H

#include "EventUnit.h"
#include <string>

/**
 * @brief Represents a power station unit supplying festival electricity.
 */
class PowerStation : public EventUnit
{
public:
    /**
     * @brief Constructs a PowerStation unit.
     * @param name Name of the station.
     * @param capacity Available output capacity.
     * @param generators Number of active generator units.
     */
    PowerStation(const std::string& name, int capacity, int generators);

    ~PowerStation() override;

    /**
     * @brief Enters low-power mode on weather alerts.
     * @param notice Incoming notification.
     */
    void update(const Notice& notice) override;

    int getActiveGenerators() const;
    bool isLowPowerMode() const;

private:
    int generators;
    bool lowPower;
};

#endif