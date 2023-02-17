#ifndef COMMANDDISPATCHER_H
#define COMMANDDISPATCHER_H

#include <compare> // needed for MSVC - not sure why?
#include "CommandInterpreter.h"
#include "AppObservers.h"
#include "CommandFactory.h"

#ifdef ENABLE_TESTING_INTERFACE
#include "CoreCommands.h"
#include "CommandManager.h"
#include "StoredProcedure.h"
#endif

#endif