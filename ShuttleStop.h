#ifndef SHUTTLE_STOP_H
#define SHUTTLE_STOP_H

#include "EventUnit.h"

#include <string>

/**
 * @brief A shuttle stop for the event transport loop (concrete Leaf).
 *
 * On a weather notice the shuttle changes route to an inland route and keeps
 * running; transport is paused only by an explicit pause notice.
 */
class ShuttleStop : public EventUnit
{
public:
    /**
     * @brief Constructs a shuttle stop.
     *
     * @param name Display name of the stop.
     * @param capacity Number of shuttles that can queue at once.
     * @param routeName Current route served by this stop.
     */
    ShuttleStop(const std::string& name, int capacity,
                const std::string& routeName);

    ~ShuttleStop() override;

    /**
     * @brief ShuttleStop-specific reaction: reroute on weather notices.
     *
     * @param notice The notice pushed by the parent group.
     */
    void update(const Notice& notice) override;

    /** @return The name of the current route. */
    std::string getRoute() const;

private:
    std::string route;
};

#endif