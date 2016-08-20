/// @file SignalStructureBuilder.cpp
///
/// VCD signal structure builder class.
///
/// @ingroup Tracer
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

#include <algorithm>

#include "SignalStructureBuilder.h"

void TRACER::SignalStructureBuilder::Dump()
{
    SIGNAL::Signal::SignalNameFieldsT previous_fields;

    for (const auto &unique_signal : m_UniqueSignals)
    {
        const SIGNAL::Signal *signal = unique_signal.second;
        const SIGNAL::Signal::SignalNameFieldsT current_fields = signal->GetNameFields();

        bool found_mismatch = false;
        std::size_t continue_index = 0;

        std::tie(found_mismatch, continue_index) = FindContinuation(current_fields, previous_fields);

        if (found_mismatch)
        {
            EndScopesDownTo(previous_fields, continue_index);
        }

        ContinueScopes(continue_index, current_fields, signal);

        previous_fields = current_fields;
    }

    EndScopesDownTo(previous_fields, 0);
}

std::tuple<bool, std::size_t> TRACER::SignalStructureBuilder::FindContinuation(const SIGNAL::Signal::SignalNameFieldsT
        &currentFields,
        const SIGNAL::Signal::SignalNameFieldsT &previousFields)
{
    const std::size_t common_size = std::min(currentFields.size(), previousFields.size());

    for (std::size_t i = 0; i < common_size; ++i)
    {
        if (currentFields[i] != previousFields[i])
        {
            return std::make_tuple(true, i);
        }
    }

    return std::make_tuple(false, common_size);
}

void TRACER::SignalStructureBuilder::EndScopesDownTo(const SIGNAL::Signal::SignalNameFieldsT &fields,
        std::size_t lowerLimit)
{
    if (fields.empty())
    {
        return;
    }

    for (std::size_t j = fields.size() - 1; j > lowerLimit; --j)
    {
        DumpIndented("$upscope $end", j - 1);
    }
}

void TRACER::SignalStructureBuilder::ContinueScopes(std::size_t continueFrom,
        const SIGNAL::Signal::SignalNameFieldsT &fields,
        const SIGNAL::Signal *signal)
{
    for (std::size_t i = continueFrom; i < fields.size(); ++i)
    {
        if (i == (fields.size() - 1))
        {
            DumpIndented("$var " +
                         signal->GetType() + " " +
                         std::to_string(signal->GetSize()) + " " +
                         signal->GetName() + " " +
                         fields[i] + " $end",
                         i);
        }
        else
        {
            DumpIndented("$scope module " + fields[i] + " $end", i);
        }
    }
}
