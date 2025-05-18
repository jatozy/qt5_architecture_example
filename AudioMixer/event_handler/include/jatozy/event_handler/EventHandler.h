#pragma once

#include <memory>
#include <QObject>
#include <QUuid>

namespace jatozy::store {
class Store;
}

namespace jatozy::event_handler {
class EventHandler : public QObject
{
    Q_OBJECT

public:
    using Store = jatozy::store::Store;

public:
    explicit EventHandler(std::shared_ptr<Store> store, QObject *parent = nullptr);
    ~EventHandler() override = default;

    Q_INVOKABLE void toggleMuteAmp(QUuid const &id) const;
    Q_INVOKABLE void setGainAmp(QUuid const &id, float const value) const;
    Q_INVOKABLE void muteAllAmps() const;
    Q_INVOKABLE void unmuteAllAmps() const;
    Q_INVOKABLE void addAmp() const;
    Q_INVOKABLE void save() const;
    Q_INVOKABLE void undo() const;
    Q_INVOKABLE void redo() const;

private:
    std::shared_ptr<Store> m_store;
};
} // namespace jatozy::event_handler