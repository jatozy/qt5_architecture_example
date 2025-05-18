#pragma once

#include "jatozy/model/Amp.h"
#include <memory>
#include <optional>
#include <QAbstractListModel>
#include <QVector>

namespace jatozy::hardware_interface {
class Factory;
} // namespace jatozy::hardware_interface

namespace jatozy::model {
class AmpD10Model : public QAbstractListModel
{
    Q_OBJECT

public:
    using HardwareFactory = jatozy::hardware_interface::Factory;

public:
    enum AmpRoles { ObjectRole = Qt::UserRole + 1 };

public:
    explicit AmpD10Model(std::shared_ptr<HardwareFactory> hardwareFactory, QObject *parent = nullptr);

    auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int override;
    auto data(const QModelIndex &index, int role) const -> QVariant override;

    auto roleNames() const -> QHash<int, QByteArray> override;
    auto getAmp(Amp::IdType id) const -> std::optional<Amp *>;
    auto getAllAmps() const -> QVector<std::shared_ptr<Amp>> const &;
    auto emplaceNewAmp() -> Amp::IdType;
    auto emplaceNewAmp(jatozy::model::Amp::PersistentData const &data) -> void;
    auto removeAmp(jatozy::model::Amp::IdType const &id) -> void;

private:
    auto findAmp(jatozy::model::Amp::IdType const &id) const
        -> std::ranges::borrowed_iterator_t<const QVector<std::shared_ptr<jatozy::model::Amp>> &>;

private:
    QVector<std::shared_ptr<Amp>> m_amps;
    std::shared_ptr<HardwareFactory> m_hardwareFactory;
};
} // namespace jatozy::model