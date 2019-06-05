#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;
#include "BinaryTree.h"

void fill_count_map(unordered_map<char,int> &mp,string &s){
   for(int i=0;i<s.size();i++){
     if(mp.count(s[i])==0){
        mp[s[i]]=1;
     }
     else{
        mp[s[i]]++;
     }
   }
}

void fill_priority_queue(priority_queue<BinaryTreeNode*,vector<BinaryTreeNode*>,Compare_2_objects> &pq,unordered_map<char,int> &count_map){
     unordered_map<char,int>::iterator it;
     it=count_map.begin();
     while(it!=count_map.end()){
        BinaryTreeNode *bt=new BinaryTreeNode(it->first,it->second);
        pq.push(bt);
        it++;
     }
}

BinaryTreeNode* buildTree(priority_queue<BinaryTreeNode*,vector<BinaryTreeNode*>,Compare_2_objects> &pq){
     BinaryTreeNode *root;
     while(!pq.empty()){
            BinaryTreeNode *l=pq.top();
            pq.pop();
            if(pq.empty()){
                return l;
            }
            BinaryTreeNode *r=pq.top();
            pq.pop();
            root=new BinaryTreeNode('\0',l->value+r->value);
            root->left=l;
            root->right=r;
            pq.push(root);
     }
   return root;
}

void fill_encoder(BinaryTreeNode *root,unordered_map<char,string> &mp,string code){
     if(root==nullptr){
        return;
     }
     if(root->left==nullptr&&root->right==nullptr){
        mp[root->character]=code;
        return;
     }
     fill_encoder(root->left,mp,code+"0");
     fill_encoder(root->right,mp,code+"1");
}

void fill_decoder(unordered_map<char,string> &encoder,unordered_map<string,char> &decoder){
     unordered_map<char,string>::iterator it;
     it=encoder.begin();
     while(it!=encoder.end()){
        decoder[it->second]=it->first;
        it++;
     }
}

int main(){

string s;
cout<<"Enter the text : ";
cin>>s;
unordered_map<char,int> count_map;
fill_count_map(count_map,s);
//Make priority queue of objects and fill it using count_map
priority_queue<BinaryTreeNode*,vector<BinaryTreeNode*>,Compare_2_objects> pq;
fill_priority_queue(pq,count_map);
//Now build the tree using priority queue
BinaryTreeNode *root=buildTree(pq);//Take a binary tree having value and left and right children
//The leaf node will represent the character in the string which we will use shortly.

//Now we will fill get the code for each character by using binary 0 and 1
//Calling 0 on left and 1 on right
unordered_map<char,string> encoder;
fill_encoder(root,encoder,"");
for(int i=0;i<s.size();i++){
    cout<<encoder[s[i]]<<" ";
}
//Now fill decoder using encoder
unordered_map<string,char> decoder;
fill_decoder(encoder,decoder);
return 0;
}
