/*******************************************************************************
*
* Maximum Bandwidth Path using Kruskal's algorithm
*
*******************************************************************************/

#include <MaxBWPath.h>


int main()
{
  Heap<int> *Heap1 = new Heap<int>();

  Heap1->Insert(1,2,3);
  Heap1->Insert(4,5,6);
  Heap1->Insert(7,8,9);
  Heap1->Delete(0);
  Heap1->print();



  cout<<"Maximum edge : "<<Heap1->MaxEdge()<<" "<<Heap1->MaxEdge2()<<endl;

  /* Creating graphs of 5000 nodes as an adjacency list */
  LinkedList<int> *Graph_1 = new LinkedList<int>[NUMBER_OF_VERTICES];

  srand(42);
  /* Construct a cycle of connected nodes */
  for(unsigned int i = 0;i<NUMBER_OF_VERTICES;i++)
  {
    unsigned int weight_insert = rand()%100;
    if(i==(NUMBER_OF_VERTICES-1))
    {
      Graph_1[i].insert(i,99999);
      Graph_1[i].insert(0,weight_insert);
      continue;
    }
    Graph_1[i].insert(i,99999);
    Graph_1[i].insert(i+1,weight_insert);
  }

  for(unsigned int i = 0;i<NUMBER_OF_VERTICES;i++)
  {
    for(unsigned int NV = 0;NV<(NUMBER_OF_VERTICES);NV++)
    {
      if((rand()%10000)<=4)
      {
        unsigned int weight_insert = rand()%100;
        Graph_1[i].insert(NV,weight_insert);
        Graph_1[NV].insert(i,weight_insert);
      }

    }

  }

  Heap<int> *Heap2 = new Heap<int>();


  for(unsigned int idx = 0; idx<NUMBER_OF_VERTICES;idx++)
  {
    std::vector<int> AdjVert_temp = Graph_1[idx].GetAdjacentNodes();
    std::vector<int> AdjWeights_temp = Graph_1[idx].GetAdjacentNodesWeights();

    for(unsigned int count = 1;count<=(AdjVert_temp.size()-1);count++)
    {
      int AdjNode = (int)AdjVert_temp[count];
      int AdjNodeWeight = (int)AdjWeights_temp[count];

      Heap2->Insert(idx,AdjNode,AdjNodeWeight);


    }
  }

  



  return 0;
}
