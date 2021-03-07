#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include "main.h"

int N;
int now;
int front;
int rear;
int maze[51][51];
int wall[51][51];
int visit[51][51];

xy queue[MAX_QUEUE_SIZE];

//방향 (상 하 좌 우)
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

int isEmpty(){
	if (front == rear){
		return 1;
	}
	else
		return 0;
}

void enqueue(int x,int y){
	xy temp;
	temp.x = x;
	temp.y = y;
	rear = rear % MAX_QUEUE_SIZE;
	queue[rear++] = temp;
}

xy dequeue(){
	front = front % MAX_QUEUE_SIZE;
	return queue[front++];
}
 
int startMaze(int mode, int level){
	srand(time(NULL));
	
	if(mode == SOLO){
		N = 5 + level;
		
		//wall배열 최댓값으로 초기화
		for (int x = 1; x <= N; x++){
			for (int y = 1; y <= N; y++){
				wall[x][y] = MAX;
			}
		}

		makeMaze();

		visit[1][1] = 0;
		wall[1][1] = 0;

		enqueue(1,1);
		shortDistance(1, 1);
		enqueue(1, 1);
		breakWall(1, 1);
		
		return 	checkAnswer();
	}
	else if(mode == MULTI){
		printf("다인모드입니다.\n");

		//wall배열 최댓값으로 초기화
		for (int x = 1; x <= N; x++){
			for (int y = 1; y <= N; y++){
				wall[x][y] = MAX;
			}
		}

		makeMaze();

		visit[1][1] = 0;
		wall[1][1] = 0;

		enqueue(1,1);
		shortDistance(1, 1);
		enqueue(1, 1);
		breakWall(1, 1);

		return checkAnswer();
	}
}

//미로 출력 함수
void makeMaze(){
	
	//미로 받는 부분
	for (int x = 1; x <= N; x++){
		for (int y = 1; y <= N; y++){
			if (x == 1 && y == 1){
				maze[x][y] = 1;
			}
			else if (x == N && y == N){
				maze[x][y] = 1;
			}
			else{
				maze[x][y] = rand() % 2;
			}
		}
	}

	//미로 출력
	for (int x = 1; x <= N; x++){
		for (int y = 1; y <= N; y++){
			printf("%d", maze[x][y]);
		}
		printf("\n");
	}
}

//미로 벽뚫기 함수
void breakWall(int x, int y){
	int nx;
	int ny;
	while(! isEmpty()){
		xy pop = dequeue();
		for (int i = 0; i < 4; i++){
			nx = pop.x + dx[i];
			ny = pop.y + dy[i];

			//미로판을 아예 나갈 때
			if (nx < 1 || nx > N || ny < 1 || ny > N){
				continue;
			}
			
			//벽인 경우
			if (maze[nx][ny] == 0){
				if (wall[nx][ny] > wall[pop.x][pop.y] + 1){
					wall[nx][ny] = wall[pop.x][pop.y] + 1;
					enqueue(nx, ny);
				}
			}

			//길인 경우
			else if(maze[nx][ny] == 1){
				if (wall[nx][ny] > wall[pop.x][pop.y]){
					wall[nx][ny] = wall[pop.x][pop.y];
					enqueue(nx, ny);
				}
			}
		}
	}
}

//미로 최단거리 찾는 함수
void shortDistance(int x, int y){
	int nx;
	int ny;
	while(! isEmpty()){
		xy pop = dequeue();
		for (int i = 0; i < 4; i++){
			nx = pop.x + dx[i];
			ny = pop.y + dy[i];

			//미로판을 아예 나갈 때
			if (nx < 1 || nx > N || ny <1 || ny > N)
				continue;
			//벽인 경우
			if (maze[nx][ny] == 0)
				continue;
			//
			if (visit[nx][ny] == 0){
				visit[nx][ny] = visit[pop.x][pop.y] + 1;
				enqueue(nx, ny);
			}
		}
	}
}

//정답 확인 함수
int checkAnswer(){
	Answer answer;
	int wrong = 0;
	int maze_check; //미로가 탈출 가능하면 1, 아닐 경우 0
	int count = 0; //정답일 경우 1, 아닐 경우 0

	//탈출 가능한 미로인지 확인 여부
	if (wall[N][N] == 0){
		maze_check = 1;
	}
	else{
		maze_check = 0;
	}
	if (maze_check == 1)
		printf("%d %d", maze_check, visit[N][N]);
	else if (maze_check == 0)
		printf("%d %d", maze_check, wall[N][N]);

	//정답 확인
	while (count != 1){
		//답 입력
		printf("\n탈출이 가능한가요? (O or X) : ");
		scanf(" %c", &answer.Yes_No);
		if (answer.Yes_No == 'O' || answer.Yes_No == 'o'){
			printf("미로를 탈출하기 위한 최단경로의 길이는? : ");
			scanf("%d", &answer.num);
		}
		else if (answer.Yes_No == 'X' || answer.Yes_No == 'x'){
			printf("미로를 탈출하기 위해 뚫어야 하는 벽의 개수는? : ");
			scanf("%d", &answer.num);
		}
		//정답인지 확인
		if (maze_check == 1){
			if (answer.Yes_No == 'O' || answer.Yes_No == 'o'){
				if (answer.num == visit[N][N]){
					count = 1;
				}
				else{
					printf("\n틀렸습니다.\n");
					wrong++;
					continue;
				}
			}
			else{
				printf("\n틀렸습니다.\n");
				wrong++;
				continue;
			}
		}
		else if (maze_check == 0){
			if (answer.Yes_No == 'X' || answer.Yes_No == 'x'){
				if (answer.num == wall[N][N]){
					count = 1;
				}
				else{
					printf("\n틀렸습니다.\n");
					wrong++;
					continue;
				}
			}
			else{
				printf("\n틀렸습니다.\n");
				wrong++;
				continue;
			}
		}
	}
	printf("\n정답입니다.\n");
	return wrong;
}
