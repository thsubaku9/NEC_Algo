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

#include "graphdata.h"


void unmark_node(graphdata Graphdata, long int selected_vertex)
{
    Graphdata.isActive[selected_vertex] = false;
}
void finalize_utility(graphdata Graphdata)
{
    //you really don't want to be stuck on singular nodes
    for(int i =0; i<Graphdata.vertices;i++ )
    {
        if(Graphdata.degreeCount[i]>0)
        {Graphdata.isActive[i] = true;}
        //else {std::cout<<i<<" is inactive\n";}
    }
}

int pick_optimal(graphdata Graphdata,AdjacencyList myList,bool &toContinue)
{
    //run one finds highest node degree
    //run two checks nodes with highest run degree and selects based on selection
    int currentBest;
    //disjoint nodes to be excluded
    long int currentHighest = 1;
    long int currentNS ;
    long int currentVD ;
    bool isFirst = true;

    for(int i = 0; i<Graphdata.vertices; i++)
    {
        if((currentHighest< Graphdata.degreeCount[i]||isFirst) && Graphdata.isActive[i]){
            currentHighest = Graphdata.degreeCount[i];
            currentBest = i;
            currentNS = neighbourhood_score(Graphdata,myList,i);
            currentVD = vertices_disabled(Graphdata,myList,i);
            toContinue = true;
            isFirst = false;
        }
        else if(currentHighest == Graphdata.degreeCount[i] && Graphdata.isActive[i]){
            //selection criteria ->
            //for all same valued nodes, select the one which has the lowest neighbourhood count score
            //incase of further collision, select the one which triggers highest node deactivation

            long int tempNS = neighbourhood_score(Graphdata,myList,i);
            int tempVD = vertices_disabled(Graphdata,myList,i);
            if(tempNS < currentNS || (tempNS == currentNS && tempVD > currentVD))
            {
                currentBest = i;toContinue = true;
            }
        }
    }

    return  currentBest;

}

long int neighbourhood_score(graphdata Graphdata, AdjacencyList myList, int nodeSelected)
{
    edgeList* temp = myList.returnEdgeList(nodeSelected);
    long int count = 0;
    while(temp!= NULL)
    {
        count+=Graphdata.isActive[temp->node]*Graphdata.degreeCount[temp->node];
        temp=temp->next;
    }
    return count;

}

long int vertices_disabled(graphdata Graphdata, AdjacencyList myList, int nodeSelected)
{
    edgeList* temp = myList.returnEdgeList(nodeSelected);
    long int count = 0;
    while(temp!= NULL)
    {
        count+= (Graphdata.isActive[temp->node]&&Graphdata.degreeCount[temp->node] == 1)?1:0 ;
        temp=temp->next;
    }
    return count;
}

void mark_surrounding_nodes(graphdata Graphdata, int selected_vertex,AdjacencyList myList)
{
    //reduce count of surrounding nodes IFF they are active ( continue logic)
    edgeList* temporaryList = myList.returnEdgeList(selected_vertex);

    while(temporaryList != NULL)
    {
        if(Graphdata.isActive[temporaryList->node] && Graphdata.degreeCount[temporaryList->node]>0){
            Graphdata.degreeCount[temporaryList->node]--;
            if(Graphdata.degreeCount[temporaryList->node] ==0)
            {
                unmark_node(Graphdata,temporaryList->node);
            }
        }
        temporaryList = temporaryList->next;
    }

}

long int returnEdges(graphdata Graphdata,long int selected_vertex)
{
    return  Graphdata.degreeCount[selected_vertex];
}

long int vertex_cover_solve(graphdata Graphdata, long int net_edges,AdjacencyList myList)
{
    long int vertex_count = 0;
    long int edges_covered = 0;
    bool toContinue = true;

    //perform your VCP solve here
    finalize_utility(Graphdata);
    int selected_vertex;

    bool isUsed[Graphdata.vertices] = {false};

    while (net_edges > edges_covered)
    {
        //select optimal vertex
        selected_vertex = pick_optimal(Graphdata,myList,toContinue);
        if(toContinue)
        {
            //critical section, do not modify this region
            //update edges covered
            isUsed[selected_vertex] = true;
            edges_covered += returnEdges(Graphdata,selected_vertex);
            //notify its surrounding nodes about update
            mark_surrounding_nodes(Graphdata,selected_vertex,myList);
            //remove utility of this node
            unmark_node(Graphdata,selected_vertex);
            //increment vertex_count
            vertex_count++;
            toContinue = false;
            //critical section over
        }
        else{
            break;
        }
    }

    /*
    for(int iter1=0 ; iter1<Graphdata.vertices; iter1++)
    {
        if(isUsed[iter1])std::cout<<iter1+1<<"\t";
    }
     */
    /*
    std::cout<<"\nEdge Count: "<<edges_covered<<" Total Edges: "<<net_edges;
    std::cout<<"\nMVC Count: "<<vertex_count<<" Total Vertices: "<<Graphdata.vertices;
    std::cout<<"\n";
    */

    return vertex_count;
}
