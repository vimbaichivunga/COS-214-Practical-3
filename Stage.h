#ifndef STAGE_H
#define STAGE_H

#include "EventUnit.h"

#include <string>

/**
 * @brief A performance stage (concrete Leaf).
 *
 * An outdoor stage pauses its performance when a safety notice arrives and
 * resumes on a resume notice. On a capacity alert it checks its own crowd
 * limit and may close the pit if exceeded.
 */
class Stage : public EventUnit
{
public:
    /**
     * @brief Constructs a stage.
     *
     * @param name Display name of the stage.
     * @param capacity Nominal spectator capacity.
     * @param currentLineUp Name of the performance currently booked.
     */
    Stage(const std::string& name, int capacity,
          const std::string& currentLineUp);

    ~Stage() override;

    /**
     * @brief Stage-specific reaction: pause performance on safety notices.
     *
     * @param notice The notice pushed by the parent group.
     */
    void update(const Notice& notice) override;

    /** @return The name of the booked performance. */
    std::string getLineUp() const;

private:
    std::string lineUp;
};

#endif