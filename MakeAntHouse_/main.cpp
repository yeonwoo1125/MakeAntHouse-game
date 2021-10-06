#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h> //커서 이동
#include<conio.h> //_getch()
#include<stdbool.h> //boolean 타입 사용
#include<time.h> //랜덤 함수 사용
#include<string>
//#include<mysql.h> //mysql 관련 함수 사용
#pragma comment(lib, "winmm.lib") // timeGetTime() 함수 사용을 위한 라이브러리

using namespace std;
#define MAGIC_KEY 224 //상하좌우 화살표가 들어올 때 선행되어 들어오는 숫자
#define SPACE 32 //스페이스 키 값
#define ENTER 13 //엔터 키 값
#define ESC 27 //esc 키 값

string user_Nickname; //사용자 이름
string plz_space = "[스페이스나 엔터를 눌러주세요.]";
int houseSize = 20; //개미집 크기

enum GUEST {
	LOGIN_USER,
	START,
	QUITGUEST
};
enum LOGIN {
	CREATE,
	FIND,
	QUESTION,
	QUITLOGIN
};

enum MENU {
	GAMESTART = 0,
	INFO,
	QUIT,
	ACCOUNT
};

enum KEYBOARD {
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};

//화면 그리는 함수
void DrawReadyGame();
void DrawFirstInfoGame();
void DrawSecondeInfoGame();
void DrawStartGame();
void DrawGameOver();
void DrawGamePass();
void DrawLogin();
void DrawGuestLogin();
void DrawStartMiniGame();
void DrawDieAnt();

void DrawFIndAcc();
void DrawFindId();
void DrawFindPw();

//메뉴 고르기
GUEST selectGuest();
LOGIN SelectLogin();
MENU ReadyGame();


//미니게임
bool RockPaperScissors();
bool QuizGame();
bool upDownGame();
void timingGame();

//뷰
void InfoGame();
void startGame();
int userLogin();

//게임 시작 준비
int checkReady();
int checkGuest();
void readyStart();

//로그인 관련
void CreateAccount();
bool LoginAccount();
int QuestionAccount();

