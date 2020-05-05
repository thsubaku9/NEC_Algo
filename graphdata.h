/*

Copyright 2020 Kaustubh KJ

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/

#ifndef VERTEXCOVER_GRAPHDATA_H
#define VERTEXCOVER_GRAPHDATA_H

#endif //VERTEXCOVER_GRAPHDATA_H

#include <iostream>
#include <vector>
#include <chrono>
#include "fileprocessing.h"

struct graphdata{
    int vertices;
    bool *isActive; //0 -> node is no longer useful , 1 -> node is useful
    long int *degreeCount;
};

long int vertex_cover_solve(graphdata Graphdata, long int net_edges,AdjacencyList myList);

void mark_surrounding_nodes(graphdata Graphdata, long int selected_vertex);

void unmark_node(graphdata Graphdata, long int selected_vertex);

void finalize_utility(graphdata Graphdata);

int pick_optimal(graphdata Graphdata,AdjacencyList myList, bool &toContinue);

long int returnEdges(graphdata Graphdata,long int selected_vertex);

long int neighbourhood_score(graphdata Graphdata, AdjacencyList myList, int nodeSelected);

long int vertices_disabled(graphdata Graphdata, AdjacencyList myList, int nodeSelected);
