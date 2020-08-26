#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>                                 
#include <Windows.h>                               
#include <process.h>

int stone_turn = 1;  // (전역변수) 흑돌과 백돌 순서   1=흑 2=백
int Omok_Board[20][20] = { 0, }; // 좌표를 배열로 표현할때 사용하는 (전역배열)
int time = 0;   //시간을 나타내는 전역변수

int explain(); //방법 설명 함수
void Omok_Game_background();  //바둑판
void Gotoxy(int x, int y);  //바둑판 좌표를 구현하는 함수
void Put_stone(int color);    //돌을 놓는 함수
int control_stone(); // 바둑알 컨트롤 함수
void rm_stone(int x, int y); //바둑알 이동시 전칸 돌 삭제
int game_check(int x, int y);  //승패를 결정하는 함수
unsigned _stdcall timer(void *arg); //타이머

int main(void) {
	system("mode con cols=90 lines=22 | title 오목");
	int cot= explain();
	if (cot == 0) return 0; 
	Omok_Game_background();
	control_stone();
}

int explain()
{
	char press;
	Gotoxy(15, 2);
	printf("*****  오목 룰   *****\n");
	Gotoxy(9,5);
	printf("* 흑돌이 먼저 수를 두게 됩니다 *\n");
	Gotoxy(9, 7);
	printf("* 돌이 5개 이상 연결되면 승리합니다 *\n");
	Gotoxy(9, 9);
	printf("* 게임을 시작하시려면 Space Bar를 눌러주세요 *\n");
	Gotoxy(9, 11);
	printf("* 게임을 종료하시려면 Esc를 눌러주세요 *");


	Gotoxy(17, 14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("*** 조작법 ***\n\n\n");
	printf("조작1 :: 위로 이동: W    아래로 이동: W    왼쪽 이동: A    오른쪽 이동: D  착수: SPACEBAR\n\n");
	printf("조작2 :: 위로 이동: 8    아래로 이동: 5    왼쪽 이동: 4    오른쪽 이동: 6  착수:    0\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("                                                                           10320 - 임도현");


	for (; 1;) {
		press = _getch();
		if (press == 27) return 0;
		if (press == 32) {
			Gotoxy(0, 0);
			system("cls");
			return 1;
		}
	}
}

//컨트롤 패널
int control_stone() {
	int x = 10, y = 10;
	char key;
	Gotoxy(10, 10);
	Put_stone(stone_turn);
	_beginthreadex(NULL, 0, timer, 0, 0, NULL);
	while (1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		Gotoxy(28, 10);
		printf("-[ ");
		Put_stone(stone_turn);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		printf(" 차례입니다. ]-");   //수정

		key = _getch();

		if (65 <= key && key <= 90) key = +32;
		if (key == 56) key = 119;
		else if (key == 48	) key = 32;
		else if (key == 52) key = 97;
		else if (key == 54) key = 100;
		else if (key == 53) key = 115;

		switch (key) {     //a=97 d=100 w=119 s=115
		case 119:  //w
			if (1 <= y - 1 && y - 1 < 19) {
				rm_stone(x, y);
				y--;
				Gotoxy(x, y);
				Put_stone(stone_turn);
			}
			break;

		case 115:  //s
			if (1 < y + 1 && y + 1 <= 19) {
				rm_stone(x, y);
				y++;
				Gotoxy(x, y);
				Put_stone(stone_turn);
			}
			break;

		case 100:  //d
			if (1 < x + 1 && x + 1 <= 19) {
				rm_stone(x, y);
				x++;
				Gotoxy(x, y);
				Put_stone(stone_turn);
			}
			break;

		case 97:  //a
			if (1 <= x - 1 && x - 1 < 19) {
				rm_stone(x, y);
				x--;
				Gotoxy(x, y);
				Put_stone(stone_turn);
			}
			break;


		case 32:
			Gotoxy(29, 8);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("좌표 : [%d][%d]", x, y);
			Gotoxy(x, y);
			if (Omok_Board[x][y] == 0) {
				Omok_Board[x][y] = stone_turn;
				Put_stone(stone_turn);

				if (game_check(x, y) == 1) {
					Gotoxy(22, 12);
					printf("################################################");
					Gotoxy(22, 13);
					printf("##                  ");
					Put_stone(stone_turn);
					printf("돌 승리                 ##");
					Gotoxy(22, 14);
					printf("################################################");
					Gotoxy(38, 1);  printf("                ");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					Gotoxy(29, 16); printf("[ 종료 :: ESC  ]");
					stone_turn = 4; // 타이머 종료
					
					while (1) {
						key = _getch();
						if(key==27) _endthread();
						
					}
				}

			if (stone_turn==1) stone_turn++;
			else if(stone_turn==2)stone_turn--;


			Gotoxy(27, 7);
			printf("                            ");

			break;
			} 
			else {
				Gotoxy(27, 7);
				printf("[주의!!] 이미 돌이 있습니다");
				continue;
			}
		case 27:
			exit(0);
		}
	}
}

//움직였을때 지우기
void rm_stone(int x, int y) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	Gotoxy(x, y);									// 현재 돌이 위치한 곳으로 이동 

	if (Omok_Board[x][y] == 0) {
		if (x == 1 && y == 1)                           // 그곳이 만약 1,1 (왼쪽 위 모서리)인 경우
			printf("┌─");
		else if (x == 19 && y == 1) {                     // 그곳이 만약 19,1 (오른쪽 위 모서리)인 경우
			printf("  ");  //버그 처리용도
			Gotoxy(x, y);
			printf("┐");
		}
		else if (x == 1 && y == 19)                     // 그곳이 만약 0,19 (왼쪽 아래 모서리)인 경우
			printf("└─");
		else if (x == 19 && y == 19) {                  // 그곳이 만약 19,19 (오른쪽 아래 모서리)인 경우
			printf("  ");
			Gotoxy(x, y);
			printf("┘");
		}
		else if (x == 1)                                // 그곳이 만약 1,* (왼쪽줄)인 경우                 
			printf("├─");
		else if (y == 1)                                // 그곳이 만약 *,1 (윗줄)인 경우
			printf("┬─");
		else if (x == 19) {								// 그곳이 만약 19,* (오른쪽줄)인 경우
			printf("  ");
			Gotoxy(x, y);
			printf("┤");
		}
		else if (y == 19)                               // 그곳이 만약 *,19 (아랫줄)인 경우
			printf("┴─");
		else                                           // 그 외의 경우
			printf("┼─");
	}else if(Omok_Board[x][y]==1){
		Put_stone(1);
	}else if(Omok_Board[x][y] == 2){
		Put_stone(2);
	}
}

//좌표
void Gotoxy(int x, int y){
	COORD Pos;
	Pos.X = 2*x-2;   // 첫줄에 x좌표를 1로 설정
	Pos.Y = y-1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//게임화면 구현
void Omok_Game_background(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	int i, j;
	printf("┌─");
	for (i = 0; i < 17; i++) printf("┬─");

	printf("┐  %d\n",1);

	for (i = 0; i < 17; i++) {
		printf("├─");
		for (j = 0; j < 17; j++)
			printf("┼─");
		printf("┤  %d\n",i+2);
	}
	printf("└─");
	for (i = 0; i < 17; i++)printf("┴─");
	printf("┘  %d\n",19);

	Gotoxy(1, 48);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("==========================================================================================\n");
	printf("조작1 :: 위로 이동: W    아래로 이동: W    왼쪽 이동: A    오른쪽 이동: D  착수: SPACEBAR\n");
	printf("조작2 :: 위로 이동: 8    아래로 이동: 5    왼쪽 이동: 4    오른쪽 이동: 6  착수:    0");

	Gotoxy(30, 3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("<----조작---->\n");
	Gotoxy(24, 4);
	printf("W A S D 로 움직이고 스페이스키를 누르시오\n");
	Gotoxy(39, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("<ESC :: 종료 >");
}

//돌 출력
void Put_stone(int color) {
	if (color==1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); //흑
		printf("○");
	}
	else if(color==2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //백
		printf("●");
	}
}


//승패 체크
int game_check(int x, int y) {
	int i, j = 0, k = 1, count = 0;
	int a[20] = { 0, };   //5줄 체크할때 사용하는 배열 초기화
	for (i = 0; i <= 5; i++) a[i] = 0; j = 0;  //5줄 체크할때 사용하는 배열 초기화
	for (i = 1; i <= 19; i++) {    //세로 체크
		for (j = 0; j <= 4; j++) {  // 
			a[j] = Omok_Board[i + j][y];
		}
		for (j = 0; j <= 4; j++) {  // 
			if (a[j] == stone_turn) count++;
		}
		if (count == 5) return 1;
		for (j = 0; j < 5; j++) a[i] = 0;
		count = 0;
	}

	for (i = 0; i <=5; i++) a[i] = 0; j = 0;  //5줄 체크할때 사용하는 배열 초기화
	for (i = 1; i <= 19; i++) {    //세로 체크
		for (j = 0; j <= 4; j++) {  // 
			a[j] = Omok_Board[x][i + j];
		}
		for (j = 0; j <= 4; j++) {  // 
			if (a[j] == stone_turn) count++;
		}
		if (count == 5) return 1;
		for (j = 0; j < 5; j++) a[i] = 0;
		count = 0;
	}

	for (i = 0; i <= 5; i++) a[i] = 0;  j = 0;//5줄 체크할때 사용하는 배열 초기화
	for (i = x - y + 1; i+5 <= 19; i++) {    //대각선↘ 체크
		if (i > 0) {
			for (j = 0; j <= 4; j++) {  // 
				a[j] = Omok_Board[i+j][k+j];
			}
			for (j = 0; j <= 4; j++) {  // 
				if (a[j] == stone_turn) count++;
			}
			if (count == 5) return 1;
			for (j = 0; j < 5; j++) a[i] = 0;
			count = 0;
		}
		k++;
	}

	k = 1; 	for (i = 0; i <= 5; i++) a[i] = 0;  j = 0;//5줄 체크할때 사용하는 배열 초기화
	for (i = x + y - 1; i >= 1; i--) {    //대각선↗ 체크
		if (i > 0) {
			for (j = 0; j <= 4; j++) {  // 
				a[j] = Omok_Board[k + j][i - j];
			}
			for (j = 0; j <= 4; j++) {  //  
				if (a[j] == stone_turn) count++;
			}
			if (count == 5) return 1;
			for (j = 0; j < 5; j++) a[j] = 0;
			count = 0;
		}
		k++;
	}
}
unsigned _stdcall timer(void *arg) {
	while (1) {
		Gotoxy(22, 1);
		printf("[플레이시간 : %d sec]", time);
		if (stone_turn == 4) return 1;
		Sleep(1040);
		time++;
	}
}