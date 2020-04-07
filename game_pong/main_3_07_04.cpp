#include <windows.h>
#include <iostream>
#include <conio.h>
#include <mmsystem.h> 
#include <cstdio>
#include <stdlib.h>

#pragma comment (lib, "Winmm.lib")

using namespace std;

void cls(){
// Get the Win32 handle representing standard output.
// This generally only has to be done once, so we make it static.
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

CONSOLE_SCREEN_BUFFER_INFO csbi;
COORD topLeft = { 0, 0 };

// std::cout uses a buffer to batch writes to the underlying console.
// We need to flush that to the console because we're circumventing
// std::cout entirely; after we clear the console, we don't want
// stale buffered text to randomly be written out.
std::cout.flush();

// Figure out the current width and height of the console window
if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
// TODO: Handle failure!
abort();
}
DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

DWORD written;

// Flood-fill the console with spaces to clear it
FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

// Reset the attributes of every character to the default.
// This clears all background colour formatting, if any.
FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

// Move the cursor back to the top left for the next sequence of writes
SetConsoleCursorPosition(hOut, topLeft);
}

// x is the column, y is the row. The origin (0,0) is top-left.
void setCursorPosition(int x, int y){
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
std::cout.flush();
COORD coord = { (SHORT)x, (SHORT)y };
SetConsoleCursorPosition(hOut, coord);
}

void xyBall(int &ballx, int &bally, int &napr){
	setCursorPosition(ballx, bally);
	cout << " ";
	if (napr == 1){
		ballx+=1;
		bally-=1;
	}
	else if(napr == 2){
		ballx-=1;
		bally-=1;
	}
	else if(napr == 3){
		ballx-=1;
		bally+=1;
	}
	else if(napr == 4){
		ballx+=1;
		bally+=1;
	}	
}

void setupMenu(void) {
	cls();
	cout << ">>>>> menu of pong <<<<<"
		 << "\n>> enter '1' to play"
	 	<< "\n>> enter '2' to check information"
	 	<< "\n>> enter '0' to exit";
}

