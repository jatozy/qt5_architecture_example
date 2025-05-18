#pragma once

#include "jatozy/model/Amp.h"
#include <memory>

namespace jatozy::hardware_interface {
class Factory;
class Hardware;
} // namespace jatozy::hardware_interface

namespace jatozy::model {
class AmpD10 : public Amp
{
public:
    using HardwareFactory = jatozy::hardware_interface::Factory;
    using HardwareHardware = jatozy::hardware_interface::Hardware;

public:
    AmpD10(std::shared_ptr<HardwareFactory> const &hardwareFactory, QObject *parent = nullptr);
    AmpD10(
        IdType id,
        float gain,
        bool mute,
        std::shared_ptr<HardwareFactory> const &hardwareFactory,
        QObject *parent = nullptr);
    ~AmpD10() override = default;

    auto gain() const -> float override;
    auto setGain(float value) -> void override;
    auto mute() const -> bool override;
    auto setMute(bool value) -> void override;
    auto inputLevel() const -> float override;
    auto outputLevel() const -> float override;
    auto id() const -> IdType override;

private slots:
    auto onGainChanged(float value) -> void;
    auto onMuteChanged(bool value) -> void;
    auto onInputLevelChanged(float value) -> void;
    auto onOutputLevelChanged(float value) -> void;

private:
    float m_inputLevel{0.0f};
    float m_outputLevel{0.0f};
    IdType m_id;

    std::shared_ptr<HardwareHardware> m_hardware;
};
} // namespace jatozy::model