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

#include "fileprocessing.h"

using namespace std;

vector<int> toLocations(string info,string splitPattern)
{
    int len = info.size();
    int patternlen = splitPattern.size();

    bool isLocation = false;

    vector<int> locations;
    for(int i=0;i<len;i++)
    {
        isLocation = true;

        for(int k=0;k<patternlen;k++)
        {
            if(info[i+k] != splitPattern[k])
            {
                isLocation = false;
                break;
            }
        }
        if(isLocation){ locations.push_back(i); i+=patternlen; }
    }
    return locations;
}

AdjacencyList loadData(char* filename)
{

    char stuff[10],stuff2[10], linetype;
    int vertices,edges;
    int node1,node2;
    fstream fileReader;
    fileReader.open(filename,fileReader.in);

    fileReader >> stuff >>stuff2 >> vertices >>edges;
    std::cout<<"VERTICES:";
    std::cout<<vertices;
    std::cout<<"EDGES:";
    std::cout<<edges;
    std::cout<<"\n";
    AdjacencyList graphList(vertices,edges);

    for(int i =0; i<edges; i++)
    {
        if(fileReader.eof())
        {std::cout<<"FILE IS BROKEN";}
        else{
            fileReader >> linetype >> node1 >> node2;
            //unsigned int toInsert1 = (unsigned int)node1;
            //unsigned int toInsert2 = (unsigned int)node2;
            graphList.insert(node1-1,node2-1);
        }
        //std::cout<<"\nLine:"<<i;
    }



    fileReader.close();
    return graphList;

    //--------------
    /*
    string data;
    fstream file;
    string splitPattern(" ");

    file.open(filename, file.in );
    //initial info
    getline(file,data);

    vector<int> locations = toLocations(data,splitPattern);
    locations.push_back(data.size());
    long int values[2];
    int startingLoc = locations[1]+1;

    //obtain nodes and edges
    for( int i = 2; i <locations.size(); i++)
    {
        char val[locations[i] - startingLoc +1]; int index = 0;
        for(int j = startingLoc; j < locations[i]; j++)
        { val[index++] = data[j]; }
        val[index]='\0';
        values[i -2] = atoi(val);
        startingLoc = locations[i]+1;
    }

    AdjacencyList graphList(values[0],values[1]);
    // main part of reading the edges
    while(getline(file,data))
    {
        vector<int> locations = toLocations(data,splitPattern);
        locations.push_back(data.size());
        startingLoc = locations[0]+1;

        unsigned int tempStore[2];

        for( int i = 1; i <locations.size(); i++)
        {
            char val[locations[i] - startingLoc +1]; int index = 0;
            for(int j = startingLoc; j < locations[i]; j++)
            { val[index++] = data[j]; }
            val[index]='\0';
            tempStore[i -1] = (unsigned int)atoi(val);
            startingLoc = locations[i]+1;

        }
        graphList.insert(tempStore[0] - 1, tempStore[1] - 1);
    }
    file.close();
    return graphList;
     */
}
