#include "jatozy/store/Store.h"
#include <jatozy/model/Amp.h>
#include <jatozy/model/AmpD10Model.h>
#include <jatozy/model/UndoStackModel.h>
#include <jatozy/persistency_interface/Factory.h>
#include <jatozy/persistency_interface/Storage.h>
#include <QModelIndex>
#include <QUndoStack>

namespace jatozy::store {
Store::Store(
    std::shared_ptr<jatozy::hardware_interface::Factory> const &hardwareFactory,
    std::shared_ptr<jatozy::persistency_interface::Factory> const &persistencyFactory,
    QObject *parent)
    : QObject(parent)
    , m_state(std::make_shared<State>(hardwareFactory))
    , m_storage(persistencyFactory->create())
    , m_undoStack(std::make_shared<QUndoStack>())
{
    m_state->ampsD10Raw()->emplaceNewAmp();
}

auto Store::stateRaw() const -> State *
{
    return m_state.get();
}

auto jatozy::store::Store::executeCommand(std::unique_ptr<QUndoCommand> command) -> void
{
    m_undoStack->push(command.release());
    m_state->commandNamesRaw()->appendName(m_undoStack->text(m_undoStack->count() - 1));
}

auto Store::save() const -> void
{
    m_storage->createSnapshot(m_state->ampsD10Raw());
    m_storage->store();
}

auto Store::load() -> void
{
    m_storage->load();
    for (auto const data : m_storage->getAmpsD10Snapshot()) {
        m_state->ampsD10Raw()->emplaceNewAmp(data);
    }
}

auto Store::undo() const -> void
{
    if (m_undoStack->canUndo()) {
        m_undoStack->undo();
    }
}

auto Store::redo() const -> void
{
    if (m_undoStack->canRedo()) {
        m_undoStack->redo();
    }
}
} // namespace jatozy::store
