#include<stdlib.h>
#include <iostream>
#include<vector>
#include <cmath>
#include <math.h>
#include <string.h>
#include <time.h>
#include <random>
#include<algorithm>
#include <iomanip>
#include <fstream>
#include<stack>

using namespace std;

#define OUTPUT_LOG 0

typedef struct
{
  int EDGE_1;
  int EDGE_2;
}GraphEdge;


template <class T>
class Heap{

  private:
    std::vector<T> H;
    std::vector<T> EdgeWeight;
    std::vector<T> H_Edge2;
    T *tail;

    std::vector<T> Swap(std::vector<T> H_,int x,int y)
    {
      T temp = H_[x];
      H_[x] = H_[y];
      H_[y] = temp;


      return H_;
    }

    bool MakeHeap_Parent(std::vector<T> weight_MP, std::vector<T> H_,std::vector<T> H_Edge_2,int n)
    {
      //cout<<"Index : "<<" : "<<(n-1)/2<<endl;
      unsigned int Parent_idx = (double)(n-1)/2;
      //cout<<"Parent_idx : "<<Parent_idx<<endl;
      if(weight_MP[n]<=weight_MP[Parent_idx])
      {
        return true;

      }

      else
      {
        std::vector<T> H1 = Swap(H_,n,Parent_idx);
        std::vector<T> H2 = Swap(H_Edge_2,n,Parent_idx);
        H = H1;
        H_Edge2 = H2;
        int TempPos = position[H_[n]];
        position[H_[n]] = position[H_[Parent_idx]];
        position[H_[Parent_idx]] = TempPos;
        std::vector<T> weight_MP_1 = Swap(weight_MP,n,Parent_idx);
        EdgeWeight = weight_MP_1;
        return MakeHeap_Parent(weight_MP_1,H1,H2,Parent_idx);
      }

    }

    bool MakeHeap_Child(std::vector<T> weight11,std::vector<T> H11,std::vector<T> H22,int i)
    {
      if((2*i)+1>(H11.size()-1))
      {
        return true;
      }

      if(weight11[((2*i)+1)]>=weight11[((2*i)+2)])
      {
        if(weight11[i]>=weight11[((2*i)+2)])
        {
          return true;
        }
        else
        {
          H = Swap(H11,i,((2*i)+1));
          H_Edge2 = Swap(H22,i,((2*i)+1));
          int TempPos = position[H[i]];
          position[H[i]] = position[H[(2*i)+1]];
          position[H[(2*i)+1]] = TempPos;
          EdgeWeight = Swap(weight11,i,((2*i)+1));
          return MakeHeap_Child(EdgeWeight,H,H_Edge2,((2*i)+1));
        }
      }
      else
      {
        if(weight11[i]>=weight11[((2*i)+2)])
        {
          return true;
        }

        else
        {
          H = Swap(H11,i,((2*i)+2));
          H_Edge2 = Swap(H22,i,((2*i)+2));
          int TempPos = position[H[i]];
          position[H[i]] = position[H[(2*i)+1]];
          position[H[(2*i)+1]] = TempPos;
          EdgeWeight = Swap(weight11,i,((2*i)+2));
          return MakeHeap_Child(EdgeWeight,H,H_Edge2,((2*i)+2));
        }
      }
    }

  public:
    /* Position of the element in the heap */
    int position[5000];

    bool Insert(T value,T value_edge2,T weight)
    {
      if(H.size() == 0)
      {
        H.push_back(value);
        H_Edge2.push_back(value_edge2);
        EdgeWeight.push_back(weight);
        position[value] = H.size()-1;
        //cout<<"Added an element, H.size() is : "<<H.size()<<endl;
        return true;
      }

      else
      {
        //cout<<"size : "<<H.size()<<endl;
        H.push_back(value);
        H_Edge2.push_back(value_edge2);
        EdgeWeight.push_back(weight);

        position[value] = H.size()-1;
        //cout<<"Adding element to heap"<<endl;
        //cout<<"H.size() : "<<H.size()<<endl;
        return MakeHeap_Parent(EdgeWeight,H,H_Edge2,(H.size()-1));

      }
    }

    void print()
    {
      #if OUTPUT_LOG
      std::cout << "\033[1;33mContents of the heap : \033[0m"<<std::endl;
      for(unsigned int i = 0;i<H.size();i++)
      {
        std::cout<<H[i]<<" "<<H_Edge2[i]<<" "<<EdgeWeight[i]<<std::endl;
      }
      std::cout << "\033[1;33mEnd of heap\033[0m"<<std::endl;
      #endif
    }

