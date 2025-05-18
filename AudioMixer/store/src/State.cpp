#include "jatozy/store/State.h"
#include <jatozy/model/AmpD10Model.h>
#include <jatozy/model/UndoStackModel.h>

namespace jatozy::store {

State::State(
    std::shared_ptr<jatozy::hardware_interface::Factory> const &hardwareFactory, QObject *parent)
    : QObject(parent)
    , m_ampsD10(std::make_shared<AmpD10Model>(hardwareFactory))
    , m_commandNames(std::make_shared<UndoStackModel>())
{}

auto State::ampsD10Raw() const -> AmpD10Model *
{
    return m_ampsD10.get();
}

auto jatozy::store::State::commandNamesRaw() const -> UndoStackModel *
{
    return m_commandNames.get();
}
} // namespace jatozy::store