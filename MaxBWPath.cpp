/*******************************************************************************
*
* Maximum Bandwidth Path using Kruskal's algorithm
*
*******************************************************************************/

#include <MaxBWPath.h>
#include <MaxBWPathUtils.h>




int main()
{
  long time1 = getMicrotime();
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

  DisjointSets ds(NUMBER_OF_VERTICES);


  Graph MaxSpTree(NUMBER_OF_VERTICES);
  std::vector<int> vecu,vecv;
  while(Heap2->SizeOfHeapIsZero()!=0)
  {
    int u = Heap2->MaxEdge();
    int v = Heap2->MaxEdge2();
    int weight = Heap2->MaxWeight();



    int set_u = ds.find(u);
    int set_v = ds.find(v);
    if (set_u != set_v)
    {

            vecu.push_back(set_u);
            vecv.push_back(set_v);

       MaxSpTree.addEdge(u,v,weight);


      ds.merge(set_u, set_v);
    }
    Heap2->Delete(0);
  }

  int dest = 1549;
  int src = 68;
 MaxSpTree.DFS(src,dest);
cout<<endl;
 long time2 = getMicrotime();
 cout<<"Total execution time : "<<(time2-time1)*1e-6<<endl;



  std::remove("UData.txt");
  std::remove("VData.txt");
  std::ofstream outfile_TS1;

  outfile_TS1.open("UData.txt", std::ios_base::app);
  for(unsigned int i = 0;i<vecu.size();i++)
  {
    outfile_TS1<<std::setprecision(20)<<vecu[i]<< std::endl;
  }
  outfile_TS1.close();

  outfile_TS1.open("VData.txt", std::ios_base::app);
  for(unsigned int i = 0;i<vecv.size();i++)
  {
    outfile_TS1<<std::setprecision(20)<<vecv[i]<< std::endl;
    //std::cout<<"Writing file"<<std::endl;
  }
  outfile_TS1.close();






  return 0;
}
