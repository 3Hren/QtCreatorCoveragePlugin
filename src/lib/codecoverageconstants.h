#pragma once

#include <projectexplorer/projectexplorerconstants.h>

const char RUN_ACTION_ID[] = "CodeCoverage.Action.Run";
const char WAIT_ACTION_ID[] = "CodeCoverage.Action.Wait";
const char RENDER_ACTION_ID[] = "CodeCoverage.Action.Render";

const char MENU_ID[] = "CodeCoverage.Menu";

const int RUN_ACTION_PRIORITY = ProjectExplorer::Constants::P_ACTION_BUILDPROJECT + 2;
const int WAIT_ACTION_PRIORITY = RUN_ACTION_PRIORITY;
