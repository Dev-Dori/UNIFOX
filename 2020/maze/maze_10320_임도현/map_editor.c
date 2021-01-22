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
	system("mode con cols=120 lines=30 | title �̷�");
	//menu();

	int i, j;

	for (i = 1; i <= 25; i++) {
		for (j = 1; j <= 25; j++) {
			if (map[i][j] == 1) printf("��");
			if (map[i][j] == 0) printf("  ");
		}
		printf("\n");
	}

	map[1][2] = 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	Gotoxy(36, 3);
	printf("< �� ������ ����Ű >");
	Gotoxy(29, 5);
	printf("1. W A S D �� ���� �����̼���");
	Gotoxy(29, 6);
	printf("2. SPACEBAR �� ���� ���� �� �ֽ��ϴ�");
	Gotoxy(29, 7);
	printf("3. BACKSPACEBAR �� �̹� ������ ���� ���� �� �ֽ��ϴ�.");
	Gotoxy(29, 8);
	printf("4. �� ������ �Ϸ��ٸ� ENTER �� ���� SAVE ������ ���弼��.");
	control_block();
	return 0;
}



void menu() {
	system("mode con cols=80 lines=50 | title ���Ӹ޴�");
	printf("\n\n\n");
	printf("                #####     ###     ###     #    ####   #####     \n");
	printf("                #        #       #       # #   #   #  #         \n");
	printf("                #####    ####    #      #####  ####   #####     \n");
	printf("                #            #   #      #   #  #      #         \n");
	printf("                #####    ####     ###   #   #  #      #####     \n\n\n");
	printf("################################################################################\n\n");
}

//��Ʈ�� �г�
int control_block() {
	int x = 2, y = 2;
	char key;
	Gotoxy(x, y);
	Put_block(1);
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);  //��y �� x
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
		printf("���� ���� ��� : %s\n", save); 		// ������θ� ���
	}

	if (_mkdir("save") == 0) printf("���丮 ���� ����\n"); //������ ��η� ��������
	else printf("������ �̹� �����ϰų� ������ �� �����ϴ�.\n");

	fp = fopen("save\\save.txt", "wt");

	for (i = 0; i < 26; i++) {
		for (j = 0; j < 26; j++) {
			fprintf(fp, "%d ", map[j][i]);
		}
		fprintf(fp, "\n");
	}


	fclose(fp);

	printf("�Ϸ�");
	system("pause");
}

void Put_block(int color) {
	if (color) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf("��");
	}

}

void rm_block(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	Gotoxy(x, y);									// ���� ���� ��ġ�� ������ �̵� 

	if (map[x][y] == 1) {
		Put_block(0);
	}
	else printf("  ");

}

void Gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = 2 * x - 2;   // ù�ٿ� x��ǥ�� 1�� ����
	Pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}