#ifndef VENDOR_H
#define VENDOR_H

#include "EventUnit.h"

#include <string>

/**
 * @brief A food/stall vendor (concrete Leaf).
 *
 * A vendor suspends service on a safety or closing notice and restops on a
 * capacity alert, because a near-full area should not encourage more custom.
 * The menu text distinguishes one vendor from another.
 */
class Vendor : public EventUnit
{
public:
    /**
     * @brief Constructs a vendor stall.
     *
     * @param name Display name of the stall.
     * @param capacity Seating capacity of the stall.
     * @param menuShort Human-readable summary of what is sold here.
     */
    Vendor(const std::string& name, int capacity, const std::string& menuShort);

    ~Vendor() override;

    /**
     * @brief Vendor-specific reaction: suspend service on safety notices.
     *
     * @param notice The notice pushed by the parent group.
     */
    void update(const Notice& notice) override;

    /** @return A short description of the menu sold here. */
    std::string getMenu() const;

private:
    std::string menu;
};

#endif