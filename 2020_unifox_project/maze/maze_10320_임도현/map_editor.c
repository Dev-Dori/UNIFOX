#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <direct.h>

char map[26][26] = { { 0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					 { 0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					 { 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1 }
};

int file_save();
void menu();
void Gotoxy(int x, int y);
int control_block();
void Put_block(int color);
void rm_block(int x, int y);

int main(void) {
	system("mode con cols=120 lines=30 | title 미로");
	//menu();

	int i, j;

	for (i = 1; i <= 25; i++) {
		for (j = 1; j <= 25; j++) {
			if (map[i][j] == 1) printf("■");
			if (map[i][j] == 0) printf("  ");
		}
		printf("\n");
	}

	map[1][2] = 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	Gotoxy(36, 3);
	printf("< 맵 에디터 조작키 >");
	Gotoxy(29, 5);
	printf("1. W A S D 로 벽을 움직이세요");
	Gotoxy(29, 6);
	printf("2. SPACEBAR 로 벽을 놓을 수 있습니다");
	Gotoxy(29, 7);
	printf("3. BACKSPACEBAR 로 이미 놓아진 벽을 지울 수 있습니다.");
	Gotoxy(29, 8);
	printf("4. 맵 제작이 완료됬다면 ENTER 를 눌러 SAVE 파일을 만드세요.");
	control_block();
	return 0;
}



void menu() {
	system("mode con cols=80 lines=50 | title 게임메뉴");
	printf("\n\n\n");
	printf("                #####     ###     ###     #    ####   #####     \n");
	printf("                #        #       #       # #   #   #  #         \n");
	printf("                #####    ####    #      #####  ####   #####     \n");
	printf("                #            #   #      #   #  #      #         \n");
	printf("                #####    ####     ###   #   #  #      #####     \n\n\n");
	printf("################################################################################\n\n");
}

//컨트롤 패널
int control_block() {
	int x = 2, y = 2;
	char key;
	Gotoxy(x, y);
	Put_block(1);
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);  //앞y 뒤 x
		key = _getch();
		if (65 <= key && key <= 90) key = +32;
		if (key == 56) key = 119;
		else if (key == 48) key = 32;
		else if (key == 52) key = 97;
		else if (key == 54) key = 100;
		else if (key == 53) key = 115;

		switch (key) {     //a=97 d=100 w=119 s=115
		case 119:  //w
			if (2 <= y - 1) {
				rm_block(x, y);
				y--;
				Gotoxy(x, y);
				Put_block(1);
			}
			break;

		case 115:  //s
			if (y + 1 <= 24) {
				rm_block(x, y);
				y++;
				Gotoxy(x, y);
				Put_block(1);
			}
			break;

		case 100:  //d
			if (x + 1 <= 24) {
				rm_block(x, y);
				x++;
				Gotoxy(x, y);
				Put_block(1);
			}
			break;

		case 97:  //a
			if (x - 1 >= 2) {
				rm_block(x, y);
				x--;
				Gotoxy(x, y);
				Put_block(1);
			}
			break;

		case 32:
			Gotoxy(x, y);
			Put_block(1);
			map[x][y] = 1;
			break;

		case 27:
			exit(0);
			break;

		case 13:   //enter
			file_save();
			return 1;
			break;

		case 8:   //backspace
			map[x][y] = 0;

		}



		Gotoxy(38, 15);
		printf("  %d %d  ", x, y);
	}
}

int file_save() {
	char save[128];
	int i, j;
	FILE  *fp;

	system("cls");

	if (GetCurrentDirectory(128, save) > 0) {
		printf("파일 저장 경로 : %s\n", save); 		// 지정경로를 출력
	}

	if (_mkdir("save") == 0) printf("디렉토리 생성 성공\n"); //지정된 경로로 폴더생성
	else printf("폴더가 이미 존재하거나 생성할 수 없습니다.\n");

	fp = fopen("save\\save.txt", "wt");

	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			fprintf(fp, "%d ", map[j][i]);
		}
		fprintf(fp, "\n");
	}


	fclose(fp);

	printf("완료");
	system("pause");
}

void Put_block(int color) {
	if (color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
		printf("■");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("■");
	}

}

void rm_block(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	Gotoxy(x, y);									// 현재 돌이 위치한 곳으로 이동 

	if (map[x][y] == 1) {
		Put_block(0);
	}
	else printf("  ");

}

void Gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = 2 * x - 2;   // 첫줄에 x좌표를 1로 설정
	Pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}