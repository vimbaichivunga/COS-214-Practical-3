#ifndef NOTICE_H
#define NOTICE_H

#include <string>

/**
 * @brief Abstract representation of an order or notice broadcast to the event.
 *
 * Notices use typed subclasses (OpenNotice, CloseNotice, ...) so that the
 * Observer collaboration can push meaningful state to every observer. Each
 * concrete notice also answers category predicates (operational, safety,
 * capacity, ...) so that EventUnit reacts through polymorphism rather than
 * switch-on-type dispatch.
 */
class Notice
{
protected:
    std::string message;
    int severity_;

public:
    /**
     * @brief Constructs a notice.
     *
     * @param message Human-readable description of the notice.
     * @param severity 0 = routine, 1 = warning, 2 = critical.
     */
    Notice(const std::string& message, int severity);

    virtual ~Notice();

    /** @return The short name/type of the notice, e.g. "Evacuate". */
    virtual std::string getName() const = 0;

    /** @return The human-readable message carried by this notice. */
    const std::string& getMessage() const;

    /** @return Severity level: 0 routine, 1 warning, 2 critical. */
    int severity() const;

    /** @return True if the notice requests units to open / re-open. */
    virtual bool isOperational() const;

    /** @return True if the notice closes/shuts a unit. */
    virtual bool isClosingNotice() const;

    /** @return True if the notice pauses activity. */
    virtual bool isPauseNotice() const;

    /** @return True if the notice resumes activity. */
    virtual bool isResumeNotice() const;

    /** @return True if the notice is safety related (weather, evacuation). */
    virtual bool isSafetyRelated() const;

    /** @return True if the notice is capacity related. */
    virtual bool isCapacityRelated() const;

    /** @return True if the notice is a weather-specific alert. */
    virtual bool isWeatherNotice() const;
};

/** @brief Requests affected areas to open. */
class OpenNotice : public Notice
{
public:
    explicit OpenNotice(const std::string& message);
    std::string getName() const override;
    bool isOperational() const override;
};

/** @brief Requests affected areas to close. */
class CloseNotice : public Notice
{
public:
    explicit CloseNotice(const std::string& message);
    std::string getName() const override;
    bool isClosingNotice() const override;
};

/** @brief Announces a schedule change. */
class ScheduleChangeNotice : public Notice
{
public:
    explicit ScheduleChangeNotice(const std::string& message);
    std::string getName() const override;
};

/** @brief Announces a capacity warning for an area. */
class CapacityAlertNotice : public Notice
{
public:
    explicit CapacityAlertNotice(const std::string& message);
    std::string getName() const override;
    bool isCapacityRelated() const override;
};

/** @brief Announces severe weather. */
class WeatherAlertNotice : public Notice
{
public:
    explicit WeatherAlertNotice(const std::string& message);
    std::string getName() const override;
    bool isSafetyRelated() const override;
    bool isWeatherNotice() const override;
};

/** @brief Asks affected units to pause activity. */
class PauseNotice : public Notice
{
public:
    explicit PauseNotice(const std::string& message);
    std::string getName() const override;
    bool isPauseNotice() const override;
};

/** @brief Asks paused units to resume activity. */
class ResumeNotice : public Notice
{
public:
    explicit ResumeNotice(const std::string& message);
    std::string getName() const override;
    bool isResumeNotice() const override;
};

/** @brief Safety-critical instruction to evacuate an area. */
class EvacuateNotice : public Notice
{
public:
    explicit EvacuateNotice(const std::string& message);
    std::string getName() const override;
    bool isSafetyRelated() const override;
    bool isClosingNotice() const override;
};

#endif