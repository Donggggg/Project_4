#define MAX_QUEUE_SIZE 10001
#define MAX 10000

//좌표
typedef struct xy{
	int x;
	int y;
}xy;

//정답입력
typedef struct Answer{
	char Yes_No;
	int num;
}Answer;

int isEmpty();
void enqueue(int x, int y);
xy dequeue();
int startMaze(int mode, int level, Game *game);
void makeMaze();
void breakWall(int x, int y);
void shortDistance(int x, int y);
int checkAnswer(int mode, Game *game);
