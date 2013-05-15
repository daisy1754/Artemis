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

#ifndef SEARCH_H
#define SEARCH_H


#include "pathtree.h"



namespace artemis
{




class TreeSearch
{
public:
    PathTreeUnexploredPtr chooseNextTarget() = 0; // What should the signature for this be?
};


class DepthFirstSearch : TreeSearch
{
public:
    DepthFirstSearch(PathTreeNodePtr tree);

    PathTreeUnexploredPtr chooseNextTarget();
};




}

#endif // SEARCH_H