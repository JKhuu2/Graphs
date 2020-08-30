//Jennifer Khuu, jtk2eh, April 21, 2020
//topological.cpp

/**
@file topological.cpp
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <algorithm>

/**
@namespace std
 */
using namespace std;

/**
 A node holding a course name and its pointer to the next course
 */
struct node{
  /**                                                                        
   name of course of the node               
   */
  string name;
  /**                                                                        
   number of edges coming into node                                        
   */
  int indegree;
  /**                                                                        
   number of edges node has going out                   
   */
  int edges;
  /**                                                                        
   pointer to next node(s)                  
   */
  node *next;
};

/**
@brief main method
Given a file stating what the prerequisites are of multiple cs courses, 
this main method will read that file and print out a topologically sorted list
of those courses in the order that they could be taken in
@param argc
@param **argv
 */

int main (int argc, char **argv) {
  
    if ( argc != 2 ) {
        cout << "Only input the file in one parameter" << endl;
        exit(1);
    }
    ifstream file(argv[1], ifstream::binary);
    if ( !file.is_open() ) {
        cout << "Can't open '" << argv[1] << "'." << endl;
        exit(2);
    }

    
    /**
     a vector of courses
     */
    vector <node*> courses;
    /**
       temporary string keeping track of each course in the file
     */
    string s;
    node* n;
    node* n2;
    node* n3;
    while(true){
      //checks to see if reach end of file
      file >> s;
       if(s == "0")
	 file >> s;
       if(s == "0")
	  break;

       n = new node();
       //n3=new node();
       for(int i=0; i<courses.size(); i++){
	 if(courses.at(i)->name==s){
	   //n=new node();
	   //stores the current hierarchy of a course
	   n=courses.at(i)->next;
	   stack <node*> h;
	   while(n){
	     h.push(n);
	     n=n->next;
	   }

	   //read the next course in the file
	   file >> s;
	   bool b=false;
	   for(int j=0;j<courses.size();j++){
	     if(courses.at(j)->name==s){
	       b=true;
	     }
	   }
	   
	   //if that course isn't in "courses", add it 
	   if(!b){
	     node* newNode = new node();
	     newNode->name = s;
	     courses.push_back(newNode);
	   }

	   //otherwise, add it as the next pointer to the first course
	   n2 = new node();
	   n2->name = s;
	   n = n2;
	   while(h.size()!=0){
	       h.top()->next = n;
	       n = h.top();   
	       h.pop();
	   }
	   courses.at(i)->next = n;
	   break;
	 }
       }
       //node* n3;
       //n=new node();
       //if n hasn't been assigned a name yet
       if(n->name==""){
	 n->name = s;
	 file >> s;
	 n3 = new node();
	 n3->name = s;
	 n->next = n3;
	 courses.push_back(n);
	 //if n3 not in "courses" add it
	 bool b2=false;
	 for(int j =0; j<courses.size(); j++){
	   if(courses.at(j)->name==s){
	     b2=true;
	   }
	 }
	 if(!b2){
	   node* n4 = new node();
	   n4->name =s;
	   courses.push_back(n4);
	 }
       }
    }
    //close file
    file.close();
    
    //making a matrix similar to making a graph for the courses
    int m [courses.size()][courses.size()];
    for(int i=0; i<courses.size(); i++){
      for(int j=0; j<courses.size(); j++){
	m[i][j]=0;
      }
    }

    for(int i=0; i<courses.size(); i++){
      //preserving our hierarchy in a stack
	  stack<node*> h;
	  node* n = courses.at(i)->next;
	  while(n){
	    h.push(n);
	    n = h.top()->next;
	  }
	 //adding the courses to our matrix
	  while(h.size() !=0){
	    for(int j=0; j<courses.size(); j++){
	      if(h.top()->name == courses.at(j)->name){
		m[i][j]=1;
	      }
	      if(i==j)
		m[i][j]=0;
	    }
	    //deallocate and clear stack one by one
	    h.pop();
	  }
    }


    int count, row, column;
    count=0;
    row=0;
    column=0;
    
    while(column<courses.size()){
      while(row<courses.size()){
	if(m[row][column]==1){
	  row=0;
	  column++;
	}
	else{
	  row++;

	}
      }
      
      cout<<courses.at(column)->name<<" ";
      for(int i=0; i<courses.size(); i++){
	m[column][i]=0;
	m[i][column]=1;
      }
      count++;
      if(count<courses.size()){
	column=0;
      }
      else {
	break;
      }
      row=0;
    }
    cout<<endl;
    
    for (int i=0; i<courses.size(); i++){
      delete courses[i];
    }
    courses.clear();
    
    return 0;
    
}
