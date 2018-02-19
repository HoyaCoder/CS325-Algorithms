/*************************************************************************
** Author: James Meehan
** Course: CS 325 - Homework #5
** Date: February 18, 2018
** Description: BFS algorithm that will correctly determine if it is possible
** to create rivalries between a group of wrestlers give their names and a list 
** of pairs of rivalries
***************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
 
using namespace std;


/***************************************
** Description: struct node can assign 
** sides to a node(wrestler) and will keep
** track of each wrestler's side
*****************************************/ 
struct node
{
	string side;
	int node;
};


int main(int argc, char *argv[]) {


   		ifstream inFile;
		
		// Make sure correct usage was followed
		if (argc != 2) {
			cout << "usage: ./wrestlers [filename]" << endl;
			return 1;
		}	
 

    	inFile.open(argv[1]);
   	 	if (!inFile)
    	{
        	cout << "Unable to open file!";
        	return 1;
    	}

   		int n;
    	inFile >> n;

        unordered_map<string, int> wmap;
        unordered_map<int, string> reverse;
        string wrestler;

        
        for (int i = 0; i < n; i++)
        {
        	inFile >> wrestler;
        	wmap.insert ( {wrestler, i} );
        	reverse.insert ( {i, wrestler} ); 
        }

       
       	int rivalries;
       	inFile >> rivalries;

        string wrestler1, wrestler2;
        vector <unordered_set<int> > adj(n);

        //create adjacency matrix. No duplicates (i.e  for (1, 5) 5 will show up as an adjacent point for 1 but 1 will not
        //show up for 5)
        for (int i = 0; i < rivalries; i++) {
        	inFile  >> wrestler1 >> wrestler2;
        	
        	if (wmap[wrestler1] < wmap[wrestler2])
        		adj[wmap[wrestler1]].insert(wmap[wrestler2]); 
        	else
        		adj[wmap[wrestler2]].insert(wmap[wrestler1]); 
        }

    	/*print adjacency matrix (DEBUG)
        for (int i = 0; i < adj.size(); i++) {
        	cout << i << " ";
        	for (unordered_set<int> :: iterator it = adj[i].begin(); it != adj[i].end(); ++it)
        		cout << *it << " ";
        	cout << endl;
        }
        cout << endl;*/

        vector<node> nodes(n);
        unordered_set<int> baby;
        unordered_set<int> heel; 
        queue<int> wqueue;

        int count = 0;
        int s;

        //Continue looping until count is >= rivalries to account for disconnected graphs
        while (count < rivalries) {

        for (int a = 0; a < n; a++) {
        		
        		if (nodes[a].side != "b" && nodes[a].side != "h") {
					//push next node onto the queue.  If it hasn't been assigned a side, assign it
					//to babyfaces
					nodes[a].side = "b";
					wqueue.push(a);
        
        			//continue until queue is empty (BFS complete)
        			while(!wqueue.empty()) {
        				//pop top wrestler off the queue
        				s = wqueue.front();
        				wqueue.pop();
       		
       					//if a wrestler adjacent to current wrestler already has the same side then
       					// print out "Impossible"
       					for (unordered_set<int> :: iterator it = adj[s].begin(); it != adj[s].end(); ++it) {
        		
        					if (nodes[s].side == nodes[*it].side) {
        						cout << "Impossible!" << endl;
        						return 0;
        					}
        				
        				//else push the wrestlers onto the queue to be searched later
        				wqueue.push(*it);
        					//assign the appropriate side to the wrestler
        					if (nodes[s].side == "b") {

        						nodes[*it].side = "h";
        						heel.insert(*it);
        						baby.insert(s);
        						count++;
        					}
        					else {
        						nodes[*it].side = "b";
        						heel.insert(s);
        						baby.insert(*it);
        						count++;
        					}
        				}
    				}

    				//short circuit if count >= rivalries.  Since there are no duplicates in our adjacency matrix
    				//this will appriately short circuit the algorithm when all rivlaries have been checked.
    				if (count >= rivalries)
    					break;
    			}
		}
	}
  
  		//Print out "Yes" and babyfaces and heels
    	cout << "Yes, it is possible " << endl;
    	unordered_set<int>::iterator iter;
   		cout << "Babyfaces: ";
   		for (iter = baby.begin(); iter != baby.end(); ++iter)
   			cout << reverse[*iter] << " ";
   		cout << endl;

   		cout << "Heels: ";
   		for (iter = heel.begin(); iter != heel.end(); ++iter)
   			cout << reverse[*iter] << " ";
   		cout << endl;

    	//close file and exit
        inFile.close();
        return 0;
}
 
 
