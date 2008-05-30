// -*-Mode: C++;-*-
// $Id$

// * BeginRiceCopyright *****************************************************
// 
// Copyright ((c)) 2002-2007, Rice University 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// 
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// 
// * Neither the name of Rice University (RICE) nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
// 
// This software is provided by RICE and contributors "as is" and any
// express or implied warranties, including, but not limited to, the
// implied warranties of merchantability and fitness for a particular
// purpose are disclaimed. In no event shall RICE or contributors be
// liable for any direct, indirect, incidental, special, exemplary, or
// consequential damages (including, but not limited to, procurement of
// substitute goods or services; loss of use, data, or profits; or
// business interruption) however caused and on any theory of liability,
// whether in contract, strict liability, or tort (including negligence
// or otherwise) arising in any way out of the use of this software, even
// if advised of the possibility of such damage. 
// 
// ******************************************************* EndRiceCopyright *

//***************************************************************************
//
// File:
//   $Source$
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef Args_hpp
#define Args_hpp

//************************* System Include Files ****************************

#include <iostream>
#include <string>
#include <vector>

//*************************** User Include Files ****************************

#include <include/general.h>

#include <lib/analysis/Args.hpp>

#include <lib/support/diagnostics.h>
#include <lib/support/CmdLineParser.hpp>

//*************************** Forward Declarations **************************

//***************************************************************************

class Args : public Analysis::Args {
public:
  enum Mode_t {
    Mode_NULL,
    Mode_SourceCorrelation,
    Mode_ObjectCorrelation,
    Mode_RawDataDump
  };

  class Exception : public Diagnostics::Exception {
  public:
    Exception(const char* x,
	      const char* filenm = NULL, unsigned int lineno = 0)
      : Diagnostics::Exception(x, filenm, lineno) 
      { }

    Exception(std::string x,
	      const char* filenm = NULL, unsigned int lineno = 0) 
      : Diagnostics::Exception(x, filenm, lineno) 
      { }

    ~Exception() { }
  };


public: 
  Args(); 
  Args(int argc, const char* const argv[]);
  virtual ~Args(); 

  // Parse the command line
  void parse(int argc, const char* const argv[]);

  // Version and Usage information
  void printVersion(std::ostream& os) const;
  void printUsage(std::ostream& os) const;
  
  // Error
  static void printError(std::ostream& os, const char* msg) /*const*/;
  static void printError(std::ostream& os, const std::string& msg) /*const*/;

  // Dump
  virtual void dump(std::ostream& os = std::cerr) const;

public:
  // Parsed Data: Command
  static const std::string& getCmd() /*const*/;

  static void parse_sourceOpts(Args* args, const std::string& opts);
  static void parse_objectOpts(Args* args, const std::string& opts);
  static void parse_metricOpts(Args* args, const std::string& opts);

  // Parsed Data
  Mode_t mode;

  // Define additional metrics
  string txt_metrics;

  // Object Correlation args
  bool obj_metricsAsPercents;
  bool obj_showSourceCode;
  uint64_t obj_procThreshold;

private:
  void Ctor();
  void setHPCHome(); 

private:
  static CmdLineParser::OptArgDesc optArgs[];
  CmdLineParser parser;
}; 

#endif // Args_hpp 