void gotoxy(int x, int y) { //커서를 특정 위치로 이동시키는 함수
	COORD Pos;
	Pos.X = 2 * x; //1칸보다는 2칸씩 움직여야 자연스러움
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//콘솔 크기, 타이틀
void SetConsoleVIew() {
	system("mode con:cols=100 lines=30"); //가로 50, 세로 20
	system("title Make Ant House By Yeonwoo"); //타이틀
}

class ant { //개미집에서 움직일 개미 객체
private :
	int ant_x, ant_y;
	int input = 0;
	char feed = '*';
	int feed_x;
	int feed_y;
	int feedCnt = 3; //기본적으로 집에 3개 생성
public:
	ant() : ant_x(0), ant_y(0),feed_x(0),feed_y(0){} //개미의 생성 위치를 집 안으로 정해야함
	int getFeedCnt() { //현재 개미집에 생성된 먹이의 수
		return feedCnt;
	}
	void ranFeed() {
		feed_x = rand() % ant_x; //개미집 내부에 먹이 생성 - >개미집 가로세로보다 작은 수임
		feed_y = rand() % ant_y;

		for (int i = 0; i < feedCnt; i++) {
			gotoxy(feed_x, feed_y);
			cout << feed;
			Sleep(5000); //5초마다 먹이 생성
			feedCnt++;
		}
	}

	void moveInHouse() { //개미집 안에서 움직임
		while (true) {
			input = _getch();
			
			if (input == MAGIC_KEY) {
				input = _getch();
				switch (input)
				{
				case UP:
					gotoxy(ant_x, ant_y);
					cout << "   ";
					gotoxy(ant_x, ant_y);
					cout << " ";
					gotoxy(ant_x, ant_y+1);
					cout << " ";
					gotoxy(ant_x, ant_y+2);
					cout << " ";
					ant_y--;
					gotoxy(ant_x, ant_y);
					cout << "*";
					gotoxy(ant_x, ant_y+1);
					cout << "*";
					gotoxy(ant_x, ant_y+2);
					cout << "*";
					break;
				case DOWN:
					gotoxy(ant_x, ant_y);
					cout << "   ";
					gotoxy(ant_x, ant_y);
					cout << " ";
					gotoxy(ant_x, ant_y + 1);
					cout << " ";
					gotoxy(ant_x, ant_y + 2);
					cout << " ";
					ant_y++;
					gotoxy(ant_x, ant_y);
					cout << "*";
					gotoxy(ant_x, ant_y + 1);
					cout << "*";
					gotoxy(ant_x, ant_y + 2);
					cout << "*";
					break;
				case RIGHT:
					gotoxy(ant_x, ant_y);
					cout << "   ";
					gotoxy(ant_x, ant_y);
					cout << " ";
					gotoxy(ant_x, ant_y + 1);
					cout << " ";
					gotoxy(ant_x, ant_y + 2);
					cout << " ";
					ant_x++;
					gotoxy(ant_x, ant_y);
					cout << "***";
					break;
				case LEFT:
					gotoxy(ant_x, ant_y);
					cout << "   ";
					gotoxy(ant_x, ant_y);
					cout << " ";
					gotoxy(ant_x, ant_y + 1);
					cout << " ";
					gotoxy(ant_x, ant_y + 2);
					cout << " ";
					ant_x--;
					gotoxy(ant_x, ant_y);
					cout << "***";
					break;
				}
			}
		}
	}
	void collisonCheck() { //개미가 개미집 벽에 닿은 경우
		//만약 집이 두개 이상이면 벽에 닿을 경우 해당 방향에 있는 집으로 이동
		//집이 없다면 그냥 더이상 앞으로 못나가게
		
	}
	void eatFeed() { //개미가 먹이를 먹은 경우 - 먹이를 지우고 미니게임 실행 
		//개미 집 내부, 랜덤한 좌표에 먹이(*) 생성
		//좌표가 겹칠 경우, 미니게임 실행
		//case 0 -> RockPaperScissors
		//case 1 -> QuizGame
		//case 2 -> upDownGame
		//case 3 -> timingGame
		if (ant_x == feed_x && ant_y == feed_y) {
			feedCnt--;
			int miniGame;
			miniGame = rand() % 4;
			switch (miniGame)
			{
			case 0:
				system("cls");
				RockPaperScissors();
				break;
			case 1:
				system("cls");
				QuizGame();
				break;
			case 2:
				system("cls");
				upDownGame();
				break;
			case 3:
				system("cls");
				cout << "보너스 게임";
				cout << "얻는 점수만큼 집이 커집니다.";
				timingGame();
				break;
			}
		}
	}
	void drawAntHouse(int r) {
		//system("cls");
		//기본 집 그리기
		gotoxy(1, 3);
		cout << "집의 크기 : " << r << endl;

		//집이 일정 크기 이상이면 반으로 나누고 집을 여러개 연결되게 만듦
		int i, j;
		for (i = 1; i <= r; i++)
		{
			for (j = 1; j <= r; j++)
			{
				if (i == 1 || i == r|| j == 1 || j == r)
					cout << "*";
				else
					cout << " ";
			}
			cout << endl;
		}
		//ranFeed();
		//eatFeed();
	}
	~ant() {}
};


class Login { //유저가 로그인 시 계정 저장 및 계정 생성 시 정보 저장
	string user_account;
	int user_id;
	string user_password;
	bool loginCheck = false; //로그인 성공 여부 파악
	string idAnswer, pwAnswer;
	string user_name;
public:
	Login() {
		this->user_id = (rand() % 100000); //랜덤 아이디 제공
	}
	void setUserName(string userName) {
		this->user_name = userName;
	}
	string getUserName() {
		return user_name;
	}
	void setIdAnswer(string idAns) {
		this->idAnswer = idAns;
	}
	string getIdAnswer() {
		return idAnswer;
	}
	void setPwAnswer(string pwAns) {
		this->pwAnswer = pwAns;
	}
	string getPwAnswer() {
		return pwAnswer;
	}
	void setUserAcc(string userAcc) {
		this->user_account = userAcc;
	}
	string getuserAcc() {
		return user_account;
	}
	int getuserId() {
		return user_id;
	}
	string getuserPw() {
		return user_password;
	}
	void setUserPw(string userPw) {
		this->user_password = userPw;
	}
	bool getLoginCheck() {
		return loginCheck;
	}

	bool checkUser(string acc, string pw) { //사용자가 입력한 계정이 있는 계정인지 체크
		int input=0;
		if (getuserAcc() == acc && getuserPw() == pw) {
			loginCheck = true;
			system("cls");
			gotoxy(21, 12);
			cout << "로그인 성공" ;
			gotoxy(16, 15);
			cout << plz_space;
			system("pause>null");
			return true;   
		}
			else if (getuserPw() != pw || getuserAcc() != acc) {
				system("cls");
				gotoxy(21, 9);
				cout << "로그인 실패" << endl;
				gotoxy(14, 11);
				cout << "다시 시도하시려면 스페이스를 눌러주세요." << endl;
				gotoxy(14, 12);
				cout << "스페이스를 누르면 로그인을 재시도합니다." << endl;
				gotoxy(17, 13);
				cout << "나가시려면 ESC를 눌러주세요.";
				while (true) {
					input = _getch();
					if (input == ESC) {
						return false;
					}
					if (input == SPACE) {
						system("cls");
						string acc;
						string pw;
						gotoxy(16, 8);
						cout << "계정 입력 : ";
						cin >> acc;
						gotoxy(16, 10);
						cout << "비밀번호 입력 : ";
						cin >> pw;
						checkUser(acc, pw);
					}
				}
				return false;
			}
	}
	~Login() {}
};

Login* user = new Login();
ant a1;

int checkGuest() { //게스트로 로그인 할건지 물음
	DrawGuestLogin();

	while (true) {
		switch (selectGuest()) { //리턴을 받아 판단
		case LOGIN_USER:
			return 2;
			break;
		case START:
			return 1;
			break;
		case QUITGUEST:
			return 0;
		}
	}
}


//메인 메뉴 그리기
void DrawReadyGame() {
	system("cls");    //화면을 클리어 해주는 함수 입니다.
	gotoxy(15, 4);
	cout << "**************************************";
	gotoxy(15, 5);
	cout << "*                                    *";
	gotoxy(15, 6);
	cout << "*              영차영차              *";
	gotoxy(15, 7);
	cout << "*        개미집을 만들어주자         *";
	gotoxy(15, 8);
	cout << "*                                    *";
	gotoxy(15, 9);
	cout << "**************************************";
	gotoxy(22, 12);
	cout << "게임시작";
	gotoxy(22, 13);
	cout << "게임설명";
	gotoxy(22, 14);
	cout << "로 그 인" << endl;
	gotoxy(22, 15);
	cout << "나 가 기" << endl;

	gotoxy(17, 19);
	cout << plz_space;
}

//게임 설명 그리기
void DrawFirstInfoGame()
{
	system("cls");
	gotoxy(3, 3);
	cout << "****************";
	gotoxy(3, 4);
	cout << "*   게임설명   *";
	gotoxy(3, 5);
	cout << "****************";

	gotoxy(3, 8);
	cout << "개미들이 다리를 다쳐서 집을 짓지 못하고 있어요!";
	gotoxy(3, 9);
	cout << "당신이 개미들이 집 만드는 걸 도와줬으면 좋겠어요..";
	gotoxy(3, 10);
	cout << "집을 만드는 방법은 간단해요!";
	gotoxy(3, 12);
	cout << "1) 원하는 집의 방향을 골라주세요.";
	gotoxy(3, 13);
	cout << "2) 집을 만들기 위해 간단한 게임을 해주세요.";
	gotoxy(3, 14);
	cout << "3) 게임에서 이기면 계속해서 집을 만들 수 있지만,";
	gotoxy(3, 15);
	cout << "   만약 진다면 더 이상 집을 짓지 못해요.";
	gotoxy(3, 19);
	cout << "그럼 잘 부탁해요!!";
	gotoxy(38, 22);
	cout << "다음 페이지";
	gotoxy(37, 22);
	cout << ">";
	system("pause>null");
}

void DrawSecondeInfoGame()
{
	system("cls");
	gotoxy(3, 3);
	cout << "****************";
	gotoxy(3, 4);
	cout << "*   순서설명   *";
	gotoxy(3, 5);
	cout << "****************";

	gotoxy(3, 8);
	cout << "게임을 처음 시작하시는 분은 회원가입을 해주세요.(로그인->회원가입)";
	gotoxy(3, 9);
	cout << "이미 계정이 존재한다면 로그인을 한 후 게임을 진행하면 됩니다.";
	gotoxy(3, 10);
	cout << "계정을 잃어버렸을 경우, 계정 찾기를 통해 계정을 찾아주세요.(로그인->계정 찾기)";
	gotoxy(3, 11);
	cout << "로그인 없이 게임을 하고 싶다면 게스트 로그인을 통해 게임을 즐겨주세요.";
	gotoxy(3, 13);
	cout << "제일 처음 게임을 시작하면, 미니게임을 통해 기본 크기의 개미집을 얻게 됩니다.";
	gotoxy(3, 14);
	cout << "개미집에 생성되는 개미의 먹이를 먹으면 미니게임을 할 수 있습니다. ";
	gotoxy(3, 15);
	cout << "하지만 오랜 시간 먹이를 먹지 않으면 개미가 죽을 수도 있으니 조심하세요.";
	gotoxy(3, 19);
	cout << "그럼 즐거운 시간 되세요!";
	gotoxy(16, 22);
	cout << plz_space;
}


//시작 화면 그리기
//디비 연동 후 계정이 없는 처음에만 실행
void DrawStartGame() {
	if (user_Nickname == "") {
		system("cls");
		gotoxy(14, 9);
		cout << "개미들이 다리를 다쳐 집을 짓지 못하고 있어요!";
		gotoxy(15, 10);
		cout << "당신이 개미들의 집을 만들어주면 좋겠어요.";
		gotoxy(13, 11);
		cout << "개미들에게 당신의 이름을 알려주면 보답을 할거예요.";
		gotoxy(15, 12);
		cout << " 당신의 이름이 무엇인가요? : ";
		cin >> user_Nickname;
	}
}
//개미 죽는 모습 - 게임 오버 그리기
void DrawDieAnt() { //개미집이 0보다 작아졌을 경우, 먹이를 먹지 않았을 경우
	if (a1.getFeedCnt() > 9) {
		gotoxy(18, 10);
		cout << user_Nickname << "님의 개미가 굶어죽었습니다.";
		gotoxy(18, 11);
		cout << user_Nickname << "님의 집의 크기는 "<<houseSize<<"입니다.";
		gotoxy(18, 14);
		DrawGameOver();
	}
	else if (houseSize <= 0) {
		gotoxy(18, 10);
		cout << user_Nickname << "님의 집이 부숴져 개미가 이사를 갔습니다.";
		gotoxy(18, 12);
		DrawGameOver();
	}
}

//미니게임 시작 화면 그리기
void DrawStartMiniGame() {
	system("cls");
	gotoxy(15, 8);
	cout << "--------------------------";
	gotoxy(15, 9);
	cout << "|   현재 집이 없으므로   |";
	gotoxy(15, 10);
	cout << "|  미니게임을 실행합니다 |";
	gotoxy(15, 11);
	cout << "--------------------------";
	gotoxy(14, 14);
	cout << plz_space;
	system("pause>null");
}

//게임 오버 그리기
void DrawGameOver() {
	gotoxy(8, 8);
	cout << "-------------------";
	gotoxy(8, 9);
	cout << "| G A M E O V E R |";
	gotoxy(8, 10);
	cout << "-------------------";
	gotoxy(7, 14);
	cout << plz_space;
	system("pause>null");
}
//게임 통과 그리기
void DrawGamePass() {
	gotoxy(8, 8);
	cout << "-------------------";
	gotoxy(8, 9);
	cout << "| G A M E P A S S |";
	gotoxy(8, 10);
	cout << "-------------------";
	gotoxy(7, 14);
	cout << plz_space;
	system("pause>null");
}
//로그인 화면 그리기
void DrawLogin() {

	system("cls");    //화면을 클리어 해주는 함수

	gotoxy(22, 12);
	cout << "로 그 인";
	gotoxy(22, 13);
	cout << "회원가입";
	gotoxy(22, 14);
	cout << "계정찾기";
	gotoxy(22, 15);
	cout << "나 가 기";

	gotoxy(17, 19);
	cout << plz_space;
}

//게스트 로그인 화면 그리기
void DrawGuestLogin() {
	system("cls");
	gotoxy(17, 8);
	cout << "게스트로 로그인 하시겠습니까?";
	gotoxy(13, 9);
	cout << "게스트로 로그인 시 게임 종료 후 저장되지 않습니다.";
	gotoxy(23, 12);
	cout << "로 그 인";
	gotoxy(23, 13);
	cout << "게임시작";
	gotoxy(23, 14);
	cout << "나 가 기";

	gotoxy(18, 17);
	cout << plz_space;
}
//계정찾기 화면 그리기
void DrawFIndAcc() {
	system("cls");
	gotoxy(20, 3);
	cout << "****************";
	gotoxy(20, 4);
	cout << "*   계정찾기   *";
	gotoxy(20, 5);
	cout << "****************";
	gotoxy(15, 13);
	cout << "계정명 찾기";
	gotoxy(27, 13);
	cout << "비밀번호 찾기";
	gotoxy(15, 15);
	cout << "로그인 하기";
	gotoxy(27, 15);
	cout << "메인으로 가기";
}
//아이디 찾기 화면 그리기
void DrawFindId() {
	string answer;
	int input = 0;
	system("cls");
	gotoxy(20, 3);
	cout << "******************";
	gotoxy(20, 4);
	cout << "*   아이디찾기   *";
	gotoxy(20, 5);
	cout << "******************";
	while (true) {
		system("cls");
		if (user->getIdAnswer().empty()) {
			gotoxy(18, 11);
			cout << "먼저 계정을 생성해주세요.";
			gotoxy(16, 14);
			cout << plz_space;
			system("pause>null");
			break;
		}

		gotoxy(15, 8);
		cout << "질문에 대한 답을 하시면 힌트가 제공됩니다.";
		gotoxy(15, 10);
		cout << "가장 좋아하는 전공은? : ";
		cin >> answer;
		
		if (user->getIdAnswer() == answer) {
			gotoxy(15, 12);
			cout << user->getUserName() << "님의 아이디는 " << user->getuserAcc();
			system("pause>null");
			break;
		}
		
		else {
			gotoxy(20, 14);
			cout << "다시 입력해주세요.";
			gotoxy(18, 15);
			cout << "ESC를 누르면 종료합니다.";
			
			input = _getch();
			if (input == ESC) break;
			else continue;
		}
	}
}

//비밀번호 찾기 화면 그리기
void DrawFindPw() {
	string answer;
	string userId;
	int input = 0;
	system("cls");
	gotoxy(20, 3);
	cout << "********************";
	gotoxy(20, 4);
	cout << "*   비밀번호찾기   *";
	gotoxy(20, 5);
	cout << "********************";
	while (true) {
		system("cls");
		if (user->getPwAnswer().empty()) {
			gotoxy(18, 11);
			cout << "먼저 계정을 생성해주세요.";
			gotoxy(16, 14);
			cout << plz_space;
			system("pause>null");
			break;
		}

		gotoxy(15, 10);
		cout << "아이디를 입력해주세요. : ";
		cin >> userId;
		gotoxy(15, 12);
		cout << "질문에 대한 답을 하시면 힌트가 제공됩니다.";
		gotoxy(15, 13);
		cout << "태어난 달은? (두글자) :  ";
		cin >> answer;

		if (user->getuserAcc() == userId && user->getPwAnswer()==answer) {
			gotoxy(15, 15);
			cout << user->getUserName() << "님의 비밀번호는 " << user->getuserPw();
			system("pause>null");
			break;
		}

		else {
			gotoxy(20, 15);
			cout << "다시 입력해주세요.";
			gotoxy(18, 16);
			cout << "ESC를 누르면 종료합니다.";

			input = _getch();
			if (input == ESC) break;
			else continue;
		}
	}
}

GUEST selectGuest() {
	int y = 0; //커서의 y 위치
	int input = 0; //키보드 입력을 받을 변수
	while (true) { //게임 루프
		
		//DrawUserCursor 함수
		if (y <= 0) { //커서가 위로 그만 올라가게
			y = 0;
		}
		else if (y >= 2) { //커서가 아래로 그만 내려가게
			y = 2;
		}
		gotoxy(22, 12 + y); //위치조정
		cout << ">";

		input = _getch();
		//→←↑↓ 방향키를 누를 경우
		if (input == MAGIC_KEY) { //224가 들어옴
			//system("cls");
			switch (_getch()) //한번 더 받음

			{
			case UP: //위
				--y;
				break;
			case DOWN: //아래
				++y;
				break;
			}
		}
		//메인 메뉴 고름
		else if (input == SPACE || input == ENTER) { //키보드가 스페이스일 경우
			switch (y) { //y위치에 따라 판단
			case 0:
				return LOGIN_USER;
			case 1:
				return START;
			case 2:
				return QUITGUEST;
			}
		}
	}
}
LOGIN SelectLogin() {
	int y = 0; //커서의 y 위치
	int input = 0; //키보드 입력을 받을 변수
	while (true) { //게임 루프
		DrawLogin(); //준비화면 그리기

		//DrawUserCursor 함수
		if (y <= 0) { //커서가 위로 그만 올라가게
			y = 0;
		}
		else if (y >= 3) { //커서가 아래로 그만 내려가게
			y = 3;
		}
		gotoxy(21, 12 + y); //위치조정
		cout << ">";

		input = _getch();
		//→←↑↓ 방향키를 누를 경우
		if (input == MAGIC_KEY) { //224가 들어옴
			switch (_getch()) //한번 더 받음
			{
			case UP: //위
				--y;
				break;
			case DOWN: //아래
				++y;
				break;
			}
		}
		//메인 메뉴 고름
		else if (input == SPACE || input == ENTER) { //키보드가 스페이스일 경우
			switch (y) { //y위치에 따라 판단
			case 0:
				return FIND;
			case 1:
				return CREATE;
			case 2:
				//system("cls");
				return QUESTION;
			case 3:
				return QUITLOGIN;
			}
		}
	}
}

MENU ReadyGame() {
	int y = 0; //커서의 y 위치
	int input = 0; //키보드 입력을 받을 변수
	while (true) { //게임 루프
		DrawReadyGame(); //준비화면 그리기

		//DrawUserCursor 함수
		if (y <= 0) { //커서가 위로 그만 올라가게
			y = 0;
		}
		else if (y >= 3) { //커서가 아래로 그만 내려가게
			y = 3;
		}

		gotoxy(21, 12 + y); //위치조정
		cout << ">";

		input = _getch();
		//→←↑↓ 방향키를 누를 경우
		if (input == MAGIC_KEY) { //224가 들어옴
			switch (_getch()) //한번 더 받음
			{
			case UP: //위
				--y;
				break;
			case DOWN: //아래
				++y;
				break;
			}
		}
		//메인 메뉴 고름
		else if (input == SPACE || input == ENTER) { //키보드가 스페이스일 경우
			switch (y) { //y위치에 따라 판단
			case 0:
				return GAMESTART;
			case 1:
				return INFO;
			case 2:
				return ACCOUNT;
			case 3:
				system("cls");
				return QUIT;
			}
		}
	}
}

//미니 게임
// 가위바위보
bool RockPaperScissors() {

	string user_select;
	string RPS[] = { "가위","바위","보","가위","바위","보","가위","바위","보","가위","바위","보" };
	string com_select;
	int win_cnt = 0;
	int lose_cnt = 0;

	while (true) {
		gotoxy(23, 3);
		cout << "가위바위보";
		gotoxy(14, 8);
		cout << "가위 바위 보 중에 하나를 골라 입력해주세요.";
		gotoxy(37, 5);
		cout << win_cnt << "승 " << lose_cnt << "패 " ;
		gotoxy(14, 10);
		cout << user_Nickname << " : ";
		cin >> user_select;


		com_select = RPS[rand() % 12]; //컴퓨터는 가위바위보 중 하나를 랜덤으로 가져옴
		gotoxy(14, 12);
		cout << "나쁜 개미 : " << com_select;

		if (user_select == "가위") { //유저가 가위를 골랐을 경우
			if (com_select == "바위") {

				gotoxy(14, 14);
				cout << "졌습니다.";
				lose_cnt++;
			}
			else if (com_select == "보") {
				gotoxy(14, 14);
				cout << "이겼습니다.";
				win_cnt++;
			}
			else if (com_select == "가위") {
				gotoxy(14, 14);
				cout << "비겼습니다.";
			}
		}
		else if (user_select == "바위") { //유저가 바위를 골랐을 경우
			if (com_select == "보") {
				gotoxy(14, 14);
				cout << "졌습니다.";
				lose_cnt++;
			}
			else if (com_select == "가위") {
				gotoxy(14, 14);
				cout << "이겼습니다.";
				win_cnt++;
			}
			else if (com_select == "바위") {
				gotoxy(14, 14);
				cout << "비겼습니다.";
				
			}
		}
		else if (user_select == "보") { //유저가 보를 골랐을 경우
			if (com_select == "가위") {
				gotoxy(14, 14);
				cout << "졌습니다.";
				lose_cnt++;
			}
			else if (com_select == "바위") {
				gotoxy(14, 14);
				cout << "이겼습니다.";
				win_cnt++;
			}
			else if (com_select == "보") {
				gotoxy(14, 14);
				cout << "비겼습니다.";
			}
		}
		else {
			gotoxy(14, 14);
			cout << "잘못 골랐습니다.";
		}

		if (lose_cnt == 2) {
			gotoxy(14, 15);
			cout << "더 이상 집을 짓지 못해요 ㅠㅠ";
			Sleep(2000);
			system("cls");
			DrawGameOver();
			
			houseSize -= rand() % 5 + 1;	
			return false;

		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "집을 지을 수 있어요!";
			Sleep(2000);
			system("cls");
			DrawGamePass();
			houseSize += rand() % 7 + 2;
			system("pause>null");
			return true;
		}
		Sleep(1000);
		system("cls"); //화면 지우기
	}
}

//퀴즈 게임
bool QuizGame() {
	string quiz[] = { "대한민국의 수도는?(두글자) : ", "3 * 3 = ", " 3 * 5 + 9 = ","좋아하는 노래를 적어주세요! : ","2 + 3 * 5 = ",
		"부엉이가 수영할 때 내는 소리는?(세글자) : ","세상에서 가장 가난한 왕은?(네글자) : ","4 / 2 + 6 = ","7 * 8 / 4 = ","깃허브 아이콘의 동물 이름은? (세글자) : ", "좋아하는 전공은 ? : " };
	string answer[] = { "서울","9","24","","17","첨부엉", "최저임금", "8", "14","고양이","" };
	string q, user_answer;
	int i;
	int win_cnt = 0;
	int lose_cnt = 0;

	while (true) {
		gotoxy(23, 3);
		cout << "퀴즈 게임";

		i = rand() % 11;
		q = quiz[i];
		gotoxy(14, 10);
		cout << q;
		cin >> user_answer;

		if (user_answer == answer[i]) {
			gotoxy(22, 12);
			cout << "정답입니다!";
			win_cnt++;
		}
		else {
			if (user_answer== "") { //답이 ""일 경우 무조건 정답처리 
				gotoxy(22, 12);
				cout << "정답입니다!";
				win_cnt++;
			}
			gotoxy(22, 12);
			cout << "틀렸습니다.";
			lose_cnt++;
		}

		if (lose_cnt == 2) {
			gotoxy(14, 15);
			cout << "더 이상 집을 짓지 못해요 ㅠㅠ";
			houseSize -= rand() % 5 + 1;
			system("cls");
			DrawGameOver();
			return false;
		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "집을 지을 수 있어요!";
			houseSize += rand() % 7 + 2;
			system("cls");
			DrawGamePass();
			return true;
		}
		Sleep(1500);
		system("cls"); //화면 지우기
	}
}

//업다운 게임
bool upDownGame() {
	int com_sel = rand() % 50 + 1;
	int user_sel;
	int cnt = 0;
	while (cnt <= 5) {
		gotoxy(21, 3);
		cout << "업다운 게임";
		gotoxy(11, 6);
		cout << "1~50 까지의 수 중에서 개미가 원하는 숫자를 맞춰보세요!";
		gotoxy(11, 7);
		cout << "기회는 총 5번입니다. 과연 개미는 어떤 수를 골랐을까요? : ";

		cin >> user_sel;
		cnt++;
		if (com_sel == user_sel) {
			gotoxy(11, 10);
			cout << "개미가 고른 수는 " << com_sel << "입니다! 축하합니다~" << endl;
			houseSize += rand() % 7 + 2;
			DrawGamePass();
			return true;
		}
		if (cnt == 5) {
			system("cls");
			gotoxy(10, 10);
			cout << "개미가 고른 수는 " << com_sel << "입니다. 집을 지을 수 없어요ㅠㅠ";
			Sleep(1500);
			system("cls");
			DrawGameOver();
			houseSize -= rand() % 5 + 1;
			return false;
		}

		else if (com_sel > user_sel) {
			gotoxy(11, 10);
			cout << "개미는 더 큰 수를 골랐습니다!";
			gotoxy(11, 11);
			cout << "남은 기회는 " << 5 - cnt << "번 입니다!";
		}
		else if (com_sel < user_sel) {
			gotoxy(11, 10);
			cout << "개미는 더 작은 수를 골랐습니다!";
			gotoxy(11, 11);
			cout << "남은 기회는 " << 5 - cnt << "번 입니다!";
		}
		Sleep(1500);
		system("cls"); //화면 지우기
	}
}

//타이밍 맞추기 게임(보너스 게임) - 무조건 집이 커짐
void timingGame() {
	timeBeginPeriod(1); //timer interrupt 해상도를 1로 맞춤
	char pointList[4][256] = { // 점수 리스트
		{"Bad"},
		{"NoGood"},
		{"Good"},
		{"Grea"},
	};

	int g_timing[] = { 5, 10, 14, 17, 20, 25, 29, 34, 37 }; // 타이밍

	char userPoint[9][256] = { {" "} }; // 유저의 점수 기록하는 배열

	double begin; // 처음 시작시 시간
	double end; // 프로그램 실행 후 반복문안에서 체크할 시간
	double checkC; // begin - end 값
	int tIndex = 0; // 스테이지 체크
	begin = timeGetTime();

	cout << fixed; // 출력 소수점 자리수 고정
	cout.precision(3); // 소수점 밑 3자리까지 출력

	while (1) {

		end = timeGetTime();
		checkC = (end - begin) / 1000; // 경과시간 구하기

		cout << "타이머 : " << checkC << endl;
		cout << endl;

		if (_kbhit()) {
			// fabs는 double의 절대값 구하는 함수입니다.
			if (fabs((double)g_timing[tIndex] - checkC) >= (double)1) { // 유저 입력 시간이 1초이상 차이날 경우 
				strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			}
			// 0.75이하로 차이나고 0.5초 초과로 차이날경우
			else if (fabs((double)g_timing[tIndex] - checkC) <= (double)0.75 && fabs((double)g_timing[tIndex] - checkC) > (double)0.5) {
				strcpy_s(userPoint[tIndex], strlen(pointList[1]) + 1, pointList[1]);
			}
			// 0.5이하로 차이나고 0.25초 초과로 차이날경우
			else if (fabs((double)g_timing[tIndex] - checkC) <= (double)0.5 && fabs((double)g_timing[tIndex] - checkC) > (double)0.25) {
				strcpy_s(userPoint[tIndex], strlen(pointList[2]) + 1, pointList[2]);
			}
			// 0.25 이하로 차이날 경우
			else if (fabs((double)g_timing[tIndex] - checkC) <= (double)0.25) {
				strcpy_s(userPoint[tIndex], strlen(pointList[3]) + 1, pointList[3]);
			}

			_getch(); // 버퍼 비우기
			tIndex++; // 스테이지 상승
		}

		// 유저가 입력하지 않았을 경우 자동으로 Bad값을 저장
		if (checkC > 6 && tIndex == 0) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
		}
		else if (checkC > 11 && tIndex == 1) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
		}
		else if (checkC > 15 && tIndex == 2) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
		}
		else if (checkC > 18 && tIndex == 3) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
		}
		else if (checkC > 21 && tIndex == 4) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
		}
		else if (checkC > (double)26 && tIndex == 5) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
		}
		else if (checkC > (double)30 && tIndex == 6) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
		}
		else if (checkC > (double)35 && tIndex == 7) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
		}
		else if (checkC > (double)38 && tIndex == 8) {
			strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			tIndex++;
			break;
		}

		for (int i = 0; i < 9; i++) { // 현재 스테이지와 유저의 점수를 출력
			cout << g_timing[i] << " Sec : " << userPoint[i] << endl;
		}

		if (tIndex == 9) // 스테이지가 8이 지났을 경우 종료
			break;
		system("cls"); // 콘솔 지우기
	}
	timeEndPeriod(1); // timer interrupt 초기화
}

