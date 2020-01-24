#include <stdio.h>
#include <stdlib.h>
//	C:\Users\takee\Desktop\test.txt

typedef struct {
	int y;
	int x;
} Name;

typedef struct element {
	Name elName;
	struct element* f[4];
} Element;

typedef Element* ElementPtr;

void searchAround (char[][4], ElementPtr, ElementPtr[][4]);

void graphize (char Board[][4], int yPac, int xPac, ElementPtr* startP, ElementPtr links[][4]) {
	links[yPac][xPac] = malloc(sizeof(Element));
	links[yPac][xPac]->elName.y = yPac;
	links[yPac][xPac]->elName.x = xPac;
	*startP = links[yPac][xPac];
	searchAround(Board, *startP, links);
}

void searchAround (char Board[][4], ElementPtr p, ElementPtr links[][4]) {
	int y = p->elName.y;
	int x = p->elName.x;
	// right element
	if (x == 3 || Board[y][x+1] == '#' || links[y][x+1] != NULL) {
		p->f[0] = NULL;
	}
	else {
		links[y][x+1] = malloc(sizeof(Element));
		links[y][x+1]->elName.y = y;
		links[y][x+1]->elName.x = x+1;
		p->f[0] = links[y][x+1];
		searchAround(Board, p->f[0], links);
	}
	// down element
	if (y == 3 || Board[y+1][x] == '#' || links[y+1][x] != NULL) {
		p->f[1] = NULL;
	}
	else {
		links[y+1][x] = malloc(sizeof(Element));
		links[y+1][x]->elName.y = y+1;
		links[y+1][x]->elName.x = x;
		p->f[1] = links[y+1][x];
		searchAround(Board, p->f[1], links);
	}
	// left element
	if (x == 0 || Board[y][x-1] == '#' || links[y][x-1] != NULL) {
		p->f[2] = NULL;
	}
	else {
		links[y][x-1] = malloc(sizeof(Element));
		links[y][x-1]->elName.y = y;
		links[y][x-1]->elName.x = x-1;
		p->f[2] = links[y][x-1];
		searchAround(Board, p->f[2], links);
	}
	// up element
	if (y == 0 || Board[y-1][x] == '#' || links[y-1][x] != NULL) {
		p->f[3] = NULL;
	}
	else {
		links[y-1][x] = malloc(sizeof(Element));
		links[y-1][x]->elName.y = y-1;
		links[y-1][x]->elName.x = x;
		p->f[3] = links[y-1][x];
		searchAround(Board, p->f[3], links);
	}
}

// function for representing pacman's movement in game board
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

// function for directing pacman
int go (char gameBoard[4][4], int y, int x, char dir) {
	switch (dir) {
		case 'd':
			if (y == 3)
				return 0;
			gameBoard[y][x] = '1';
			gameBoard[y+1][x] = '0';
			show(gameBoard);
			return 1;
		case 'u':
			if (y == 0)
				return 0;
			gameBoard[y][x] = '1';
			gameBoard[y-1][x] = '0';
			show(gameBoard);
			return 1;
		case 'r':
			if (x == 3)
				return 0;
			gameBoard[y][x] = '1';
			gameBoard[y][x+1] = '0';
			show(gameBoard);
			return 1;
		case 'l':
			if (x == 0)
				return 0;
			gameBoard[y][x] = '1';
			gameBoard[y][x-1] = '0';
			show(gameBoard);
			return 1;
	}
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

	int xPac = 0, yPac = 0, x, y;
	ElementPtr start;
	ElementPtr links[4][4] = {NULL};
	graphize(gameBoard, yPac, xPac, &start, links);
	
	//finding foods
	for (y = 0; y < 4; y++)
		for (x = 0; x < 4; x++)
			if (gameBoard[y][x] == '*') {
				// going to food position
				while (y != yPac) {
					if (y > yPac) {
						go(gameBoard, yPac, xPac, 'd');
						yPac++;
					}
					if (y < yPac){
						go(gameBoard, yPac, xPac, 'u');
						yPac--;
					}
				}
				while (x != xPac) {
					if (x > xPac) {
						go(gameBoard, yPac, xPac, 'r');
						xPac++;
					}
					if (x < xPac){
						go(gameBoard, yPac, xPac, 'l');
						xPac--;
					}
				}
			}
}
