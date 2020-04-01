#include "widget/effectwidgetutils.h"
#include "widget/weffectparameterknobcomposed.h"

namespace {
const QString effectGroupSeparator = "_";
const QString groupClose = "]";
} // anonymous namespace

void WEffectParameterKnobComposed::setupEffectParameterSlot(const ConfigKey& configKey) {
    EffectParameterSlotBasePointer pParameterSlot =
            m_pEffectsManager->getEffectParameterSlot(EffectManifestParameter::ParameterType::KNOB, configKey);
    if (!pParameterSlot) {
        qWarning() << "EffectParameterKnobComposed" << configKey <<
                "is not an effect parameter.";
        return;
    }
    setEffectKnobParameterSlot(pParameterSlot);
    setFocusPolicy(Qt::NoFocus);
}

void WEffectParameterKnobComposed::setEffectKnobParameterSlot(
        EffectParameterSlotBasePointer pParameterSlot) {
    m_pEffectParameterSlot = pParameterSlot;
    if (m_pEffectParameterSlot) {
        connect(m_pEffectParameterSlot.data(), SIGNAL(updated()),
                this, SLOT(parameterUpdated()));
    }
    parameterUpdated();
}

void WEffectParameterKnobComposed::parameterUpdated() {
    if (m_pEffectParameterSlot) {
        setBaseTooltip(QString("%1\n%2").arg(
                       m_pEffectParameterSlot->name(),
                       m_pEffectParameterSlot->description()));
    } else {
        // The knob should be hidden by the skin when the parameterX_loaded ControlObject
        // indicates no parameter is loaded, so this tooltip should never be shown.
        setBaseTooltip("");
    }
}
