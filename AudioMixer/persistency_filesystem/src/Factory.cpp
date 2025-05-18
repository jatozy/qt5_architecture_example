#include "jatozy/persistency_filesystem/Factory.h"
#include "Storage.h"
#include <QString>

namespace jatozy::persistency_filesystem {
Factory::Factory(QString filePath)
    : m_filePath(std::move(filePath))
{}

auto Factory::create() -> std::shared_ptr<jatozy::persistency_interface::Storage>
{
    return std::make_shared<Storage>(m_filePath);
}
} // namespace jatozy::persistency_filesystem