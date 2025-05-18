#pragma once

#include "jatozy/model/Amp.h"
#include "jatozy/model/AmpD10Model.h"
#include "jatozy/store/State.h"
#include <QUndoCommand>

namespace jatozy::store::commands {
class AddAmp : public QUndoCommand
{
public:
    using IdType = jatozy::model::Amp::IdType;

public:
    AddAmp(State *state, QUndoCommand *parent = nullptr)
        : QUndoCommand(parent)
        , m_state(state)
    {
        setText(QString("Add New Amp"));
    }

    auto undo() -> void override { m_state->ampsD10Raw()->removeAmp(m_id); }

    auto redo() -> void override { m_id = m_state->ampsD10Raw()->emplaceNewAmp(); }

private:
    State *m_state;
    IdType m_id;
};
} // namespace jatozy::store::commands