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

#include <iostream>
#include <cstring>
#include "graphdata.h"

void loadGraphData(graphdata myGraph,AdjacencyList myList)
{
    edgeList *temporary;
    for( int i = 0; i<myList.vertexCount() ; i++ )
    {
        temporary = myList.returnEdgeList(i);

        while(temporary != NULL)
        {
            //number of nodes as neighbours
            myGraph.degreeCount[i]++;
            temporary = temporary->next;
        }
    }
}

void metaDescribe(graphdata myGraph,AdjacencyList myList)
{
    std::cout<<"Vertices: "<<myList.vertexCount()<<"\tEdges: "<<myList.edgeCount()<<"\n";
    //std::cout<<"\n";myList.desc(0);
    /*
    myList.desc(myList.vertexCount()-1);
    std::cout<<"\n";
    std::cout<<myList.vertexCount()-1<<"\t";
    myList.desc(myList.vertexCount()-2);
    std::cout<<"\n";
    std::cout<<myList.vertexCount()<<"\t";
    myList.desc(myList.vertexCount()-2);
     */
    std::cout<<"\n";
}

AdjacencyList createKgraph(int n){
    AdjacencyList resultant(n,(n*(n-1))/2);

    for (int i =0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            resultant.insert(i,j);
        }
    }

    return resultant;
}
int main() {


    std::string path;
    std::cout<<"File name with path:";
    std::cin>>path;

    char filedir[path.size()+1];
    strcpy(filedir,path.c_str());
    std::cout<<filedir;


    AdjacencyList thisList = loadData(filedir);
    //AdjacencyList thisList = createKgraph(2500);

    //D:\\GraphSet\\cfat\\c-fat500-10.clq-compliment.txt
    //D:\\GraphSet\\totest\\graph50-01.txt
    //D:\\GraphSet\\totest3\\johnson16-2-4.clq-compliment.txt
    //D:\\GraphSet\\JustC\\C1000.9.clq-compliment.txt
    //D:\\GraphSet\\JustC\\C2000.9.clq-compliment.txt
    //D:\\GraphSet\\san\\san1000.clq-compliment.txt
    //D:\\GraphSet\\MANN_a81.txt
    //D:\\GraphSet\\brock\\brock800_4.clq-compliment.txt


    //AdjacencyList thisList = createKgraph(400);
    //preprocessing to be handled at this part

    graphdata thisGraph;
    thisGraph.vertices =thisList.vertexCount();
    thisGraph.degreeCount = new long int[thisGraph.vertices] {0};
    thisGraph.isActive = new bool[thisGraph.vertices] {false};

    //50,100,500,1000,1200,1800,2400,2700,3000
    loadGraphData(thisGraph,thisList);
    //preprocessing has been done. Implement main solve from this point onwards
    //metaDescribe(thisGraph,thisList);
    auto start_time = std::chrono::high_resolution_clock ::now();
    auto result = vertex_cover_solve(thisGraph, thisList.edgeCount(),thisList);
    std::cout<<"\n";
    std::cout<<result;

    auto end_time = std::chrono::high_resolution_clock ::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout<<"\nTime taken: "<<duration.count();
    std::cout<<"\n";
    return 0;
}
