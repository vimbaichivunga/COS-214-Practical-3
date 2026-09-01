#ifndef NOTICE_H
#define NOTICE_H

#include <string>

/**
 * @brief Abstract base class representing system notices and orders.
 */
class Notice
{
protected:
    std::string message;
    int severity_;

public:
    /**
     * @brief Constructs a Notice instance.
     * @param message Descriptive broadcast text.
     * @param severity Priority rank (0 = info, 1 = warning, 2 = safety/critical).
     */
    Notice(const std::string& message, int severity);

    virtual ~Notice();

    virtual std::string getName() const = 0;
    const std::string& getMessage() const;
    int severity() const;

    virtual bool isOperational() const;
    virtual bool isClosingNotice() const;
    virtual bool isPauseNotice() const;
    virtual bool isResumeNotice() const;
    virtual bool isSafetyRelated() const;
    virtual bool isCapacityRelated() const;
    virtual bool isWeatherNotice() const;
};

class OpenNotice : public Notice
{
public:
    explicit OpenNotice(const std::string& message);
    std::string getName() const override;
    bool isOperational() const override;
};

class CloseNotice : public Notice
{
public:
    explicit CloseNotice(const std::string& message);
    std::string getName() const override;
    bool isClosingNotice() const override;
};

class ScheduleChangeNotice : public Notice
{
public:
    explicit ScheduleChangeNotice(const std::string& message);
    std::string getName() const override;
};

class CapacityAlertNotice : public Notice
{
public:
    explicit CapacityAlertNotice(const std::string& message);
    std::string getName() const override;
    bool isCapacityRelated() const override;
};

class WeatherAlertNotice : public Notice
{
public:
    explicit WeatherAlertNotice(const std::string& message);
    std::string getName() const override;
    bool isSafetyRelated() const override;
    bool isWeatherNotice() const override;
};

class PauseNotice : public Notice
{
public:
    explicit PauseNotice(const std::string& message);
    std::string getName() const override;
    bool isPauseNotice() const override;
};

class ResumeNotice : public Notice
{
public:
    explicit ResumeNotice(const std::string& message);
    std::string getName() const override;
    bool isResumeNotice() const override;
};

class EvacuateNotice : public Notice
{
public:
    explicit EvacuateNotice(const std::string& message);
    std::string getName() const override;
    bool isSafetyRelated() const override;
    bool isClosingNotice() const override;
};

#endif