//게임 정보 뷰
void InfoGame() {
	DrawFirstInfoGame();
	DrawSecondeInfoGame();
	system("pause>null");
}

//게임 시작 뷰
void startGame() {
	if (houseSize == 20) {
		DrawStartMiniGame();
		system("pause>null");
		system("cls");
		if (user_Nickname.empty()) DrawStartGame();

		system("cls");
		if (RockPaperScissors()) {
			system("cls");
			a1.drawAntHouse(houseSize);
			a1.moveInHouse();
		}
		else {
			system("cls");
			a1.drawAntHouse(houseSize);
			a1.moveInHouse();
		}
	}
}

void readyStart() { //게임 시작 전 로그인 체크, 하우스 사이즈, 게스트 로그인 여부 묻기
	system("cls");
	if (!(user->getLoginCheck())) { //로그인이 안되어 있으면 게스트 로그인 여부 물음
		checkReady();
	}
	else { //로그인 되어 있으면 바로 게임 하는데 이름이 없으면 이름 입력 부분부터 / 디비 연동하면 처음말곤 실행될 일 없음
		if (user_Nickname.empty()) DrawStartGame();
		system("cls");
	}
}

int checkReady() {
	switch (checkGuest()) {
	case 0: return 0;
	case 1: startGame();
	case 2: LoginAccount();
	}
}

