#ifndef SECURITY_POST_H
#define SECURITY_POST_H

#include "EventUnit.h"

#include <string>

/**
 * @brief A security/perimeter post (concrete Leaf).
 *
 * A security post can be registered with the EventControl directly (outside
 * the Composite tree) to demonstrate that observation does not require
 * containment. It logs every notice and alerts on safety notices.
 */
class SecurityPost : public EventUnit
{
public:
    /**
     * @brief Constructs a security post.
     *
     * @param name Display name of the post.
     * @param capacity Number of officers on duty.
     * @param sectorDescription Area patrolled by this post.
     */
    SecurityPost(const std::string& name, int capacity,
                 const std::string& sectorDescription);

    ~SecurityPost() override;

    /**
     * @brief SecurityPost reaction: logs every notice, alerts on safety.
     *
     * @param notice The notice pushed by the subject it is registered with.
     */
    void update(const Notice& notice) override;

    /** @return Area patrolled by this post. */
    std::string getSector() const;

private:
    std::string sector;
};

#endif