#pragma once

#include <jatozy/model/Amp.h>
#include <jatozy/model/AmpD10Model.h>
#include <jatozy/persistency_interface/Storage.h>
#include <memory>
#include <QString>
#include <QVector>

namespace jatozy::persistency_filesystem {
class Storage : public jatozy::persistency_interface::Storage
{
public:
    explicit Storage(QString filePath);
    ~Storage() override = default;

    auto load() -> void override;
    auto store() const -> void override;
    auto getAmpsD10Snapshot() const -> SnapshotType const & override;
    auto createSnapshot(jatozy::model::AmpD10Model const *const amps) -> void override;

private:
    QString m_filePath;
    SnapshotType m_snapshotD10;
};
} // namespace jatozy::persistency_filesystem