void CreateAccount() {//계정 생성
	system("cls");
	string acc;
	string pw;
	string idAnswer, pwAnswer;
	string name;
	gotoxy(12, 8);
	cout << "생성할 계정의 계정명 입력 : ";
	cin >> acc;
	user->setUserAcc(acc); //계정명 저장
	gotoxy(12, 10);
	cout << "생성할 계정의 비밀번호 입력 : ";
	cin >> pw;
	user->setUserPw(pw);
	gotoxy(12, 12);
	cout << "이름 입력 : ";
	cin >> name;
	user->setUserName(name);

	gotoxy(12,14);
	cout << "계정을 잃어버렸을 경우를 대비해, 질문에 대답해주세요. ";
	gotoxy(12, 15);
	cout << "가장 좋아하는 전공은? : ";
	cin >> idAnswer;
	user->setIdAnswer(idAnswer);

	gotoxy(12, 17);
	cout << "태어날 달은? (두글자) : ";
	cin >> pwAnswer;
	user->setPwAnswer(pwAnswer);

	system("cls");
	gotoxy(18, 12);
	cout << "계정이 생성되었습니다.";
	gotoxy(16, 14);
	cout << plz_space;
	system("pause>null");
} 

bool LoginAccount() {//생성한 계정 확인, 로그인하기
	system("cls");
	string acc;
	string pw;
	gotoxy(15, 8);
	cout << "계정 입력 : ";
	cin >> acc;
	gotoxy(15, 10);
	cout << "비밀번호 입력 : ";
	cin >> pw;
	return user->checkUser(acc, pw);
} 

