#pragma once

#include "jatozy/model/Amp.h"
#include "jatozy/model/AmpD10Model.h"
#include "jatozy/store/State.h"
#include <QUndoCommand>

namespace jatozy::store::commands {
class UnmuteAllAmps : public QUndoCommand
{
public:
    UnmuteAllAmps(State *state, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent)
        , m_state(state)
    {
        setText(QString("Unmute All Amps"));
    }

    auto undo() -> void override
    {
        for (auto amp : m_state->ampsD10Raw()->getAllAmps()) {
            amp->setMute(true);
        }
    }

    auto redo() -> void override
    {
        for (auto amp : m_state->ampsD10Raw()->getAllAmps()) {
            amp->setMute(false);
        }
    }

private:
    State *m_state;
};
} // namespace jatozy::store::commands