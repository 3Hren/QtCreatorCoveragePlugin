#pragma once

#include "codecoverage_global.h"

#include <extensionsystem/iplugin.h>

class ActionManager;
class StateMachine;
class WizardManager;

namespace CodeCoverage {
namespace Internal {

class CodeCoveragePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    ActionManager *actionManager;
    StateMachine *stateMachine;
    WizardManager *wizardManager;
public:
    CodeCoveragePlugin();
    ~CodeCoveragePlugin();
    
    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();
};

} // namespace Internal
} // namespace CodeCoverage
