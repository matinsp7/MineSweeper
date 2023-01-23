#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <conio.h>
using namespace std;

string message;
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
	int n , count = 1;
	cout << setw(20) << "* "<< "Enter the map dimension: ";
	cin >> n;
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
            startnewgame();
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