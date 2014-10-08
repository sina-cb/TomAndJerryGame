#include <vector>
#include <iostream>
using namespace std;

#define DRAW 3
#define TOM_WIN 2
#define JERRY_WIN 1
#define UNKNOWN 0

#define N 3
#define STEPS 3 * 3 * 2

int tomWinCount = 0;
int jerryWinCount = 0;
int drawCount = 0;
int data[N][N][N][N][STEPS];

int dynamic_W(int n, vector< vector<int> > (*NBR)(vector<int>, int), vector<int> tomP, vector<int> jerryP, vector<int> cheeseP, int m);
void W (int n, vector< vector<int> > (*NBR)(vector<int>, int), vector<int> tomP, vector<int> jerryP, vector<int> cheeseP, int m);
vector< vector<int> > NBR (vector<int> position, int n);

int main(int argc, char** argv){
	vector <int> tomP0;
	vector <int> jerryP0;
	vector <int> cheeseP0;

	tomP0.push_back(0);
	tomP0.push_back(0);

	jerryP0.push_back(2);
	jerryP0.push_back(2);

	cheeseP0.push_back(1);
	cheeseP0.push_back(1);

	dynamic_W(N, NBR, tomP0, jerryP0, cheeseP0, STEPS);

	cout << "Dynamic Programming Results: " << endl;
	cout << "\tJerry Win Count --> " << jerryWinCount << endl;
	cout << "\tTom Win Count --> " << tomWinCount << endl;
	cout << "\tTie Game Count --> " << drawCount << endl;

	if (jerryWinCount > 0){
		cout << "\tJerry Wins!" << endl;
	}else if (drawCount > 0){
		cout << "\tTie Game!" << endl;
	}else if (tomWinCount > 0){
		cout << "\tTom Wins!" << endl;
	}

	cout << endl;

	tomWinCount = 0;
	jerryWinCount = 0;
	drawCount = 0;

	W (N, NBR, tomP0, jerryP0, cheeseP0, STEPS);

	cout << "Recursive Results: " << endl;
	cout << "\tJerry Win Count --> " << jerryWinCount << endl;
	cout << "\tTom Win Count --> " << tomWinCount << endl;
	cout << "\tTie Game Count --> " << drawCount << endl;

	if (jerryWinCount > 0){
		cout << "\tJerry Wins!" << endl;
	}else if (drawCount > 0){
		cout << "\tTie Game!" << endl;
	}else if (tomWinCount > 0){
		cout << "\tTom Wins!" << endl;
	}
}

/**
 * Dynamic programming version of Tom&Jerry program
 */
int dynamic_W(int n, vector< vector<int> > (*NBR)(vector<int>, int), vector<int> tomP, vector<int> jerryP, vector<int> cheeseP, int m){

	int entry = data[tomP[0]][tomP[1]][jerryP[0]][jerryP[1]][m];
	if (entry != UNKNOWN){
		 if (entry == TOM_WIN){
			 tomWinCount ++;
			 return entry;
		 }

		 if (entry == JERRY_WIN){
			 jerryWinCount ++;
			 return entry;
		 }

		 if (entry == DRAW){
			 drawCount ++;
			 return entry;
		 }

		 cerr << "There was an error!!!" << endl;
	}

	/*if (drawCount == 0 && jerryWinCount == 0){*/  //If you want to stop the process after the first time you find a draw or win, you can uncomment this line
	if (true){										// And comment this line
		if (tomP == jerryP && tomP == cheeseP){
			drawCount ++;
			return DRAW;
		}
		if (tomP == jerryP && tomP != cheeseP){
			tomWinCount ++;
			return TOM_WIN;
		}
		if (tomP != jerryP && jerryP == cheeseP){
			jerryWinCount ++;
			return JERRY_WIN;
		}
		if (m == 0){
			drawCount ++;
			return DRAW;
		}

		if (m % 2 == 0){
			vector< vector<int> > neighborCells = (*NBR)(jerryP, n);
			for (unsigned int i = 0; i < neighborCells.size(); i++){
				int result = dynamic_W(n, (*NBR), tomP, neighborCells[i], cheeseP, m - 1);
				data[tomP[0]][tomP[1]][neighborCells[i][0]][neighborCells[i][1]][m - 1] = result;
			}
		}else{
			vector< vector<int> > neighborCells = (*NBR)(tomP, n);
			for (unsigned int i = 0; i < neighborCells.size(); i++){
				int result = dynamic_W(n, (*NBR), neighborCells[i], jerryP, cheeseP, m - 1);
				data[neighborCells[i][0]][neighborCells[i][1]][jerryP[0]][jerryP[1]][m - 1] = result;
			}
		}
	}

	return UNKNOWN;
}

/**
 * Recursive version of Tom&Jerry program
 */
void W (int n, vector< vector<int> > (*NBR)(vector<int>, int), vector<int> tomP, vector<int> jerryP, vector<int> cheeseP, int m){
	/*if (drawCount == 0 && jerryWinCount == 0){*/  //If you want to stop the process after the first time you find a draw or win, you can uncomment this line
	if (true){										// And comment this line
		if (tomP == jerryP && tomP == cheeseP){
			drawCount ++;
			return;
		}
		if (tomP == jerryP && tomP != cheeseP){
			tomWinCount ++;
			return;
		}
		if (tomP != jerryP && jerryP == cheeseP){
			jerryWinCount ++;
			return;
		}
		if (m == 0){
			drawCount ++;
			return;
		}

		if (m % 2 == 0){
			vector< vector<int> > neighborCells = (*NBR)(jerryP, n);
			for (unsigned int i = 0; i < neighborCells.size(); i++){
				W(n, (*NBR), tomP, neighborCells[i], cheeseP, m - 1);
			}
		}else{
			vector< vector<int> > neighborCells = (*NBR)(tomP, n);
			for (unsigned int i = 0; i < neighborCells.size(); i++){
				W(n, (*NBR), neighborCells[i], jerryP, cheeseP, m - 1);
			}
		}
	}else{
		return;
	}
}

/**
 * Simplified version of NBR which returns all neighbors of a cell in an n x n matrix without considering any walls in the matrix.
 */
vector< vector<int> > NBR (vector<int> position, int n){
	vector < vector<int> > results;

	int tempX;
	int tempY;

	tempX = position[0] - 1;
	tempY = position[1];

	if (tempX >= 0){
		vector <int> temp;
		temp.push_back(tempX);
		temp.push_back(tempY);

		results.push_back(temp);
	}

	tempX = position[0];
	tempY = position[1] - 1;

	if (tempY >= 0){
		vector <int> temp;
		temp.push_back(tempX);
		temp.push_back(tempY);

		results.push_back(temp);
	}

	tempX = position[0] + 1;
	tempY = position[1];

	if (tempX < n){
		vector <int> temp;
		temp.push_back(tempX);
		temp.push_back(tempY);

		results.push_back(temp);
	}

	tempX = position[0];
	tempY = position[1] + 1;

	if (tempY < n){
		vector <int> temp;
		temp.push_back(tempX);
		temp.push_back(tempY);

		results.push_back(temp);
	}

	return results;
}
