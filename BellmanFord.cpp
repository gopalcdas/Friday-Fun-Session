#include <stdio.h>
#include <limits>
#include <string>
#include <math.h>

using namespace std;

#define EXTRA_CURRENCY "0"

struct Vertex
{
  string name;
};

struct Edge
{
  int fromId;
  int toId;
  double cost;
};

struct Graph
{
  Vertex *vertices;
  Edge *edges;
};

void SetVertex(Vertex* vertex, string name)
{
  vertex->name = name;
}

void SetEdge(Edge* edge, int sourceId, int destinationId, double cost)
{
  edge->fromId = sourceId;
  edge->toId = destinationId;
  edge->cost = cost;
}

double NegativeLogRate(double rate)
{
  return -log(rate);
}

Graph* GetInputGraphProfit(int &numberOfVertices, int &numberOfEdges)
{
  numberOfVertices = 4;
  numberOfEdges = 6;

  Graph *graph = new Graph;
  graph->vertices = new Vertex[numberOfVertices];
  graph->edges = new Edge[numberOfEdges];

  SetVertex(&graph->vertices[0], EXTRA_CURRENCY);
  SetVertex(&graph->vertices[1], "1");
  SetVertex(&graph->vertices[2], "2");
  SetVertex(&graph->vertices[3], "3");
  
  SetEdge(&graph->edges[0], 0, 1, 0);
  SetEdge(&graph->edges[1], 0, 2, 0);
  SetEdge(&graph->edges[2], 0, 3, 0);

  SetEdge(&graph->edges[3], 1, 2, 20);
  SetEdge(&graph->edges[4], 1, 3, 40);
  SetEdge(&graph->edges[5], 3, 2, -30);

  return graph;
}

void InitializeDistance(double *distance, int numberOfVertices)
{
  for(int i=0; i<numberOfVertices; i++)
    distance[i] = numeric_limits<double>::max();
}

void InitializePredecessor(int *predecessor, int numberOfVertices)
{
  for(int i=0; i<numberOfVertices; i++)
    predecessor[i] = -1;
}

bool IsEqual(double f, double s)
{
  return std::fabs(f - s) < std::numeric_limits<double>::epsilon();
}

bool Relax (Edge *e, double* distance, int* predecessor)
{
  if(!IsEqual(numeric_limits<double>::max(), distance[e->fromId]) 
     && distance[e->toId] > distance[e->fromId] + e->cost)
  {
    distance[e->toId] = distance[e->fromId] + e->cost;
    predecessor[e->toId] = e->fromId;
    return true;
  }

  return false;
}

bool BellmanFord(Graph *graph, int numberOfVertices, int numberOfEdges, int source, double* distance, int* predecessor, int &edgeWithNegativeCycle)
{
  distance[source] = 0;

  bool valueChanged;
  for(int i=0; i<numberOfVertices-1; i++)
  {
    valueChanged = false;
    for(int j=0; j<numberOfEdges; j++)
      valueChanged = Relax(&graph->edges[j], distance, predecessor) || valueChanged;

    if(!valueChanged)
      return true;
  }

  for(int j=0; j<numberOfEdges; j++)
    if(Relax(&graph->edges[j], distance, predecessor))
    {
      edgeWithNegativeCycle = j;
      return false;
    }
}

void PrintCycle(Graph* graph, int *predecessor, int currentVertex, int firstVertex)
{
  currentVertex = predecessor[currentVertex];
  if(currentVertex == firstVertex)
    return;
		
  PrintCycle(graph, predecessor, currentVertex, firstVertex);
  printf("-> %s ", graph->vertices[currentVertex].name.c_str());
}

void PrintResult(bool success, double* distance, int numberOfVertices)
{
	if(!success)
		return;

	for(int i=1; i<numberOfVertices; i++)
		printf("[%d]=%f\n", i, distance[i]);
}

void Call(Graph *graph, int numberOfVertices, int numberOfEdges)
{
  double *distance = new double[numberOfVertices];
  int *predecessor = new int[numberOfVertices];

  InitializeDistance(distance, numberOfVertices);
  InitializePredecessor(predecessor, numberOfVertices);

  int edgeWithNegativeCycle;
  bool success = BellmanFord(graph, numberOfVertices, numberOfEdges, 0, distance, predecessor, edgeWithNegativeCycle);

  PrintResult(success, distance, numberOfVertices);
}

int main()
{
  int numberOfVertices, numberOfEdges;

  Graph* graph = GetInputGraphProfit(numberOfVertices, numberOfEdges);
  Call(graph, numberOfVertices, numberOfEdges);
}
