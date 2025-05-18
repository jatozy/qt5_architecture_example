#include "jatozy/event_handler/EventHandler.h"
#include <jatozy/store/Store.h>
#include <jatozy/store/commands/AddAmp.h>
#include <jatozy/store/commands/MuteAllAmps.h>
#include <jatozy/store/commands/SetGainAmp.h>
#include <jatozy/store/commands/ToggleMuteAmp.h>
#include <jatozy/store/commands/UnmuteAllAmps.h>

namespace jatozy::event_handler {

EventHandler::EventHandler(std::shared_ptr<Store> store, QObject *parent)
    : QObject(parent)
    , m_store(std::move(store))
{}

auto EventHandler::toggleMuteAmp(QUuid const &id) const -> void
{
    m_store->executeCommand(
        std::make_unique<jatozy::store::commands::ToggleMuteAmp>(m_store->stateRaw(), id));
}

auto EventHandler::setGainAmp(QUuid const &id, float const value) const -> void
{
    m_store->executeCommand(
        std::make_unique<jatozy::store::commands::SetGainAmp>(m_store->stateRaw(), id, value));
}

auto EventHandler::muteAllAmps() const -> void
{
    m_store->executeCommand(
        std::make_unique<jatozy::store::commands::MuteAllAmps>(m_store->stateRaw()));
}

auto EventHandler::unmuteAllAmps() const -> void
{
    m_store->executeCommand(
        std::make_unique<jatozy::store::commands::UnmuteAllAmps>(m_store->stateRaw()));
}

auto EventHandler::addAmp() const -> void
{
    m_store->executeCommand(std::make_unique<jatozy::store::commands::AddAmp>(m_store->stateRaw()));
}

auto EventHandler::save() const -> void
{
    m_store->save();
}

auto EventHandler::undo() const -> void
{
    m_store->undo();
}

auto EventHandler::redo() const -> void
{
    m_store->redo();
}
} // namespace jatozy::event_handler