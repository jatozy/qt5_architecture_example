#include "jatozy/model/AmpD10Model.h"
#include "jatozy/model/AmpD10.h"
#include <algorithm>

namespace jatozy::model {
AmpD10Model::AmpD10Model(std::shared_ptr<HardwareFactory> hardwareFactory, QObject *parent)
    : QAbstractListModel(parent)
    , m_hardwareFactory(std::move(hardwareFactory))
{}

auto AmpD10Model::rowCount(const QModelIndex & /*parent*/) const -> int
{
    return m_amps.size();
}

auto AmpD10Model::data(const QModelIndex &index, int role) const -> QVariant
{
    if (!index.isValid() || index.row() >= m_amps.size())
        return QVariant();

    auto const amp = m_amps.at(index.row());

    switch (role) {
    case ObjectRole:
        return QVariant::fromValue(amp.get());
    default:
        return QVariant();
    }
}

auto AmpD10Model::roleNames() const -> QHash<int, QByteArray>
{
    return {{ObjectRole, "device"}};
}

auto AmpD10Model::getAmp(Amp::IdType id) const -> std::optional<Amp *>
{
    if (auto const it = findAmp(id); it != m_amps.cend()) {
        return it->get();
    }

    return std::nullopt;
}

auto AmpD10Model::getAllAmps() const -> QVector<std::shared_ptr<Amp>> const &
{
    return m_amps;
}

auto AmpD10Model::emplaceNewAmp() -> Amp::IdType
{
    auto const row = m_amps.size();

    beginInsertRows(QModelIndex(), row, row);
    auto const newAmp = std::make_shared<AmpD10>(m_hardwareFactory, this);
    auto const result = newAmp->id();
    m_amps.append(newAmp);
    endInsertRows();
    return result;
}

auto jatozy::model::AmpD10Model::emplaceNewAmp(jatozy::model::Amp::PersistentData const &data) -> void
{
    auto const row = m_amps.size();

    beginInsertRows(QModelIndex(), row, row);
    m_amps.append(std::make_shared<AmpD10>(data.id, data.gain, data.mute, m_hardwareFactory, this));
    endInsertRows();
}

auto jatozy::model::AmpD10Model::removeAmp(jatozy::model::Amp::IdType const &id) -> void
{
    if (auto const it = findAmp(id); it != m_amps.cend()) {
        auto const row = std::distance(m_amps.cbegin(), it);
        beginRemoveRows(QModelIndex(), row, row);
        m_amps.remove(row);
        endRemoveRows();
    }
}

auto jatozy::model::AmpD10Model::findAmp(jatozy::model::Amp::IdType const &id) const
    -> std::ranges::borrowed_iterator_t<const QVector<std::shared_ptr<jatozy::model::Amp>> &>
{
    auto const idMatcher = [&id](auto const &amp) { return amp->id() == id; };

    return std::ranges::find_if(m_amps, idMatcher);
}
} // namespace jatozy::model