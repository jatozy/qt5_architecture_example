#include "jatozy/model/UndoStackModel.h"

namespace jatozy::model {
UndoStackModel::UndoStackModel(QObject *parent)
    : QAbstractListModel(parent)
{}

auto UndoStackModel::rowCount(const QModelIndex & /*parent*/) const -> int
{
    return m_commandNames.size();
}

auto UndoStackModel::data(const QModelIndex &index, int role) const -> QVariant
{
    if (!index.isValid() || index.row() >= m_commandNames.count()) {
        return {};
    }

    if (role == NameRole) {
        return m_commandNames.at(index.row());
    }

    return {};
}

auto UndoStackModel::roleNames() const -> QHash<int, QByteArray>
{
    return {{NameRole, "name"}};
}

auto UndoStackModel::appendName(QString name) -> void
{
    auto const row = m_commandNames.size();

    beginInsertRows(QModelIndex(), row, row);
    m_commandNames.append(std::move(name));
    endInsertRows();
}
} // namespace jatozy::model