#ifndef STAGE_H
#define STAGE_H

#include "EventUnit.h"
#include <string>

/**
 * @brief Event stage hosting performances.
 */
class Stage : public EventUnit
{
public:
    /**
     * @brief Constructs a Stage unit.
     * @param name Name of the stage.
     * @param capacity Spectator capacity limit.
     * @param currentLineUp Performance act currently scheduled.
     */
    Stage(const std::string& name, int capacity,
          const std::string& currentLineUp);

    ~Stage() override;

    /**
     * @brief Pauses performances upon receiving a safety notice.
     * @param notice Incoming notification.
     */
    void update(const Notice& notice) override;

    std::string getLineUp() const;

private:
    std::string lineUp;
};

#endif