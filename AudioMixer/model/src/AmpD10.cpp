#include "jatozy/model/AmpD10.h"
#include <jatozy/hardware_interface/Factory.h>
#include <jatozy/hardware_interface/Hardware.h>
#include <QRandomGenerator>

namespace jatozy::model {
AmpD10::AmpD10(std::shared_ptr<HardwareFactory> const &hardwareFactory, QObject *parent)
    : Amp(parent)
    , m_id(QUuid::createUuid())
    , m_hardware(hardwareFactory->create())
{
    connect(m_hardware.get(), &HardwareHardware::gainChanged, this, &AmpD10::onGainChanged);
    connect(
        m_hardware.get(), &HardwareHardware::inputLevelChanged, this, &AmpD10::onInputLevelChanged);
    connect(
        m_hardware.get(),
        &HardwareHardware::outputLevelChanged,
        this,
        &AmpD10::onOutputLevelChanged);
}

AmpD10::AmpD10(
    IdType id,
    float gain,
    bool mute,
    std::shared_ptr<HardwareFactory> const &hardwareFactory,
    QObject *parent)
    : AmpD10(hardwareFactory, parent)
{
    setGain(gain);
    setMute(mute);
    m_id = id;
}

auto AmpD10::gain() const -> float
{
    return m_hardware->gain();
}

auto AmpD10::setGain(float value) -> void
{
    if (qFuzzyCompare(gain(), value)) {
        return;
    }
    m_hardware->setGain(value);
    emit gainChanged();
}

auto AmpD10::mute() const -> bool
{
    return m_hardware->mute();
}

auto AmpD10::setMute(bool value) -> void
{
    if (mute() == value) {
        return;
    }
    m_hardware->setMute(value);
    emit muteChanged();
}

auto AmpD10::inputLevel() const -> float
{
    return m_inputLevel;
}

auto AmpD10::outputLevel() const -> float
{
    return m_outputLevel;
}

auto AmpD10::id() const -> IdType
{
    return m_id;
}

auto AmpD10::onGainChanged(float /*gain*/) -> void
{
    emit gainChanged();
}

auto AmpD10::onMuteChanged(bool /*value*/) -> void
{
    emit muteChanged();
}

auto AmpD10::onInputLevelChanged(float level) -> void
{
    if (!qFuzzyCompare(m_inputLevel, level)) {
        m_inputLevel = level;
        emit inputLevelChanged();
    }
}

auto AmpD10::onOutputLevelChanged(float level) -> void
{
    if (!qFuzzyCompare(m_outputLevel, level)) {
        m_outputLevel = level;
        emit outputLevelChanged();
    }
}

} // namespace jatozy::model