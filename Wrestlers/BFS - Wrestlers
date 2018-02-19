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

        //cout << endl;
    	/*print adjacency matrix
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
        while (count < rivalries) {

        for (int a = 0; a < n; a++) {

        		cout << "a is " << a << endl;
        		
        		if (nodes[a].side != "b" && nodes[a].side != "h") {
				
					nodes[a].side = "b";
					wqueue.push(a);
        
        			while(!wqueue.empty()) {
        				s = wqueue.front();
        				wqueue.pop();
       		
       					for (unordered_set<int> :: iterator it = adj[s].begin(); it != adj[s].end(); ++it) {
        		
        					if (nodes[s].side == nodes[*it].side) {
        			
        						cout << "Impossible!" << endl;
        						return 0;
        					}
        				//cout << "IT is: " << *it << " ";
        				wqueue.push(*it);
        		
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

    				if (count >= rivalries)
    					break;
    			}
		}
	}
  
    	cout << "count " << count << endl;
    	unordered_set<int>::iterator iter;
   		cout << "Babyfaces: ";
   		for (iter = baby.begin(); iter != baby.end(); ++iter)
   			cout << reverse[*iter] << " ";
   		cout << endl;

   		cout << "Heels: ";
   		for (iter = heel.begin(); iter != heel.end(); ++iter)
   			cout << reverse[*iter] << " ";
   		cout << endl;

    
        inFile.close();
        return 0;
}
 
