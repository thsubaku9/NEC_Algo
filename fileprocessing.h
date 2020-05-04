//
// Created by kernel on 26-01-2020.
//

#ifndef VERTEXCOVER_FILEPROCESSING_H
#define VERTEXCOVER_FILEPROCESSING_H

#endif //VERTEXCOVER_FILEPROCESSING_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct edgeList{
    int node;
    edgeList *next = NULL;
};

class AdjacencyList
{

private:
    edgeList **node;
    int vertices;
    long int edges;
    edgeList **lastPointer;    //lastPointer ref for fast insertion

public:
    AdjacencyList(int n, long int e)
    {
        vertices = n;
        edges = e;
        node = (edgeList**)malloc(sizeof(edgeList *) * vertices);
        for(int i=0;i<n;i++)
        {node[i] = NULL;}

        lastPointer = (edgeList**)malloc(sizeof(edgeList *) * vertices);

        for(int i=0;i<n;i++)
        {lastPointer[i] = NULL;}
    }

    void insert(int v1, int v2)
    {
        if(node[v1] == NULL)        //first assignment
        {
            node[v1] = new edgeList();
            node[v1]->node = v2 ;
            lastPointer[v1] = node[v1];
        } else{
            lastPointer[v1]->next = new edgeList();
            lastPointer[v1] = lastPointer[v1]->next;
            lastPointer[v1]->node = v2;
        }

        //need to do reverse assignment too
        if(node[v2] == NULL)
        {
            node[v2] = new edgeList();
            node[v2]->node = v1;
            lastPointer[v2] = node[v2];
        } else{
            lastPointer[v2]->next = new edgeList();
            lastPointer[v2] = lastPointer[v2]->next;
            lastPointer[v2]->node = v1;
        }

    }

    void desc(int v1)
    {
        edgeList *toDesc = node[v1];
        while(toDesc!=NULL)
        {std::cout<<toDesc->node<<" -> ";toDesc=toDesc->next;}
        std::cout<<"NULL\n";
    }

    int vertexCount()
    { return vertices; }

    long int edgeCount()
    { return edges; }
    edgeList *returnEdgeList(int vertex)
    {
        return node[vertex];
    }
};

//class AdjacencyMatrix
//{
//private:
//    bool **adjMat;
//    int vertices;
//    long int edges;
//
//public:
//    AdjacencyList(int n, long int e)
//    {
//        vertices = n;
//        edges = e;
//        node = (edgeList**)malloc(sizeof(edgeList *) * vertices);
//        for(int i=0;i<n;i++)
//        {node[i] = NULL;}
//
//        *lastPointer = new edgeList[vertices];
//    }
//
//    void insert(int v1, int v2)
//    {
//        if(node[v1] == NULL)        //first assignment
//        {
//            node[v1] = new edgeList();
//            node[v1]->node = v2 ;
//            lastPointer[v1] = node[v1];
//        } else{
//            lastPointer[v1]->next = new edgeList();
//            lastPointer[v1] = lastPointer[v1]->next;
//            lastPointer[v1]->node = v2;
//        }
//
//        //need to do reverse assignment too
//        if(node[v2] == NULL)
//        {
//            node[v2] = new edgeList();
//            node[v2]->node = v1;
//            lastPointer[v2] = node[v2];
//        } else{
//            lastPointer[v2]->next = new edgeList();
//            lastPointer[v2] = lastPointer[v2]->next;
//            lastPointer[v2]->node = v1;
//        }
//
//    }
//
//    void desc(int v1)
//    {
//        edgeList *toDesc = node[v1];
//        while(toDesc!=NULL)
//        {std::cout<<toDesc->node<<" -> ";toDesc=toDesc->next;}
//        std::cout<<"NULL\n";
//    }
//
//    int vertexCount()
//    { return vertices; }
//
//    long int edgeCount()
//    { return edges; }
//    edgeList *returnEdgeList(int vertex)
//    {
//        return node[vertex];
//    }
//};

//FUNCTIONS
std::vector<int> toLocations(std::string info,std::string splitPattern);

AdjacencyList loadData(char* filename);