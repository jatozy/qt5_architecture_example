#pragma once

#include <jatozy/model/Amp.h>
#include <jatozy/model/AmpD10Model.h>
#include <memory>
#include <QVector>

namespace jatozy::persistency_interface {
class Storage
{
public:
    using SnapshotType = QVector<jatozy::model::Amp::PersistentData>;

public:
    virtual ~Storage() = default;

    virtual auto load() -> void = 0;
    virtual auto store() const -> void = 0;

    virtual auto getAmpsD10Snapshot() const -> SnapshotType const & = 0;
    virtual auto createSnapshot(jatozy::model::AmpD10Model const *const amps) -> void = 0;
};
} // namespace jatozy::persistency_interface