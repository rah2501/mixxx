#ifndef EFFECTSBACKEND_H
#define EFFECTSBACKEND_H

#include <QObject>
#include <QList>
#include <QSet>
#include <QString>

#include "effects/defs.h"
#include "effects/effectslot.h"
#include "preferences/usersettings.h"

#include "util/memory.h"

class EffectProcessor;

// EffectsBackend enumerates available effects and instantiates EffectProcessors
class EffectsBackend {
  public:
    virtual ~EffectsBackend() {};

    virtual EffectBackendType getType() const = 0;

    // returns a list sorted like it should be displayed in the GUI
    virtual const QList<QString> getEffectIds() const = 0;
    virtual EffectManifestPointer getManifest(const QString& effectId) const = 0;
    virtual const QList<EffectManifestPointer> getManifests() const = 0;
    virtual bool canInstantiateEffect(const QString& effectId) const = 0;

    virtual std::unique_ptr<EffectProcessor> createProcessor(
        const EffectManifestPointer pManifest) const = 0;

    static EffectBackendType backendTypeFromString(const QString& string) {
        if (string == "LV2") {
            return EffectBackendType::LV2;
        } else {
            return EffectBackendType::BuiltIn;
        }
    }

    static QString backendTypeToString(EffectBackendType backendType) {
        if (backendType == EffectBackendType::BuiltIn) {
            return "BuiltIn";
        } else if (backendType == EffectBackendType::LV2) {
            return "LV2";
        } else {
            return "Unknown";
        }
    }
};

#endif /* EFFECTSBACKEND_H */