    T MaxEdge()
    {
      return H[0];
    }

    T MaxEdge2()
    {
      return H_Edge2[0];
    }

    T MaxWeight()
    {
      return EdgeWeight[0];
    }


    bool Delete(T index)
    {
      if(H.size() == 0)
      {
        cout<<"Nothing to delete"<<endl;
        return false;
      }

      else if(H.size()==1)
      {
        cout<<"Deleting the last element in the tree.."<<endl;
        H.erase(H.end()-1);
        H_Edge2.erase(H_Edge2.end()-1);
        EdgeWeight.erase(EdgeWeight.end()-1);
        return true;

      }

      else
      {
        int TempPos1 = position[H[index]];
        position[H[index]] = -1;
        H[index] = H[H.size()-1];
        H_Edge2[index] = H_Edge2[H_Edge2.size()-1];
        position[H[H.size()-1]] = TempPos1;
        EdgeWeight[index] = EdgeWeight[EdgeWeight.size()-1];
        H.erase(H.end()-1);
        H_Edge2.erase(H_Edge2.end()-1);
        EdgeWeight.erase(EdgeWeight.end()-1);
        unsigned int P_idx = (double)(index-1)/2;

        if(EdgeWeight[index]>=EdgeWeight[P_idx])
        {
          return MakeHeap_Parent(EdgeWeight,H,H_Edge2,index);
        }
        else if((EdgeWeight[index]<=EdgeWeight[(2*index)+1])||(EdgeWeight[index]<=EdgeWeight[(2*index)+2]))
        {
          return MakeHeap_Child(EdgeWeight,H,H_Edge2,index);
        }
      }

    }

    int SizeOfHeapIsZero()
    {
      return H.size();
    }



};




#define NUMBER_OF_VERTICES 5000
#define NUMBER_OF_EDGES_PER_VERTEX_AVG 6
#define PERCENTAGE_VERTICES_NEIGHBORS 1000

#define INSERT_DEBUG_OUTPUT 0
#define DISPLAY_DEBUG_OUTPUT 1

using namespace std;

typedef enum
{
  STATUS_NONE = 0,
  STATUS_GRAPH_UNSEEN = 1,
  STATUS_GRAPH_FRINGE = 2,
  STATUS_GRAPH_INTREE = 3,
}NODE_STATUS;


typedef struct
{
  unsigned int NodeName;
  unsigned int NodeWeight;
}NodeAttributes;

template <class T>
struct SingleLinkedListNode{
  T data;
  T weight;
  NODE_STATUS NodeStatus;
  T Bandwidth;
  T dad;
  SingleLinkedListNode *NextNode;

  SingleLinkedListNode(){


  }

  SingleLinkedListNode(T val){

    this->data = val;
  }

  SingleLinkedListNode(T val,SingleLinkedListNode<T> NewNode){

    this->data = val;
    this->NextNode = NewNode;
  }


};




template <class T>
class LinkedList{

  private:
    SingleLinkedListNode<T> *root, *tail;

  public:
    void insert(T val,T EdgeWeight)
    {

      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode->data=val;
      tempNode->weight = EdgeWeight;
      tempNode->NodeStatus = STATUS_NONE;
      tempNode->NextNode=NULL;

      if(root)
      {
        #if INSERT_DEBUG_OUTPUT
        cout<<"Adding new elements "<<endl;
        #endif
        tail->NextNode=tempNode;
        tail=tempNode;
      }
      else
      {
        root=tempNode;
        tail=tempNode;
        tempNode=NULL;
        #if INSERT_DEBUG_OUTPUT
        cout<<"New root added : "<<val<<endl;
        #endif
      }

    }

