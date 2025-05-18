#pragma once

#include <memory>
#include <QObject>

namespace jatozy::model {
class AmpD10Model;
class UndoStackModel;
} // namespace jatozy::model

namespace jatozy::hardware_interface {
class Factory;
} // namespace jatozy::hardware_interface

namespace jatozy::store {
class State : public QObject
{
    Q_OBJECT
    Q_PROPERTY(jatozy::model::AmpD10Model *ampsD10 READ ampsD10Raw NOTIFY ampsD10Changed)
    Q_PROPERTY(
        jatozy::model::UndoStackModel *commandNames READ commandNamesRaw NOTIFY commandNamesChanged)

public:
    using AmpD10Model = jatozy::model::AmpD10Model;
    using UndoStackModel = jatozy::model::UndoStackModel;

public:
    explicit State(
        std::shared_ptr<jatozy::hardware_interface::Factory> const &hardwareFactory,
        QObject *parent = nullptr);
    ~State() override = default;

    auto ampsD10Raw() const -> AmpD10Model *;
    auto commandNamesRaw() const -> UndoStackModel *;

signals:
    auto ampsD10Changed() -> void;
    auto commandNamesChanged() -> void;

private:
    std::shared_ptr<AmpD10Model> m_ampsD10;
    std::shared_ptr<UndoStackModel> m_commandNames;
};
} // namespace jatozy::store