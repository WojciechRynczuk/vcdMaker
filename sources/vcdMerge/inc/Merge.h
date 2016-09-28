/// @file Merge.h
///
/// The merging unit.
///
/// @par Full Description
/// The class defines the merging entity.
///
/// @ingroup Merge
///
/// @par Copyright (c) 2016 vcdMaker team
///
/// Permission is hereby granted, free of charge, to any person obtaining a
/// copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included
/// in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
/// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.

#pragma once

/// @defgroup Merge Merge
///
/// @brief Merge related classes.
///
/// @par Full Description
/// The group gathers classes needed by the merge application.

#include "Source.h"

namespace MERGE
{
    /// The merging unit class. Allows for merging different
	/// signal sources.

    /// The merging unit class.
    class Merge
    {
        public:
            /// The merge constructor.
            ///
            /// @param verboseMode 'true' enables the verbose mode.
			Merge(bool verboseMode) : 
				m_Sources(),
				m_VerboseMode(verboseMode),
				m_pMerged(NULL)
			{
			};

			~Merge()
			{
			}

			void Add(Source& source);
			void Join();
			SIGNAL::SignalDb* Get();

        private:
            /// A type defining a container for signal sources.
            using SignalSourcesT = std::vector<Source*>;

            /// The set of sources.
			SignalSourcesT m_Sources;

			/// The output database.
			SIGNAL::SignalDb* m_pMerged;

			/// Verbose mode.
			bool m_VerboseMode;
    };
}
