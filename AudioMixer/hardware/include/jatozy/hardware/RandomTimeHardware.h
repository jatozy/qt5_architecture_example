#pragma once

#include "jatozy/hardware_interface/Hardware.h"
#include <memory>

class QTimer;

namespace jatozy::hardware {
class RandomTimeHardware : public jatozy::hardware_interface::Hardware
{
public:
    explicit RandomTimeHardware(QObject *parent = nullptr);
    ~RandomTimeHardware() override = default;

    auto setGain(float const value) -> void override;
    auto gain() -> float override;
    auto setMute(bool const value) -> void override;
    auto mute() -> bool override;

private:
    float m_gain{1.0f};
    bool m_mute{false};
    std::shared_ptr<QTimer> m_timer;
};
} // namespace jatozy::hardware