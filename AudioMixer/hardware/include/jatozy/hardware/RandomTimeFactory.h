#pragma once

#include "jatozy/hardware_interface/Factory.h"
#include <memory>

namespace jatozy::hardware {
class RandomTimeFactory : public jatozy::hardware_interface::Factory
{
public:
    virtual ~RandomTimeFactory() = default;

    auto create() -> std::shared_ptr<jatozy::hardware_interface::Hardware> override;
};
} // namespace jatozy::hardware