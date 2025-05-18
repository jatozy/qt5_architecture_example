#pragma once

#include "jatozy/store/State.h"
#include <jatozy/model/Amp.h>
#include <memory>
#include <QObject>
#include <QUndoCommand>

class QUndoStack;

namespace jatozy::hardware_interface {
class Factory;
} // namespace jatozy::hardware_interface

namespace jatozy::persistency_interface {
class Factory;
class Storage;
} // namespace jatozy::persistency_interface

namespace jatozy::store {
class Store : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State *state READ stateRaw NOTIFY stateChanged)

public:
    explicit Store(
        std::shared_ptr<jatozy::hardware_interface::Factory> const &hardwareFactory,
        std::shared_ptr<jatozy::persistency_interface::Factory> const &persistencyFactory,
        QObject *parent = nullptr);
    ~Store() override = default;

    auto stateRaw() const -> State *;

    auto executeCommand(std::unique_ptr<QUndoCommand> command) -> void;
    auto save() const -> void;
    auto load() -> void;
    auto undo() const -> void;
    auto redo() const -> void;

signals:
    auto stateChanged() -> void;

private:
    std::shared_ptr<State> m_state;
    std::shared_ptr<jatozy::persistency_interface::Storage> m_storage;
    std::shared_ptr<QUndoStack> m_undoStack;
};
} // namespace jatozy::store