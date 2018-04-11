#include "parsecmd.h"
#include <string>
#include <iostream>

using namespace std;

int main( int argc, char** argv )
{
    // parse the command line into a var map
    VariablesMap opts = parseCommandLine( argc, argv );

    if (opts.count("logLevel")) 
    {
        cout << opts.getCmdValue("logLevel") << endl;
    }

    if (opts.count("instanceName"))
    {
        cout << opts.getCmdValue("instanceName") << endl;
    }

    if (opts.count("configTest"))
    {
        cout << opts.getCmdValue("configTest") << endl;
    }
}
