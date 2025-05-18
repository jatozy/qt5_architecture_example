#pragma once

#include "jatozy/persistency_interface/Factory.h"
#include <QString>

namespace jatozy::persistency_filesystem {
class Factory : public jatozy::persistency_interface::Factory
{
public:
    Factory(QString filePath);
    ~Factory() override = default;

    auto create() -> std::shared_ptr<jatozy::persistency_interface::Storage> override;

private:
    QString m_filePath;
};
} // namespace jatozy::persistency_filesystem