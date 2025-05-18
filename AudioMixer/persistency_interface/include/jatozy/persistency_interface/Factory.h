#pragma once

#include <memory>

namespace jatozy::persistency_interface {
class Storage;

class Factory
{
public:
    virtual ~Factory() = default;

    virtual auto create() -> std::shared_ptr<Storage> = 0;
};
} // namespace jatozy::persistency_interface