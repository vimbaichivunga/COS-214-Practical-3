#include "Notice.h"

Notice::Notice(const std::string& message, int severity)
    : message(message), severity_(severity) {}

Notice::~Notice() {}

const std::string& Notice::getMessage() const
{
    return message;
}

int Notice::severity() const
{
    return severity_;
}

bool Notice::isOperational() const { return false; }
bool Notice::isClosingNotice() const { return false; }
bool Notice::isPauseNotice() const { return false; }
bool Notice::isResumeNotice() const { return false; }
bool Notice::isSafetyRelated() const { return false; }
bool Notice::isCapacityRelated() const { return false; }
bool Notice::isWeatherNotice() const { return false; }


OpenNotice::OpenNotice(const std::string& message)
    : Notice(message, 0) {}

std::string OpenNotice::getName() const
{
    return "Open";
}

bool OpenNotice::isOperational() const
{
    return true;
}


CloseNotice::CloseNotice(const std::string& message)
    : Notice(message, 1) {}

std::string CloseNotice::getName() const
{
    return "Close";
}

bool CloseNotice::isClosingNotice() const
{
    return true;
}


ScheduleChangeNotice::ScheduleChangeNotice(const std::string& message)
    : Notice(message, 0) {}

std::string ScheduleChangeNotice::getName() const
{
    return "ScheduleChange";
}


CapacityAlertNotice::CapacityAlertNotice(const std::string& message)
    : Notice(message, 1) {}

std::string CapacityAlertNotice::getName() const
{
    return "CapacityAlert";
}

bool CapacityAlertNotice::isCapacityRelated() const
{
    return true;
}


WeatherAlertNotice::WeatherAlertNotice(const std::string& message)
    : Notice(message, 2) {}

std::string WeatherAlertNotice::getName() const
{
    return "WeatherAlert";
}

bool WeatherAlertNotice::isSafetyRelated() const
{
    return true;
}

bool WeatherAlertNotice::isWeatherNotice() const
{
    return true;
}


PauseNotice::PauseNotice(const std::string& message)
    : Notice(message, 1) {}

std::string PauseNotice::getName() const
{
    return "Pause";
}

bool PauseNotice::isPauseNotice() const
{
    return true;
}


ResumeNotice::ResumeNotice(const std::string& message)
    : Notice(message, 0) {}

std::string ResumeNotice::getName() const
{
    return "Resume";
}

bool ResumeNotice::isResumeNotice() const
{
    return true;
}


EvacuateNotice::EvacuateNotice(const std::string& message)
    : Notice(message, 2) {}

std::string EvacuateNotice::getName() const
{
    return "Evacuate";
}

bool EvacuateNotice::isSafetyRelated() const
{
    return true;
}

bool EvacuateNotice::isClosingNotice() const
{
    return true;
}