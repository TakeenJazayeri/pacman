#include <stdio.h>
#include <conio.h>
//	C:\Users\takee\Desktop\test2.txt

// function for representing pacman's movement in game board
void show (char B[][10]) {
	int i, j;
	system("cls");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++)
			printf("%c ", B[i][j]);
		printf("\n");
	}
}

// function for directing pacman
int go (char gameBoard[][10], int y, int x, char dir) {
	switch (dir) {
		case 'd':
			if (y == 4 || gameBoard[y+1][x] == '#')
				return 0;
			gameBoard[y][x] = '1';
			gameBoard[y+1][x] = '0';
			show(gameBoard);
			return 1;
		case 'u':
			if (y == 0 || gameBoard[y-1][x] == '#')
				return 0;
			gameBoard[y][x] = '1';
			gameBoard[y-1][x] = '0';
			show(gameBoard);
			return 1;
		case 'r':
			if (x == 9 || gameBoard[y][x+1] =='#')
				return 0;
			gameBoard[y][x] = '1';
			gameBoard[y][x+1] = '0';
			show(gameBoard);
			return 1;
		case 'l':
			if (x == 9 || gameBoard[y][x-1] == '#')
				return 0;
			gameBoard[y][x] = '1';
			gameBoard[y][x-1] = '0';
			show(gameBoard);
			return 1;
	}
}

// Function for counting the number of remaining foods
int foodNum(char gameBoard[][10]) {
	int i, j, result = 0;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 10; j++)
			if (gameBoard[i][j] == '*')
				result++;
	return result;
}

// Function for notifying or announcing "game over" when user makes mistake
void faultError(int* faultAd) {
	(*faultAd)++;
	if ((*faultAd) == 3)
		printf("GAME OVER! You have made 3 mistakes.\n");
	else
		printf("BE CAREFULL! You can't move in this direction.\n");
}

int main(){
	printf("Enter the file's adress:\n");
	char adr[100];
	scanf("%s", adr);
	FILE *ptf;
	ptf = fopen(adr, "r");
	while (ptf == NULL) {
		printf("There's no file with this adress. Please enter another adress:\n");
		scanf("%s", adr);
		ptf = fopen(adr, "r");
	}
	char ch, gameBoard[5][10] = {0};
	int i, j;
	for (i = 0; i < 5; i++)
		for (j = 0; j < 10; j++)
			while (gameBoard[i][j] == 0) {
				ch = fgetc(ptf);
				if (ch == '1' || ch == '0' || ch == '#' || ch == '*')
					gameBoard[i][j] = ch;
			}
	show(gameBoard);
	
	int xPac = 0, yPac = 0, x, y, fault = 0, fn = foodNum(gameBoard);
	char ch1, ch2;
	ch1 = getch();
	while (ch1 != 'e'){
		if (ch1 == -32) {
			ch2 = getch();
			switch (ch2) {
				case 80:
					if (go(gameBoard, yPac, xPac, 'd') == 0)  {
						faultError (&fault);
					}
					else
						yPac++;
					break;
				case 72:
					if (go(gameBoard, yPac, xPac, 'u') == 0)  {
						faultError (&fault);
					}
					else
						yPac--;
					break;
				case 77:
					if (go(gameBoard, yPac, xPac, 'r') == 0)  {
						faultError (&fault);
					}
					else
						xPac++;
					break;
				case 75:
					if (go(gameBoard, yPac, xPac, 'l') == 0)  {
						faultError (&fault);
					}
					else
						xPac--;
					break;
			}
		}
		else
			printf("error: Please enter an array key\n");
		if (fault == 3) {
			ch1 = 'e';
			continue;
		}
		if (foodNum(gameBoard) == 0) {
			printf("Hooray! You ate all the foods!\n");
			ch1 = 'e';
			continue;
		}
		if (foodNum(gameBoard) < fn) {
			printf("You ate a foods!\n");
			fn--;
		}
		ch1 = getch();
	}
}
