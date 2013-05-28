/*
 * Copyright 2012 Aarhus University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TRACEBUILDER_H
#define TRACEBUILDER_H

#include "trace.h"


namespace artemis
{



/*
 *  A trace of the entire execution along a single path.
 */

class Trace
{
    // TODO: this is just a list of TraceNode, so maybe doesn't need its own object?


};





/*
 *  A trace of the entire execution along a single path.
 */

class TraceBuilder
{
public:
    TraceBuilder();

    void beginRecording();
    void endRecording();
    TraceNodePtr trace();


};


} // namespace artemis

#endif // TRACEBUILDER_H