    void display()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int i=0;
      //cout<<"\n"<<endl;
      while(tempNode!=NULL)
      {
        cout<<tempNode->data<<" -> ";
        tempNode=tempNode->NextNode;
      }
      cout<<"\n";
    }

    void MakeNodesUnseen()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int i=0;
      //cout<<"\n"<<endl;
        //cout<<tempNode->data<<" -> ";
      tempNode->NodeStatus = STATUS_GRAPH_UNSEEN;
      tempNode=tempNode->NextNode;

    }

    void MakeNodesIntree()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int i=0;
      tempNode->NodeStatus = STATUS_GRAPH_INTREE;
    }

    void MakeNodesFringe()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int i=0;
      tempNode->NodeStatus = STATUS_GRAPH_FRINGE;
    }

    void SetNodeBandwidth(T BWvalue)
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      //cout<<tempNode->data<<" -> ";
      tempNode->Bandwidth = BWvalue;

    }

    std::vector<int> GetAdjacentNodes()
    {
      std::vector<int> temp;
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      #if OUTPUT_LOG
      cout<<"Adjacent nodes : "<<endl;
      #endif
      while(tempNode!=NULL)
      {
        temp.push_back(tempNode->data);
        #if OUTPUT_LOG
        cout<<tempNode->data<<endl;
        #endif
        tempNode=tempNode->NextNode;
      }

      return temp;
    }

    std::vector<int> GetAdjacentNodesWithout(int NodeName)
    {
      std::vector<int> temp;
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      #if OUTPUT_LOG
      cout<<"Adjacent nodes : "<<endl;
      #endif
      while(tempNode!=NULL)
      {
        if(tempNode->data!=NodeName)
        {
          temp.push_back(tempNode->data);
          cout<<tempNode->data<<endl;
        }

        tempNode=tempNode->NextNode;
      }

      return temp;
    }

    std::vector<int> GetAdjacentNodesWeights()
    {
      std::vector<int> temp;
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      while(tempNode!=NULL)
      {
        temp.push_back(tempNode->weight);
        tempNode=tempNode->NextNode;
      }

      return temp;
    }

    void SetDad(int dadval)
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      tempNode->dad = dadval;
    }

    void GetDad()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      #if OUTPUT_LOG
      cout<<"dad of : "<<tempNode->data<<" is : "<<tempNode->dad<<endl;
      #endif
    }

    void ViewNodeStatus()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      #if OUTPUT_LOG
      cout<<"Node status of : "<<tempNode->data<<" is : "<<tempNode->NodeStatus<<"\n";
      cout<<"Node Bandwidth of : "<<tempNode->data<<" is : "<<tempNode->Bandwidth<<"\n";
      #endif
    }

    bool IsNodeUnseen()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      if(tempNode->NodeStatus == STATUS_GRAPH_UNSEEN)
      {
        return true;
      }

      else
      {
        return false;
      }

    }


    bool IsNodeFringe()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      if(tempNode->NodeStatus == STATUS_GRAPH_FRINGE)
      {
        return true;
      }

      else
      {
        return false;
      }

    }

    T GetBandWidth()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      return tempNode->Bandwidth;
    }

    T GetWeightOfAdjNode(T val)
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      while((tempNode!=NULL))
      {
        if(tempNode->data == val)
        {
          return tempNode->weight;
        }
        tempNode=tempNode->NextNode;
      }

      return 99999;
    }

    T GetWeight()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      return tempNode->weight;
    }

    T DisplayDadNodes()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;

      //cout<<tempNode->dad<<" -> ";
      //tempNode=tempNode->NextNode;

      return tempNode->dad;
    }

    int count()
    {
      SingleLinkedListNode<T> *tempNode=new SingleLinkedListNode<T>;
      tempNode=this->root;
      unsigned int count=0;
      //cout<<"\n"<<endl;
      while(tempNode!=NULL)
      {
        count = count+1;
        tempNode=tempNode->NextNode;
      }
      //cout<<count<<"\n";

      return count;

    }

};


// To represent Disjoint Sets
struct DisjointSets
{
    int *parent, *rnk;
    int n;

    // Constructor.
    DisjointSets(int n)
    {
        // Allocate memory
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        // Initially, all vertices are in
        // different sets and have rank 0.
        for (int i = 0; i <= n; i++)
        {
            rnk[i] = 0;

            //every element is parent of itself
            parent[i] = i;
        }
    }

    // Find the parent of a node 'u'
    // Path Compression
    int find(int u)
    {
        /* Make the parent of the nodes in the path
           from u--> parent[u] point to parent[u] */
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Union by rank
    void merge(int x, int y)
    {
        x = find(x), y = find(y);

        /* Make tree with smaller height
           a subtree of the other tree  */
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else // If rnk[x] <= rnk[y]
            parent[x] = y;

        if (rnk[x] == rnk[y])
            rnk[y]++;
    }
};
