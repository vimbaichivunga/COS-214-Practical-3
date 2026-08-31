#include "Subject.h"

#include "Observer.h"
#include "Notice.h"

#include <algorithm>

Subject::Subject() {}

Subject::~Subject() {}


bool Subject::attach(Observer* observer)
{
    if (!observer)
    {
        return false;
    }
 
    if (isRegistered(observer)) //gurantees unitt isnt notified 2+ tims
    {
        return false;
    }
    observers.push_back(observer);
    return true;
}

void Subject::detach(Observer* observer)
{
    const bool wasRegistered = isRegistered(observer);
    if (!wasRegistered)
    {
        return;
    }
    for (std::vector<Observer*>::iterator it = observers.begin();
         it != observers.end(); ++it)
    {
        if (*it == observer)
        {
            observers.erase(it);
            return;
        }
    }
}

void Subject::notify(const Notice& notice)
{
    std::vector<Observer*> snapshot = observers;
    for (std::size_t i = 0; i < snapshot.size(); ++i)
    {
        snapshot[i]->update(notice);
    }
}

int Subject::observerCount() const
{
    return static_cast<int>(observers.size());
}

bool Subject::isRegistered(const Observer* observer) const
{
    return std::find(observers.begin(), observers.end(), observer)
        != observers.end();
}