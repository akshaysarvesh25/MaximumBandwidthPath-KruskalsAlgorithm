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
  return 0;
}
