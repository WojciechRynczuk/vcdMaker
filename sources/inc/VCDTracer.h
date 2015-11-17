/*!
  @file vcdtracer.h

  The VCD generation module.

  @par Full Description
  The class provides means for collecting signals
  and storing the data in the VCD format.

  @if REVISION_HISTORY_INCLUDED
  @par Edit History
  @li [0]    wojciech.rynczuk@wp.pl    16-DEC-2014    Initial file revision.
  @endif

  @ingroup Tracer

  @par Copyright (c) MMXV Wojciech Rynczuk

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.

*/
#ifndef __VCDTRACER_H__
#define __VCDTRACER_H__

/*!
    @defgroup Tracer Tracer

    @brief The VCD tracer core.

    @par Full Description
    The Tracer subsystem is the core of the application. It is responsible
    for collecting the signals and storing them in the VCD format.

*/

// SYSTEM INCLUDES
#include <fstream>    //std::ofstream
#include <string>     //std::string
#include <map>        //std::map
#include <set>        //std::multiset
#include <vector>     //std::vector

// C PROJECT INCLUDES
// (none)

// C++ PROJECT INCLUDES
#include "signal.h"

// FORWARD REFERENCES
// (none)

namespace TRACER
{

//!  This class collects signals and creates the output VCD file.
    /*!
      The class provides means for storing signals and creating
      the output VCD file.
    */
    class VCDTracer
    {
        public:
            // PUBLIC ENUMERATOR
            //! This enumerator defines time units in which signals are timestamped.
            struct TimeUnit
            {
                //! Time units in which signals are timestamped.
                enum _TimeUnit
                {
                    s = 0U,
                    ms,
                    us,
                    ns,
                    ps,
                    fs,
                    invalid
                };
            };

            // PUBLIC METHODS

            //! The VCDTracer constructor.
            /*!
              The constructor takes two arguments. The first one is the name of the
              output VCD file. The second one is the selection of time units in which
              logged signals are timestamped.
            */
            VCDTracer(std::string const &outputFile, TimeUnit::_TimeUnit tunit);

            //! Log a signal.
            /*!
              This method adds a signal to the signals' container.
              IMPORTANT!!! The signals do not have to be ordered (in the terms of time).
              They will be re-ordered automatically upon dumping the VCD file.
            */
            void Log(const SIGNAL::Signal *signal);

            //! Create the output VCD file.
            void Dump();

            //! The default destructor.
            ~VCDTracer();

        private:
            // PRIVATE TYPES
            //!A type defining a container for pointers to Signal objects.
            typedef std::multiset<const SIGNAL::Signal *, SIGNAL::Signal>  SignalCollectionT;

            //!A type defining a state of signals.
            typedef std::map<std::string, const SIGNAL::Signal *>  SignalStateT;

            // PRIVATE METHODS
            //! Generate the VCD header.
            void GenerateHeader();

            //! Generate the basic header information.
            void GenerateBasicInformation();

            //! Generate the signals structure within the header.
            void GenerateSignalStructure();

            //! Generate the signals footprints within the header.
            void GenerateSignalDefaults();

            //! Generate the VCD body.
            void GenerateBody();

            //! Dump signals states with the given timestamp.
            void DumpSignals(uint64_t timestamp);

            //! Split the signal name into fields: the module, the sub-module(s), the signal name.
            std::vector<std::string> SplitSignal(std::string name, const char delim);

            // MEMBER VARIABLES
            //! The VCD output file.
            std::ofstream m_File;

            //! The VCD time unit in which the signals are timestamped.
            std::string m_TimeUnit;

            //! The current signals state.
            SignalStateT m_SignalState;

            //! The previous signals state.
            SignalStateT m_LastSignalState;

            //! The container for the signals.
            SignalCollectionT m_SignalSet;
    };

}

#endif

