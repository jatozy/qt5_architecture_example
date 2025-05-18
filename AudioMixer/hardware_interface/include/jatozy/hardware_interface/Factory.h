#pragma once

#include "jatozy/hardware_interface/Hardware.h"
#include <memory>

namespace jatozy::hardware_interface {
class Factory
{
public:
    virtual ~Factory() = default;

    virtual auto create() -> std::shared_ptr<Hardware> = 0;
};
} // namespace jatozy::hardware_interface