int QuestionAccount() { //계정 찾는 거 질문
	//아이디 찾기, 비밀번호 찾기, 로그인하기, 회원가입하기
	int y = 0; //커서의 y 위치
	int x = 0;
	int input = 0; //키보드 입력을 받을 변수
	while (true) { //게임 루프
		DrawFIndAcc(); //준비화면 그리기
			
		if (y <= 0) { //커서가 위로 그만 올라가게
			y = 0;
		}
		else if (y >= 2) { //커서가 아래로 그만 내려가게
			y = 2;
		}
		if (x <= 0) { //커서가 왼쪽으로 그만가게
			x = 0;
		}
		else if (x >= 12) { //커서가 오른쪽으로 그만가게
			x = 12;
		}
		gotoxy(14+x, 13 + y); //위치조정
		cout << ">";

		input = _getch();
		//→←↑↓ 방향키를 누를 경우
		if (input == MAGIC_KEY) { //224가 들어옴
			switch (_getch()) //한번 더 받음
			{
			case UP: //위
				y-=2;
				break;
			case DOWN: //아래
				y+=2;
				break;
			case LEFT:
				x-=12;
				break;
			case RIGHT:
				x+=12;
				break;
			}
		}
		//메인 메뉴 고름
		else if (input == SPACE || input == ENTER) { //키보드가 스페이스일 경우
			switch (y+x) { //y위치에 따라 판단
			case 0:
				DrawFindId();
				break;
			case 2:
				LoginAccount();
				break;
			case 12:
				//system("cls");
				DrawFindPw();
				break;
			case 14:
				return 0;
			}
		}
	}
}

//로그인 뷰
int userLogin() {
	DrawLogin();
	while (true) {
		switch (SelectLogin()) { //리턴을 받아 판단
		case FIND:
			if (LoginAccount()) {
				ReadyGame();
				break;
			}
			break;
		case CREATE:
			CreateAccount();
			ReadyGame();
			break;
		case QUESTION:
			QuestionAccount();
			ReadyGame();
			break;
		case QUITLOGIN :
			return 0;

		}
	}
}

//메인 루프
int main() {
	srand((unsigned int)time(NULL));

	SetConsoleVIew(); //프로그램 시작할 때 콘솔 크기
	while (true) {
		switch (ReadyGame()) { //리턴을 받아 판단
		case GAMESTART:
			readyStart();
			break;
		case INFO:
			InfoGame();
			break;
		case ACCOUNT:
			userLogin();
			break;
		case QUIT:
			delete user;
			return 0;
		}
	}
	return 0;
}