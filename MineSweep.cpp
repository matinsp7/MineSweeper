#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <vector>
using namespace std;

string message;
int** backendBoard;
char** frontendBoard;
int n;
int openedCells;
HANDLE hConsole;
int timeSpend;
int flagCount;


void DesignMenu(){
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


void Flag(int x,int y){
  if(frontendBoard[x][y] == 'f'){
    frontendBoard[x][y] = 'o';
    flagCount--;
  }
  else if(frontendBoard[x][y] == 'o'){
    frontendBoard[x][y] = 'f';
    flagCount++;
  }
    
}

int Win (){
  timeSpend = time(0) - timeSpend;
cout << "\t\t" << setw (5) << "* "<< "Enter your name: ";
string name;
cin.ignore();
getline (cin , name);
ofstream out;
out.open("scores.txt" , ios::app);
out << name << " " << timeSpend;
out.close();
}


void OpenZero(int,int);

void Open(int x,int y){
 if(x != -1 && x != n && y != -1 && y != n){
  if(frontendBoard[x][y] == 'o'){
   if(backendBoard[x][y] == 0){
    frontendBoard[x][y] = char(48);
    openedCells++;
    OpenZero(x,y);
   }
   else{
    frontendBoard[x][y] = char(backendBoard[x][y] + 48);
    openedCells++;
   }
  }
 }
}


void OpenZero(int x,int y){
 Open(x-1 , y-1);
 Open(x , y-1);
 Open(x+1 , y-1);
 Open(x-1 , y);
 Open(x+1 , y);
 Open(x-1 , y+1);
 Open(x , y+1);
 Open(x+1 , y+1);
}


void PrintMap(){
  SetConsoleTextAttribute(hConsole,7);

 int count = 1 , counter=2;
 cout << "\n\n" << setw(10) << 1;
 for (int j=0 ; j<n-1 ; j++){
  cout << setw(3) << counter;
  counter ++;
 }
 cout << endl;
 cout << setw(10) << "*";
 for (int j=0 ; j<n-1 ; j++){
  cout << setw(3) << "*";
  counter ++;
 }
 cout << endl;
 //-------------------------------------
 for(int i = 0 ; i < n ; i++){
  cout << setw(7) << count << "*";
  for(int j = 0 ; j < n; j++){
        //--------------------------------
        if(frontendBoard[i][j] == '0'){
                SetConsoleTextAttribute(hConsole,128);
        }else if(frontendBoard[i][j] == 'o'){
                SetConsoleTextAttribute(hConsole,6);
        }else if(frontendBoard[i][j] == 'X'){
                SetConsoleTextAttribute(hConsole,192);
        }else if(frontendBoard[i][j] == 'f'){
                SetConsoleTextAttribute(hConsole,224);
        }else {
                SetConsoleTextAttribute(hConsole,48);
        }
   cout << setw(2) << frontendBoard[i][j] << " "; // the main work
  }
  SetConsoleTextAttribute(hConsole,7);
  count ++;
  cout << endl << endl;
 }
 cout << endl;
 SetConsoleTextAttribute(hConsole,7);
}

void Lose(){
    for(int i = 0;i < n;i++){
      for(int j =0;j < n;j++){
        if(backendBoard[i][j] == -50){
          frontendBoard[i][j] = 'X';
        }
      }
    }
    system("cls");
    PrintMap();
    getch();
}

void GameManager(){

 while(1){
  system("cls");
  cout << openedCells << endl;
  PrintMap();
  if(openedCells == n*n - n && flagCount == n){
    Win();
    break;
  }
  int x,y,actionType;
  cout << setw(10) << "* " << "Enter X: ";
  cin >> x;
  cout << setw(10) << "* " << "Enter Y: ";
  cin >> y;
  cout << setw(10) << "* " << "Select Action Type(Open:0 Flag:1):";
  cin >> actionType;
  
	if(actionType == 1){
	   Flag(x-1,y-1);
	}
	else if (actionType == 0){
	  if(backendBoard[x-1][y-1] == -50){
	    Lose();
	    break;
	   }
	   else{
	    Open(x-1,y-1);
	   }
	  }
  }	
 }
 
 
void create_bomb (){
 srand((unsigned)time(0));
 for (int i=0; i<n; i++){
  int x = rand()%n;
  int y = rand()%n;
  if(backendBoard[x][y] == -50){
   i--;
   continue;
  }
  backendBoard[x][y] = -50;
 }
}


void create_map(){
 backendBoard = new int*[n];
 frontendBoard = new char*[n];
 for(int i =0;i < n;i++){
  backendBoard[i] = new int[n];
  frontendBoard[i] = new char[n];
  for(int j = 0;j < n;j++){
   backendBoard[i][j] = 0;
   frontendBoard[i][j] = 'o';
  }
 }
 openedCells =0;
}



bool isBomb(int x , int y){
 if(x != -1 && x != n && y != -1 && y != n){
  if(backendBoard[x][y] == -50){
   return 1;
  }
 }
 return 0;
}


void create_backend(){
 for(int x =0;x < n;x++){
  for(int y =0;y < n;y++){
   if(backendBoard[x][y] != -50){
   int sum = 0;
   sum += isBomb(x-1 , y-1);
   sum += isBomb(x , y-1);
   sum += isBomb(x+1 , y-1);
   sum += isBomb(x-1 , y);
   sum += isBomb(x+1 , y);
   sum += isBomb(x-1 , y+1);
   sum += isBomb(x , y+1);
   sum += isBomb(x+1 , y+1);
   backendBoard[x][y] = sum;
   }
  }
 }
}


void results (){
  vector<string> names;
  vector<int> scores;
  ifstream out("scores.txt" , ios::in);
  while(!out.eof()){
    string newName;
    long int newScore;
    out >> newName >> newScore;
    names.push_back(newName);
    scores.push_back(newScore);
  }
  while(1){
    bool changed = 0;
    for(int i =1;i < scores.size();i++){
      if(scores[i - 1] > scores[i]){
        int tempI = scores[i];
        string tempS = names[i];
        scores[i] = scores[i - 1];
        names[i] = names[i - 1];
        scores[i - 1] = tempI;
        names[i - 1] = tempS;
        changed = 1;
      }
    }
      if(changed == 0){
        break;
      }
  }
  system("cls");
  for(int i =0;i < scores.size();i++){
    cout << names[i] << " " << scores[i] << "\n";
  }
  getch();
}

int main (){
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  message = "Welcome :)";
  DesignMenu();
  sleep(2);
  while(1){
	  SetConsoleTextAttribute(hConsole,14);
	  message = "Enter an appropriate option.";
	  DesignMenu();
	  int input;
	  cin >> input;
	  switch(input){
	            case 1:
	    system ("cls");
	    cout << endl << endl << endl << endl << endl<< setw(25) << "* "<< "Enter the map dimension: ";
	    cin >> n;
	    create_map();
	    create_bomb();
	    create_backend();
	    timeSpend = time(0);
	    GameManager();
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