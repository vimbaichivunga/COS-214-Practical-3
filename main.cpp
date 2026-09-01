#include "EventControl.h"
#include "EventGroup.h"
#include "Notice.h"
#include "Stage.h"
#include "Gate.h"
#include "Vendor.h"
#include "InfoDesk.h"
#include "ShuttleStop.h"
#include "MedicalTeam.h"
#include "SecurityPost.h"
#include "PowerStation.h"

#include <iostream>
#include <string>

static void section(const std::string& title)
{
    std::cout << std::endl
              << "================ " << title << " ================"
              << std::endl;
}

int main()
{
    std::cout
        << "========================================================="
        << std::endl;
    std::cout
        << "  EventFlow - Astral Fields Festival (Composite+Observer)"
        << std::endl;
    std::cout
        << "========================================================="
        << std::endl;

    // --------------------------------------------------------------
    section("1. Build the Composite (3 levels below the root)");
    // --------------------------------------------------------------
    EventGroup* root = new EventGroup("Astral Fields Festival", 0, 12000);

    EventGroup* plaza = new EventGroup("Plaza Zone", 100, 4000);
    Stage* aurora = new Stage("Aurora Stage", 2500, "The Falling Orbit");
    Gate* northGate = new Gate("North Gate", 2000, "Weekend Pass");
    MedicalTeam* medic = new MedicalTeam("Medical Team", 50,
                                         "general first aid");
    EventGroup* foodCourt = new EventGroup("Food Court", 40, 1200);
    Vendor* taco = new Vendor("Taco Vendor", 30, "street tacos & limeade");
    Vendor* coffee = new Vendor("Coffee Vendor", 25, "espresso & pastries");

    foodCourt->add(taco);
    foodCourt->add(coffee);
    plaza->add(aurora);
    plaza->add(northGate);
    plaza->add(medic);
    plaza->add(foodCourt);

    EventGroup* river = new EventGroup("River Zone", 50, 3000);
    Stage* riverStage = new Stage("River Stage", 1800, "Echo Bay Strings");
    ShuttleStop* shuttle = new ShuttleStop("Shuttle Stop", 20, "River Loop");
    InfoDesk* riverDesk = new InfoDesk("River Info Desk", 6,
                                       "Western fields");

    river->add(riverStage);
    river->add(shuttle);
    river->add(riverDesk);

    EventGroup* camping = new EventGroup("Camping Zone", 0, 2000);
    InfoDesk* campOffice = new InfoDesk("Camp Office", 4,
                                        "Camping fields");
    PowerStation* power = new PowerStation("Backup Power Station", 900, 3);

    camping->add(campOffice);
    camping->add(power);

    root->add(plaza);
    root->add(river);
    root->add(camping);

    northGate->admitOne();
    northGate->admitOne();

    root->reportStatus();
    std::cout << "Tree levels below root: root -> zone -> area -> unit."
              << std::endl;

    // --------------------------------------------------------------
    section("2. Observer registration");
    // --------------------------------------------------------------
    EventControl control("Festival Control", root);
    control.attach(root);                  // root receives every broadcast
    SecurityPost* security = new SecurityPost("Perimeter Post", 12,
                                              "outer ring");
    control.attach(security);              // out-of-tree monotask observer

    std::cout << "Observers of control: " << control.observerCount()
              << " (root + SecurityPost)" << std::endl;

    // Policy demo: duplicate attach is ignored, detach of unknown is no-op.
    control.attach(root);
    std::cout << "After duplicate attach(root): " << control.observerCount()
              << " (unchanged - duplicate registration ignored)"
              << std::endl;
    SecurityPost* ghost =
        new SecurityPost("Ghost Post", 1, "nowhere");
    control.detach(ghost);
    std::cout << "Detaching an observer that was never registered "
              << "(ghost post): silent no-op, now " << control.observerCount()
              << " observers." << std::endl;
    delete ghost;

    // --------------------------------------------------------------
    section("3. Notice 1: Open (cascades to the whole tree)");
    // --------------------------------------------------------------
    control.broadcast(OpenNotice("Gates open, the festival begins."));

    // --------------------------------------------------------------
    section("4. Notice 2: ScheduleChange (units reorder)");
    // --------------------------------------------------------------
    control.broadcast(
        ScheduleChangeNotice("Aurora Stage headline moves to 21:30."));

    // --------------------------------------------------------------
    section("5. Notice 3: CapacityAlert (group threshold + vendor rule)");
    // --------------------------------------------------------------
    control.broadcast(
        CapacityAlertNotice("Plaza Zone is approaching capacity."));
    control.printAggregateCapacity();

    // --------------------------------------------------------------
    section("6. Notice 4: WeatherAlert (different rules per unit)");
    // --------------------------------------------------------------
    control.broadcast(
        WeatherAlertNotice("Severe storms forecast within the hour."));

    // --------------------------------------------------------------
    section("7. Registration change: detach SecurityPost");
    // --------------------------------------------------------------
    control.detach(security);
    std::cout << "SecurityPost detached. Observers: "
              << control.observerCount() << std::endl;
    control.broadcast(EvacuateNotice("Perimeter issues evacuation order."));
    std::cout << "(SecurityPost no longer receives notices.)" << std::endl;

    control.attach(security);
    std::cout << "SecurityPost re-attached. Observers: "
              << control.observerCount() << std::endl;

    // --------------------------------------------------------------
    section("8. Pause then Resume (units pause and recover)");
    // --------------------------------------------------------------
    control.broadcast(PauseNotice("Two-minute festival-wide pause."));
    control.broadcast(ResumeNotice("Pause lifted, continue normally."));

    // --------------------------------------------------------------
    section("9. Runtime reorganisation: move Coffee Vendor to Camping Zone");
    // --------------------------------------------------------------
    std::cout << "Before: Coffee Vendor is owned+observed by Food Court."
              << std::endl;
    foodCourt->transfer(camping, coffee);
    std::cout << "After transfer, observer counts: Food Court -> "
              << foodCourt->childCount()
              << " child, Camping Zone -> " << camping->childCount()
              << " children." << std::endl;
    root->reportStatus();

    // --------------------------------------------------------------
    section("10. Composite queries after reorganisation");
    // --------------------------------------------------------------
    control.printAggregateCapacity();
    control.printEventStatus();

    // --------------------------------------------------------------
    section("11. Close: shutdown cascade");
    // --------------------------------------------------------------
    control.broadcast(CloseNotice("End of night, closing all areas."));
    std::cout << "North Gate admissions: " << northGate->getAdmissions()
              << std::endl;

    // --------------------------------------------------------------
    section("12. Clean shutdown (root releases the owned subtree once)");
    // --------------------------------------------------------------
    delete root;       // destroys every owned component exactly once
    delete security;   // standalone observer, owned by the client
    std::cout << "EventFlow shutdown complete." << std::endl;
    return 0;
}