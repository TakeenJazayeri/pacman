#include <stdio.h>
//	C:\Users\takee\Desktop\hello\test.txt

int goDown (char gameBoard[4][4], int y, int x) {
	if (y == 3)
		return 0;
	gameBoard[y][x] = '1';
	gameBoard[y+1][x] = '0';
	show(gameBoard);
	return 1;
}

int goUp (char gameBoard[4][4], int y, int x) {
	if (y == 0)
		return 0;
	gameBoard[y][x] = '1';
	gameBoard[y-1][x] = '0';
	show(gameBoard);
	return 1;
}

int goRight (char gameBoard[4][4], int y, int x) {
	if (x == 3)
		return 0;
	gameBoard[y][x] = '1';
	gameBoard[y][x+1] = '0';
	show(gameBoard);
	return 1;
}

int goLeft (char gameBoard[4][4], int y, int x) {
	if (x == 0)
		return 0;
	gameBoard[y][x] = '1';
	gameBoard[y][x-1] = '0';
	show(gameBoard);
	return 1;
}

void show (char B[][4]) {
	int i, j;
	for (i = 0; i <400000000; i++) ;
	system("cls");
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
			printf("%c ", B[i][j]);
		printf("\n");
	}
}

int main(){
	printf("Enter the file's adress: ");
	char adr[100];
	scanf("%s", adr);
	FILE *ptf;
	ptf = fopen(adr, "r");
	char ch, gameBoard[4][4] = {0};
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			while (gameBoard[i][j] == 0) {
				ch = fgetc(ptf);
				if (ch == '1' || ch == '0' || ch == '#' || ch == '*')
					gameBoard[i][j] = ch;
			}
	show(gameBoard);

/*	int xPac = 0, yPac = 0, x, y, flag = 0;
	for (y = 0; y < 4 && flag == 0; y++)
		for (x = 0; x < 4 && flag == 0; x++)
			if (gameBoard[y][x] == '*')
				flag = 1;
	y--;
	x--;
	
	while (y != yPac) {
		if (y > yPac) {
			goDown(gameBoard, yPac, xPac);
			yPac++;
		}
		if (y < yPac){
			goUp(gameBoard, yPac, xPac);
			yPac--;
		}
	}
	while (x != xPac) {
		if (x > xPac) {
			goRight(gameBoard, yPac, xPac);
			xPac++;
		}
		if (x < xPac){
			goLeft(gameBoard, yPac, xPac);
			xPac--;
		}
	}*/
	int xPac = 0, yPac = 0, x, y, flag = 0;
	for (y = 0; y < 4 && flag == 0; y++)
		for (x = 0; x < 4 && flag == 0; x++)
			if (gameBoard[y][x] == '*') {
				while (y != yPac) {
					if (y > yPac) {
						goDown(gameBoard, yPac, xPac);
						yPac++;
					}
					if (y < yPac){
						goUp(gameBoard, yPac, xPac);
						yPac--;
					}
				}
				while (x != xPac) {
					if (x > xPac) {
						goRight(gameBoard, yPac, xPac);
						xPac++;
					}
					if (x < xPac){
						goLeft(gameBoard, yPac, xPac);
						xPac--;
					}
				}
			}
}
