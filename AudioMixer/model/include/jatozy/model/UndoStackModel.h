#pragma once

#include <QAbstractListModel>
#include <QString>
#include <QVector>

namespace jatozy::model {
class UndoStackModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles { NameRole = Qt::UserRole + 1 };

public:
    explicit UndoStackModel(QObject *parent = nullptr);
    ~UndoStackModel() override = default;

    auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int override;

    auto data(const QModelIndex &index, int role) const -> QVariant override;

    auto roleNames() const -> QHash<int, QByteArray> override;

    auto appendName(QString name) -> void;

private:
    QVector<QString> m_commandNames;
};
} // namespace jatozy::model