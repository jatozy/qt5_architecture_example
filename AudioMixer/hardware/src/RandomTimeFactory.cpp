#include "jatozy/hardware/RandomTimeFactory.h"
#include "jatozy/hardware/RandomTimeHardware.h"

namespace jatozy::hardware {

auto RandomTimeFactory::create() -> std::shared_ptr<jatozy::hardware_interface::Hardware>
{
    return std::make_shared<RandomTimeHardware>();
}

} // namespace jatozy::hardware