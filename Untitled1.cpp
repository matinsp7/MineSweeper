#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <conio.h>
#include <cstdlib>
using namespace std;

string message;
int n;

struct sdimension{
	int x;
	int y;
};
sdimension *bombs;

void design(){
	 system("cls");
    cout 
    << "\n\n"
    << "\t\t_______________________________________________\n"
    << "\t\t[|                                           |]\n"
    << "\t\t[|               MineSweeper                 |]\n"
    << "\t\t[|       1. Start new game                   |]\n"
    << "\t\t[|       2. Results                          |]\n"
    << "\t\t[|       3. Exit                             |]\n"
    << "\t\t-----------------------------------------------\n\n"
    << "\t\t         " << message << "\n"
    << "\t\t         ";
}


void startnewgame(){
	system ("cls");
	int  count = 1;
	cout << setw(20) << "* "<< "Enter the map dimension: ";
	//cin >> n; //dimenision of map 
	system ("cls");
	cout << endl << endl;
	cout << setw(20);
	for (int j=1 ; j<=n ; j++){
		cout << j << setw(5);
	}
	cout << endl;
	for (int i=0 ; i<n ; i++){
		cout << setw(15) <<  count ;
		count ++;
		for (int j=0 ; j<n ; j++){
			cout << setw(5) << "o";
		}
		cout << endl;
	}
	getch();
}


void creat_bomb (){
	system ("cls");
	cout << setw(20) << "* "<< "Enter the map dimension: ";
	cin >> n;
	bombs = new sdimension [(5*n)/2];
	if (n>=5){
		for (int i=0 ; i<(5*n)/2 ; i++){
			bool flag = 0;
			srand ((unsigned)time(0));
			int x = rand()%n;
			int y = rand ()%n;
			for (int j=0 ; j<i ; j++){
				if (x==bombs[j].x){
					if (y==bombs[j].y){
					flag = 1;
					i--;
					break;	
					}
				}
			}
			if (flag)
			continue;
			bombs[i].x = x;
			bombs[i].y = y;
		}
	}
}


void creat_map(){
	int map[n][n];
	for (int i=0 ; i < n ; i++){
		for (int j = 0 ; j<n ; j++){
			map [i][j] = 0;
		}
	}
	for (int i=0 ; i<(5*n)/2 ; i++){
		map[bombs[i].x][bombs[i].y] = -50;
	}
	for (int i=0 ; i < n ; i++){
		for (int j = 0 ; j<n ; j++){
			cout << map[i][j] << '\t';
		}
		cout << endl;
	}
	getch();
	
}


void results (){
	cout << "Results";
}
int main (){
	system ("color B");
	message = "Welcome :)";
	design();
	sleep(2);
	while(1){
		message = "Enter an appropriate option.";
		design();
		int input;
		cin >> input;
		switch(input){
            case 1:
            creat_bomb();
            creat_map();
            break;
            case 2:
            results();
            break;
            case 3:
            exit(0);
            break;
        }
	}
}