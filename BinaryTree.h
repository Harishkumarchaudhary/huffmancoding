#include<iostream>
using namespace std;

class BinaryTreeNode{
  public:
      int value;
      char character;
      BinaryTreeNode *left;
      BinaryTreeNode *right;
      BinaryTreeNode(char character,int value){
        this->character=character;
        this->value=value;
        left=nullptr;
        right=nullptr;
      }
      BinaryTreeNode(){
         value=0;
         left=nullptr,right=nullptr;
      }
};

class Compare_2_objects{
  public:
      bool operator()(const BinaryTreeNode* o1,const BinaryTreeNode *o2 ){
         if(o1->value>=o2->value) return true;
         return false;
      }
};
