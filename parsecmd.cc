#include <iostream>
#include "parsecmd.h"
#include <tclap/CmdLine.h>

using namespace std;

const string VariablesMap::instanceNameOption = "instanceName";
const string VariablesMap::configTestOption = "configTest";
const string VariablesMap::logLevelOption = "logLevel";

VariablesMap::VariablesMap()
{
    cmdMap.clear();
}

VariablesMap::~VariablesMap()
{
    cmdMap.clear();
}

bool
VariablesMap::count(const string &cmd) const
{
    return cmdMap.count(cmd);
}

string
VariablesMap::getCmdValue(const string &cmd) const
{
    return cmdMap.at(cmd);
}

void
VariablesMap::setCmdValue(const string &cmd, const string &val)
{
    cmdMap[cmd] = val;
}

VariablesMap parseCommandLine( int argc, char **argv )
{
    VariablesMap vm;

    try
    {
        TCLAP::CmdLine cmd("Command Line Options", ' ', "1.0");
        /**
         * Define a value argument and add it to the command line.
         * A value arg defines a flag and a type of value that it expects
         */
        TCLAP::ValueArg<string> instanceNameArg("i", VariablesMap::instanceNameOption, "instance name", false, "exampleInstance", "the task's instance name");
        /**
         * Add the argument nameArg to the CmdLine object. The CmdLine object
         * uses this Arg to parse the command line.
         */
        cmd.add(instanceNameArg);

        TCLAP::ValueArg<string> configTestArg("c", VariablesMap::configTestOption, "configure check", false, "configureTest", "run a configuration check only (config, initialize, then exit)");
        cmd.add(configTestArg);

        TCLAP::ValueArg<string> logLevelArg("l", VariablesMap::logLevelOption, "log level", false, "logLevel", "run at an alternate log level");
        cmd.add(logLevelArg);

        // Parse the argv array
        cmd.parse(argc, argv);

        // Get the name parsed by each arg and store in the variable map
        string instanceNameVal = "";
        string configTestVal = "";
        string logLevelVal = "";

        if (instanceNameArg.isSet()) 
        {
            instanceNameVal = instanceNameArg.getValue();
            vm.setCmdValue(VariablesMap::instanceNameOption, instanceNameVal);
        }

        if (configTestArg.isSet())
        {
            configTestVal = configTestArg.getValue();
            vm.setCmdValue(VariablesMap::configTestOption, configTestVal);
        }

        if (logLevelArg.isSet())
        {
            logLevelVal = logLevelArg.getValue();
            vm.setCmdValue(VariablesMap::logLevelOption, logLevelVal);
        }

        if (cmd.hasHelpAndVersion()) {
            cout << "help and version is built-in" << endl;
        }
    } 
    catch (TCLAP::ArgException &e)  // catch any exceptions
    { 
        cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
    }
    return vm;
}
