#pragma once

#include "jatozy/model/Amp.h"
#include "jatozy/model/AmpD10Model.h"
#include "jatozy/store/State.h"
#include <QUndoCommand>

namespace jatozy::store::commands {
class ToggleMuteAmp : public QUndoCommand
{
public:
    using IdType = jatozy::model::Amp::IdType;

public:
    ToggleMuteAmp(State *state, IdType id, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent)
        , m_state(state)
        , m_id(id)
    {
        if (isAmpMuted()) {
            setText(QString("Unmute Amp %1").arg(m_id.toString()));
        } else {
            setText(QString("Mute Amp %1").arg(m_id.toString()));
        }
    }

    auto undo() -> void override { toggle(); }
    auto redo() -> void override { toggle(); }

private:
    auto toggle() const -> void
    {
        auto const amp = m_state->ampsD10Raw()->getAmp(m_id);
        if (!amp.has_value()) {
            return;
        }
        amp.value()->setMute(!amp.value()->mute());
    }

    auto isAmpMuted() const -> bool
    {
        auto const amp = m_state->ampsD10Raw()->getAmp(m_id);
        if (!amp.has_value()) {
            return true;
        }
        return amp.value()->mute();
    }

private:
    State *m_state;
    IdType m_id;
};
} // namespace jatozy::store::commands