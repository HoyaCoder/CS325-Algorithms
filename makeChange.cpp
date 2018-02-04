/***********************************************************************
** Author: James Meehan
** Course: CS 325
** Assignment: Homework #3, Question 5
** Date: January 28, 2018
************************************************************************/

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

/************************************************************************
** function makeChange() takes a vector of coin denominations and a total
** amount to make change for and builds a table from the bottom up to 
** determine minimum number of coins needed to make change. It also takes 
** a coin vector as a parameter to store the amount of each coin denomination 
** needed to make the change.  It returns the value in the final cell of the 
** table,which contains the mininum number of coins needed.
**************************************************************/
int makeChange(vector<int>& vec, vector<int>& coins, int total) {
    int size = vec.size();
    //create a 2D vector. Values in the vector will display the fewest amount of coins needed
    //to make a certain amount of change.
    vector <vector<int> > table(size, vector<int>(total + 1));
    
    //initiliaze first element of each row to zero. Rows account for each denomination
    for ( int row = 0; row < size ; row++) 
        table[row][0]  = 0;    

    //initialize the first element of each column. Columns account for the total change
    //that is needed.  The first row is just the amount of pennies to make change.
    for ( int col = 0; col <= total ; col++) 
        table[0][col]  = col;

    //determine the fewest number of coins needed to make each level of change
    for ( int row = 1 ; row < size; row++) {
        for ( int col = 1 ; col <= total; col++) {
            // if column is less than the denomination in vec[row], than that denomination 
            // or higher can't be used so the value above it is inserted
            if (col < vec[row])
                table[row][col] = table[row - 1][col];

            else {
                // otherwise the higher denom coin may be used and we need to determine the
                // min number of coins between using the higher denom coin or not
                if (table[row -1][col] < table[row][col - vec[row]] + 1)
                    // in this case it is better not to use the higher denom coin
                    table[row][col] = table[row - 1][col];
                else
                    //in the case the higher denom coin should be used
                    table[row][col] = table[row][col - vec[row]] + 1;
            }
        }
    }

    
        int val = total;
       
       // vector <int> coins(vec.size());
        int x = 1;
       while (val > 0)
        {
            // if we are in first row enter val as the number of pennies
            if ((size - x) == 0)
            {
                coins[0] = val;
                val = 0;
            }
            // if the value in current row is less than value just above it
            // then a higher denomination coin must have been used so add
            // that to coin vec and subtract its value from val
            else if (table[size - x][val] < table[size - x - 1][val]) 
            {
        
                coins[coins.size() - x]++;
                val -= vec[vec.size() - x]; 
            }
            // in this case no more of the higher denom coins are being used so
            // we move up a row and check to see if next highest denom coin was used
            else
            {
                x++;
            }

        }

     // print coin denom array (debug)  
    /* for (int z = 0; z < coins.size(); z++)
        {
            cout << coins[z] << " ";
        }
        cout << endl; 
    // print table (debug)
     for(int i = 0; i < size; i++) {
        for(int j = 0; j < total + 1; j++) {
            cout << table[i][j] << " ";
    }
    cout << endl;
    }*/ 
    return table[size - 1][total];
}

int main () {
    ifstream inFile;

    inFile.open("amount.txt");
    if (!inFile)
    {
        cout << "Unable to open file!";
        return 1;
    }


    ofstream outFile;
    outFile.open("change.txt");


    while (!inFile.eof()) {
	vector<int> coinVec;
        string line;
    
        getline(inFile, line);
        stringstream v(line);
        int q;
        while (v >> q) {
            
            coinVec.push_back(q);
        }

        //print out the denomination set
        cout << "The coin denominations are: ";
        for (int i = 0; i < coinVec.size(); i++)
            cout << coinVec[i] << " ";
        cout << endl;

        for (int i = 0; i < coinVec.size(); i++)
            outFile << coinVec[i] << " ";
        outFile << endl;

        //get the total amount to make change for from file 
        int total;
        string numOfCoins;
        getline(inFile, numOfCoins); 
        istringstream t(numOfCoins);
        t >> total;
        cout << "The amount to make change for is: " << total << endl;
        outFile << total << endl;

        //create vector to hold the number of each coin denomination
        //needed to achieve the solution
        vector<int> numOfEachCoin(coinVec.size());

        //call makeChange()
        int solution = makeChange(coinVec, numOfEachCoin, total);

        //print array of number of each coin denomination needed
        cout << "Coin denomination totals: ";
        for (int i = 0; i < numOfEachCoin.size(); i++)
            cout << numOfEachCoin[i] << " ";
        cout << endl;

        for (int i = 0; i < numOfEachCoin.size(); i++)
            outFile << numOfEachCoin[i] << " ";
        outFile << endl;

        //print solution
        cout << "Total coins needed: " << solution << endl;
        outFile << solution << endl;

        cout << endl;
        outFile << endl;
        }

    inFile.close();
    outFile.close();

    return 0;
}
