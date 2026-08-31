#ifndef SHUTTLE_STOP_H
#define SHUTTLE_STOP_H

#include "EventUnit.h"
#include <string>

/**
 * @brief Shuttle station managing festival transport routes.
 */
class ShuttleStop : public EventUnit
{
public:
    /**
     * @brief Constructs a ShuttleStop unit.
     * @param name Name of the stop.
     * @param capacity Maximum queue capacity for shuttles.
     * @param routeName Designated transport route.
     */
    ShuttleStop(const std::string& name, int capacity, const std::string& routeName);

    ~ShuttleStop() override;

    /**
     * @brief Reroutes to inland paths during severe weather notices.
     * @param notice Incoming notification.
     */
    void update(const Notice& notice) override;

    std::string getRoute() const;

private:
    std::string route;
};

#endif