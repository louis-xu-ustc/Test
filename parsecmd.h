/*!
 ***********************************************************
 * @file parsecmd.h
 * @brief A file defining the function for parsing commands
 *
 * @section License 
 *
 * Copyright (c) 2015- Delphi Automotive. All rights 
 * reserved.
 *
 * @section changeLogs Change Logs
 *
 * @author Yunpeng Xu (yunpeng.xu@aptiv.com)
 * @date 04/02/2018
 * @remark port task part to qnx.
 *         - replace boost program_options with TCLAP.
 *         - add self-defined VariablesMap class
 *
 ***********************************************************
 */

/**********************************************************
  Copyright (c) 2014-2015 Ottomatika, Inc.
 **********************************************************/

/**********************************************************
  Copyright (c) 2010-2013 Carnegie Mellon University,
  All rights reserved.

  This source code was developed in part with support from 
  sponsors including General Motors, the National Science 
  Foundation and the US Department of Transportation.

  Use of this software is strictly governed by agreements 
  between Carnegie Mellon University and various sponsors.

  Users of this software must also be fully aware and agree 
  that Carnegie Mellon does not guarantee the correct 
  functioning of this software in any system. Carnegie 
  Mellon or any of its affiliates will not be liable for any 
  damage and/or penalties resulting from the use of this 
  software. Any user of this software takes complete 
  responsibility for the use of any software or design.
 **********************************************************/

/*
 ***********************************************************
 * parsecmd.h
 * Bryan Salesky
 * 09/02/2006
 *
 * Copyright (C) 2006 CMU. All rights reserved.
 ***********************************************************
 */
#ifndef _PARSE_CMD_H_
#define _PARSE_CMD_H_

#include <algorithm>
#include <unordered_map>
#include <string>

class VariablesMap 
{
    public:
        static const std::string helpOption;
        static const std::string instanceNameOption;
        static const std::string configTestOption;
        static const std::string logLevelOption;
        static const std::string versionOption;

        VariablesMap();
        ~VariablesMap();
        bool count(const std::string &cmd) const;
        std::string getCmdValue(const std::string &cmd) const;
        void setCmdValue(const std::string &cmd, const std::string &val);

    private:
       
        // key - command, value - value of the command
        std::unordered_map<std::string, std::string> cmdMap;
};

VariablesMap parseCommandLine( int argc, char **argv );

#endif