void setupTable(){				//setup table with obj
	int flag_1 = 1,
		count_left = 0,
		count_right = 0;
	while(true){
		if(flag_1 == 0)	break;
		cls();
		char pol[20][70],
			 inputGame;
		int	ballx = 35,
			bally = 10,
			plx1 = 3,
			plx2 = 66,
			ply1 = 3,
			ply2 = 14,
			ply1Last = ply1,
			ply2Last = ply2,
			plx1Last = plx1,
			plx2Last = plx2,
			napr = rand()%(4) + 1;
			if(napr == 0) napr++;
			
		for(int i = 0; i < 20; i++){				//creating a field
			if(i == 0 || i == 19)
				for(int j = 0; j < 70; j++)
					pol[i][j] = '-';
			else
				for(int j = 0; j < 70; j++){
					if(j == 0 || j == 69){
						pol[i][j] = '|';
						continue;
					}
					pol[i][j] = ' ';	
				}		
		}
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 70; j++)
				cout << pol[i][j];
			cout << "\n";
		}
		for(int i = ply1; i < ply1+4; i++){
					setCursorPosition(plx1, i);
					pol[i][plx1] = '|';
					cout << "|";
				}
		for(int i = ply2; i < ply2+4; i++){
			setCursorPosition(plx2, i);
			pol[i][plx2] = '|';
			cout << "|";
		}
		setCursorPosition(1,22);
		cout << count_left << " : " << count_right;
		while(true){
			cin.clear();
			if(GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)			//reading from the keyboard Y
			{
	    		if (ply1 > 1) ply1--;
			}
			if(GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{
	    		if (ply1 < 15) ply1++;
			}
			if(GetKeyState(VK_UP) & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{
	    		if (ply2 > 1) ply2--;
			}
			if(GetKeyState(VK_DOWN) & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{
	    		if (ply2 < 15) ply2++;
			}
			if(GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)			//reading from the keyboard X
			{
	    		if (plx1 > 2) plx1--;
			}
			if(GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{
	    		if (plx1 < 30) plx1++;
			}
			if(GetKeyState(VK_LEFT) & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{
	    		if (plx2 > 39) plx2--;
			}
			if(GetKeyState(VK_RIGHT) & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{
	    		if (plx2 < 67) plx2++;
			}
			if(GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
			{
	    		flag_1 = 0;
	    		Sleep(50);
			}
			if(flag_1 == 0){
				cin.clear();
				break;
			}
			
			if(ply1Last != ply1 || ply2Last != ply2 || plx1Last != plx1 || plx2Last != plx2 ){			//frame players
	
				for(int i = ply1Last; i < ply1Last+4; i++){
					setCursorPosition(plx1Last, i);
					pol[i][plx1Last] = ' ';
					cout << " ";
				}
				for(int i = ply2Last; i < ply2Last+4; i++){
					setCursorPosition(plx2Last, i);
					pol[i][plx2Last] = ' ' ;
					cout << " ";
				}
				for(int i = ply1; i < ply1+4; i++){
					setCursorPosition(plx1, i);
					pol[i][plx1] = '|';
					cout << "|";
				}
				for(int i = ply2; i < ply2+4; i++){
					setCursorPosition(plx2, i);
					pol[i][plx2] = '|';
					cout << "|";
				}
				setCursorPosition(0, 21);
				ply1Last = ply1;
				ply2Last = ply2;
				plx1Last = plx1;
				plx2Last = plx2;
			}
			
			
			if(pol[bally][ballx] != '|' && pol[bally][ballx] != '-')	xyBall(ballx, bally, napr);	//normal
			//hit wall
			if(pol[bally][ballx] == '-') {							//	napr
				if(napr == 1){										//	2\/1
					napr = 4;										//  3/\4
					bally++;										
				}
				else if(napr == 2){
					napr = 3;
					bally++;
				}
				else if(napr == 3){
					napr = 2;
					bally--;
				}
				else if(napr == 4){
					napr = 1;
					bally--;
				}
				PlaySound("wall.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			if(pol[bally][ballx] == '|' && 		//hit players
						(	(ballx != 0) && (ballx != 69)	)	){
				if(ballx < 30)	PlaySound("left.wav", NULL, SND_FILENAME | SND_ASYNC);
				if(ballx > 30)	PlaySound("right.wav", NULL, SND_FILENAME | SND_ASYNC);	
				if(napr == 1){
					if(bally > 3){			//bypassing the span through the wall
						napr = 2;
						bally--;
						ballx-=2;
					}
					else{
						napr = 3;
						bally++;
						ballx-=2;
					}
				}
				else if(napr == 2){
					if(bally > 3){
						napr = 1;
						bally--;
						ballx+=2;
					}
					else{
						napr = 4;
						bally++;
						ballx+=2;
					}
				}
				else if(napr == 3){
					if(bally < 17){
						napr = 4;
						bally++;
						ballx+=2;
					}
					else{
						napr = 1;
						bally--;
						ballx+=2;
					}
				}
				else if(napr == 4){
					if(bally < 17){
						napr = 3;
						bally++;
						ballx-=2;
					}
					else{
						napr = 2;
						bally--;
						ballx-=2;
					}
				}								
			}
			if((ballx < 1) || (ballx > 68)){				//hit wall -> gameover
				cls();
				if(ballx < 1) count_right++;
				else count_left++;
				setCursorPosition(0,0);
				cout << ">> Game over"
					 << "\n>> Please, wait...";
				Sleep(1000);
				cin.clear();
				break;
			}
			if(pol[bally][ballx] == '-') {
				if(napr == 1){
					napr = 4;
					bally++;
					ballx++;
				}
				else if(napr == 2){
					napr = 3;
					bally++;
					ballx--;
				}
				else if(napr == 3){
					napr = 2;
					bally--;
					ballx--;
				}
				else if(napr == 4){
					napr = 1;
					bally--;
					ballx++;
				}
				PlaySound("wall.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			setCursorPosition(ballx, bally);
			pol[bally][ballx] = '0';
			cout << 0;
			setCursorPosition(0, 21);
			
			Sleep(85);
		}
	}
}

void information(){
    char left = 'a';
    int flag_2 = 0;
	cls();
	setCursorPosition(0, 0);
	cout << ">> In game:"
	 << "\n>> press WASD for left player"
	 << "\n>> press arrows for right player"
	 << "\n>> press Q to left the game"
	 << "\n>> "
	 << "\n>> press Q to left information list now"
	 << "\n>> "
	 << "\n>> "
	 << "\n>> P.S."
	 << "\n>> created by tubond 2020"
	 << "\n>> thx for playing ";
	while(true){
		if(flag_2 == 1)	break;
		left = _getch();
		switch (left){
			case 'q':
				flag_2 = 1;
				break;
			default:
				break;
		}
	}
}

void inMenu(int &flag){				//menu of game
	char inputMenu;
	while (true) {
		if(flag == 0)	break;
		setupMenu();
		inputMenu = _getch();
		switch (inputMenu) {
		case '1':
			setupTable();
			_getch();
			break;
		case '2':
			information();
			break;
		case '0':
			flag = 0;
			break;
		default:
			break;
		}
	}
}

int main() {
	system("title PONG_by_tubond");
	int flag = 1;
	inMenu(flag);
	return 0;
}
