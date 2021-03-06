typedef struct Miro{
	//	int maze[51][51];
	//	Answer answer;


} Miro;

typedef struct Sudoku{
	//	_Sudoku sudoku;
	//	_Player player;

} Sudoku;

typedef struct Game{ 
	int people; //최대 인원을 5명으로 가정
	int level; //현재 난이도
	int game_select[10]; //1은 미로, 2는 스도쿠(최대 10라운드 -> 0-9라운드 정보)
	int round[2]; // 현재 라운드/총라운드
	int score[5]; // 각 인원당 스코어
	int plus_score[5]; //각 인원당 해당 라운드 획득할 스코어
	int minus_score; //틀릴 때마다 감점되는 점수

} Game;

typedef struct Setting{
	
	int miro_round;
	int sudoku_round;
	//난이도 당 곱하는 건 미로, 스도쿠에서 구현 완료
	int minus_score; //다인모드 감점 스코어

} Setting;

void setOption(Setting *set);
void setGame(Game *game);
void saveGame(Game *game);
int roadGame(Game *game);
void deleteFile();
