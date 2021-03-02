#include <stdio.h>

int sudoku[9][9] = {0};
int ran;

//지정된 두 가로 줄 교환// a,b:서로 다른 3*9집합의 가로 줄 번호(a<b)
void rowTrade(int a, int b){
	int tmp;
	for(int j = a*3; j<a+3;j++)
		for(int i = 0; i<9; i++){
			tmp = sudoku[j][i];
			sudoku[j][i] = sudoku[j+3*(b-a)][i];
			sudoku[j+3*(b-a)][i] = tmp;
		}
}
//지정된 두 세로 줄 교환// a,b:서로 다른 3*9집합의 세로 줄 번호(a<b)
void columnTrade(int a, int b){
	int tmp;
	for(int j = a*3; j<a+3; j++)
		for(int i = 0; i<9; i++){
			tmp = sudoku[i][j];
			sudoku[i][j] = sudoku[i][j+3*(b-a)];
			sudoku[i][j+3*(b-a)] = tmp;
		}
}

//3*9칸 가로끼리 혹은 세로끼리 교환
void tradeLine(){
	switch(ran%2){
		case 0:
			//가로 줄끼리 교환
			if(ran%3==2)		rowTrade(0,1);
			else if(ran%3==1)	rowTrade(1,2);
			else				rowTrade(0,2);
			break;
		case 1:
			//세로 줄끼리 교환
			if(ran%3==2)		columnTrade(0,1);
			else if(ran%3==1)	columnTrade(1,2);
			else				columnTrade(0,2);
			break;
		default: break;
	}
}
//3*9칸 가로끼리 혹은 세로끼리 모두 교환
void tradeAll(){
	switch(ran%3){
		case 1:
			//가로 전체 교환
			if(ran%2==1)	{rowTrade(0,1); rowTrade(0,2);}
			else			{rowTrade(0,1); rowTrade(1,2);}
			break;
		case 2:
			//세로 전체 교환
			if(ran%2==1)	{columnTrade(0,1); columnTrade(0,2);}
			else			{columnTrade(0,1); columnTrade(0,2);}
			break;
		case 3:
			//가로,세로 모두 교환
			break;
		default: break;
	}
}

void rotation(){
	int tmp;
	switch(ran%3){
	case 0:
		//90도 회전
		for(int a = 0; a<5; a++)
			for(int b = 0; b<4; b++){
				tmp = sudoku[a][b];
				sudoku[a][b] = sudoku[b][8-a];
				sudoku[b][8-a] = sudoku[8-a][8-b];
				sudoku[8-a][8-b] = sudoku[8-b][a];
				sudoku[8-b][a] = tmp;
			}
		break;
	case 1:
		//180도 회전
		for(int a = 0; a<5; a++)
			for(int b = 0; b<4; b++){
				tmp = sudoku[a][b];
				sudoku[a][b] = sudoku[8-a][8-b];
				sudoku[8-a][8-b] = tmp;
				tmp = sudoku[8-b][a];
				sudoku[8-b][a] = sudoku[b][8-a];
				sudoku[b][8-a] = tmp;
			}
		break;
	case 2:
		//270도 회전
		for(int a = 0; a<5; a++)
			for(int b = 0; b<4; b++){
				tmp = sudoku[a][b];
				sudoku[a][b] = sudoku[8-b][a];
				sudoku[8-b][a] = sudoku[8-a][8-b];
				sudoku[8-a][8-b] = sudoku[b][8-a];
				sudoku[b][8-a] = tmp;
			}
		break;
	default:break;
	}
}

void symmetry(){
	int tmp;
	switch(ran%4){
		case 0:	//x축 대칭
			for(int a = 0; a < 4; a++)
				for(int i = 0; i < 9; i++){
					tmp = sudoku[a][i];
					sudoku[a][i] = sudoku[8-a][i];
					sudoku[8-a][i] = tmp;
				}
			break;
		case 1:	//y축 대칭
			for(int a = 0; a < 4; a++)
				for(int i = 0; i < 9; i++){
					tmp = sudoku[i][a];
					sudoku[i][a] = sudoku[i][8-a];
					sudoku[i][8-a] = tmp;
				}
			break;
		case 2:	//y=x축 대칭
			for(int i = 0; i < 9; i++)
				for(int j = 0; j < 8-i; j++){
					tmp = sudoku[i][j];
					sudoku[i][j] = sudoku[8-j][8-i];
					sudoku[8-j][8-i] = tmp;
				}
			break;
		case 3:	//y=-x축 대칭
			for(int i = 0; i < 9; i++)
				for(int j = i+1; j < 9; j++){
					tmp = sudoku[i][j];
					sudoku[i][j] = sudoku[j][i];
					sudoku[j][i] = tmp;
				}
			break;
		default:break;
	}
}

void tradeNumber(){
	int num1, num2;
	num1 = ran%9+1;
	//랜덤 숫자 다시 생성
	num2 = ran%9+1;
	for(int i = 0; i<9; i++)
		for(int j = 0; j<9; j++){
			if(sudoku[i][j] == num1) sudoku[i][j] = num2;
			if(sudoku[i][j] == num2) sudoku[i][j] = num1;
		}
}

//void removeNum(int level, int weight){
	

int main(){

	return 0;
}
