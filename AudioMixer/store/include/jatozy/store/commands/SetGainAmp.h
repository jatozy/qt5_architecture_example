#pragma once

#include "jatozy/model/Amp.h"
#include "jatozy/model/AmpD10Model.h"
#include "jatozy/store/State.h"
#include <QUndoCommand>

namespace jatozy::store::commands {
class SetGainAmp : public QUndoCommand
{
public:
    using IdType = jatozy::model::Amp::IdType;

public:
    SetGainAmp(State *state, IdType id, float gain, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent)
        , m_state(state)
        , m_id(id)
        , m_gain(gain)
    {
        m_previousGain = amp()->gain();
        setText(QString("Set Gain of %1 to %2").arg(m_id.toString(), gain));
    }

    auto undo() -> void override { amp()->setGain(m_previousGain); }
    auto redo() -> void override { amp()->setGain(m_gain); }

private:
    auto amp() const -> jatozy::model::Amp * { return m_state->ampsD10Raw()->getAmp(m_id).value(); }

private:
    State *m_state;
    IdType m_id;
    float m_gain;
    float m_previousGain;
};
} // namespace jatozy::store::commands