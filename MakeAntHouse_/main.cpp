#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h> //커서 이동
#include<conio.h> //_getch()
#include<stdbool.h> //boolean 타입 사용
#include<time.h> //랜덤 함수 사용
#include<string>
//#include<mysql.h> //mysql 관련 함수 사용

using namespace std;
#define MAGIC_KEY 224 //상하좌우 화살표가 들어올 때 선행되어 들어오는 숫자
#define SPACE 32 //스페이스 키 값
#define ENTER 13 //엔터 키 값
#define ESC 27 //esc 키 값

string user_name = ""; //사용자 이름
string plz_space = "[스페이스나 엔터를 눌러주세요.]";
int r; //개미집 크기


enum LOGIN {
	CREATE,
	FIND,
	DELETE_ACCOUNT,
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

void DrawReadyGame();
void DrawInfoGame();
void DrawStartGame();
void DrawGameOver();
void DrawLogin();
void DrawUserCursor(int& y);
LOGIN selectGuest();
LOGIN SelectLogin();
MENU ReadyGame();

bool QuizGame();
bool upDownGame();

void InfoGame();
void startGame();

void CreateAccount();
void LoginAccount();
void DeleteAccount();
void QuestionAccount();

int userLogin()

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

class Login { //유저가 로그인 시 계정 저장 및 계정 생성 시 정보 저장
	string user_account;
	int user_id;
	string user_password;
public:

	Login() {
		this->user_id = (rand() % 100000); //랜덤 아이디 제공
	}
	Login(string account, string password) {
		this->user_account = account;
		this->user_password = password;
		this->user_id = (rand() % 100000);
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
	void checkUser(string acc, string pw) { //사용자가 입력한 계정이 있는 계정인지 체크
		if (getuserAcc() == acc && getuserPw() == pw) cout << "로그인 성공" << endl;
		else if (getuserAcc() == acc && getuserPw() != pw) cout << "비밀번호를 확인하세요" << endl;
		else if (getuserAcc() != acc) cout << "존재하지 않는 계정" << endl;
		else cout << "정신차리세요" << endl;
	}
	void checkGuest() { //게스트로 로그인 할건지 물음
		system("cls");
		gotoxy(17,10);
		cout << "게스트로 로그인 하시겠습니까?";
		gotoxy(13, 11);
		cout << "게스트로 로그인 시 게임 종료 후 저장되지 않습니다.";
		gotoxy(23, 12);
		cout << "로 그 인";
		gotoxy(23, 13);
		cout << "게임시작";
		while (true) {
			switch (selectGuest()) { //리턴을 받아 판단
			case FIND:
				LoginAccount();
				break;
			case CREATE:
				startGame();
				break;
			}
		}
	}
	virtual ~Login() {}
};




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
	cout << "게임 시작";
	gotoxy(22, 13);
	cout << "게임 설명";
	gotoxy(22, 14);
	cout << "로 그 인" << endl;
	gotoxy(22, 15);
	cout << "나 가 기" << endl;

	gotoxy(17, 19);
	cout << plz_space;
}

//게임 설명 그리기
void DrawInfoGame()
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
}


//시작 화면 그리기
//디비 연동 후 계정이 없는 처음에만 실행
void DrawStartGame() {
	if (user_name == "") {
		system("cls");
		gotoxy(14, 9);
		cout << "개미들이 다리를 다쳐 집을 짓지 못하고 있어요!";
		gotoxy(15, 10);
		cout << "당신이 개미들의 집을 만들어주면 좋겠어요.";
		gotoxy(13, 11);
		cout << "개미들에게 당신의 이름을 알려주면 보답을 할거예요.";
		gotoxy(15, 12);
		cout << " 당신의 이름이 무엇인가요? : ";
		cin >> user_name;
	}
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
//로그인 화면 그리기
void DrawLogin() {

	system("cls");    //화면을 클리어 해주는 함수

	gotoxy(22, 12);
	cout << "로 그 인";
	gotoxy(22, 13);
	cout << "회원 가입";
	gotoxy(22, 14);
	cout << "계정 찾기" << endl;
	gotoxy(22, 15);
	cout << "나 가 기" << endl;

	gotoxy(18, 19);
	cout << plz_space;
}



//커서 움직임 출력
void DrawUserCursor(int& y)
{
	if (y <= 0)        //커서가 위로 그만 올라가게 
	{
		y = 0;
	}
	else if (y >= 2) //커서가 아래로 그만 내려가게
	{
		y = 2;
	}

	gotoxy(9, 8 + y); //위치조정
	cout << ">";
}
LOGIN selectGuest() {
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
		gotoxy(22, 13 + y); //위치조정
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
				return DELETE_ACCOUNT;
			case 3:
				//system("cls");
				return QUESTION;
			case 4:
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
//메인 게임
//user는 개미, 이벤트가 발생할 때마다 집을 지키거나 늘리거나 부숴질 수 있음
//이벤트 : 미니게임 이벤트(랜덤으로 발생)




//개미집 그리기
void antHouse(int r) {
	system("cls");
	//기본 집 그리기
	gotoxy(1, 3);
	cout << "집의 크기 : " << r << endl;


	//집이 일정 크기 이상이면 반으로 나누고 집을 여러개 연결되게 만듦

	gotoxy(10, 6);
	for (int i = 1; i <= r; i++) {
		for (int j = 1; j <= r / 2 - 1; j++) {
			/*if (!(i>2 && i<r-1)) {
				gotoxy(i + 9, j + 6);
				cout << "*";
			}
			else cout << " "; */
			cout << "*";
		}

		cout << endl;
	}

	system("pause>null");
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
		cout << user_name << " : ";
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
			Sleep(1500); //1.5초를 기다림
		}

		if (lose_cnt == 2) {
			gotoxy(14, 15);
			cout << "더 이상 집을 짓지 못해요 ㅠㅠ";
			Sleep(2000);
			system("cls");
			DrawGameOver();
			if (r < 2 || rand() % 10 % 3 == 0) {//졌을 경우 3의 배수의 경우에만 집이 커짐
				int tmp = rand() % 5 + 1;
				r += tmp;
			}

			else {//졌을 경우에는 집이  작아짐
				int tmp = rand() % 4 + 1;
				r -= tmp;
			}
			antHouse(r);
			return false;

		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "집을 지을 수 있어요!";
			Sleep(2000);
			system("cls");
			r += rand() % 7 + 2;
			antHouse(r);
			return true;
		}

		Sleep(1500);
		system("cls"); //화면 지우기

	}
}

//퀴즈 게임
bool QuizGame() {
	string quiz[] = { "대한민국의 수도는?(두글자) : ", "3 * 3 = ", " 3 * 5 + 9 = ","좋아하는 노래를 적어주세요! : ","2 + 3 * 5 = ",
		"부엉이가 수영할 때 내는 소리는?(세글자) : ","세상에서 가장 가난한 왕은?(네글자) : ","4 / 2 + 6 = " };
	string answer[] = { "서울","9","24","","17","첨부엉", "최저임금", "8" };
	string q, user_answer;
	int i;
	int win_cnt = 0;
	int lose_cnt = 0;


	while (true) {
		gotoxy(23, 3);
		cout << "퀴즈 게임";

		i = rand() % 9;
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
			if (i == 3 && user_answer != "") {
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
			if (r < 2 || rand() % 10 % 3 == 0) {//졌을 경우 3의 배수의 경우에만 집이 커짐
				int tmp = rand() % 5 + 1;
				r += tmp;
			}

			else {//졌을 경우에는 집이  작아짐
				int tmp = rand() % 4 + 1;
				r -= tmp;
			}
			antHouse(r);
			return false;
		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "집을 지을 수 있어요!";
			r += rand() % 7 + 2;
			antHouse(r);
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
	int cnt = 1;
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
			r += rand() % 7 + 2;
			antHouse(r);
			return true;
		}
		if (cnt == 5) {
			system("cls");
			gotoxy(10, 10);
			cout << "개미가 고른 수는 " << com_sel << "입니다. 집을 지을 수 없어요ㅠㅠ";
			Sleep(1500);
			system("cls");
			DrawGameOver();
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


//게임 정보 뷰
void InfoGame() {
	DrawInfoGame();
	system("pause>null");
}

//게임 시작 뷰
void startGame() {
	//게임 시작을 누르는데 만약 로그인이 안되어 있으면 게스트 로그인이냐고 묻기 -> 디비 연동 안됨
	//게스트 아니라 그러면 로그인 화면 띄우기 -> 계정 없으면 회원가입 ㄲ -> 게임 설명 하고 바로 이름 입력 후 미니 게임부터..
	//로그인 성공하면 지금까지 만든 집 보여즈기 -> 0이면 게임 ㄱ

	
	/*DrawStartGame();
	system("cls");

	upDownGame();
	system("cls");
	RockPaperScissors();
	system("cls");
	QuizGame();*/
	Login user;
	user.checkGuest();
	system("pause>null");
}


Login user;
void CreateAccount() {//계정 생성
	system("cls");

	string acc;
	string pw;
	gotoxy(10, 8);
	cout << "생성할 계정의 계정명 입력 : ";
	cin >> acc;
	user.setUserAcc(acc); //계정명 저장
	gotoxy(10, 10);
	cout << "생성할 계정의 비밀번호 입력 : ";
	cin >> pw;
	user.setUserPw(pw);
	gotoxy(14, 10);
	cout << "계정이 생성되었습니다.";
} 
void LoginAccount() {//생성한 계정 확인, 로그인하기
	system("cls");
	string acc;
	string pw;
	cout << "계정 입력 : ";
	cin >> acc;
	cout << endl;
	cout << "비밀번호 입력 : ";
	cin >> pw;
	user.checkUser(acc, pw);
} 
void DeleteAccount() {//계정 삭제

} 
void QuestionAccount() { //계정 찾는 거 질문

}

//로그인 뷰
int userLogin() {

	DrawLogin();
	while (true) {
		switch (SelectLogin()) { //리턴을 받아 판단
		case FIND:
			LoginAccount();
			break;
		case CREATE:
			CreateAccount();
			userLogin();
			break;
		case DELETE_ACCOUNT:
			DeleteAccount();
			break;
		case QUESTION:
			QuestionAccount();
			break;
		case QUITLOGIN :
			startGame();
			break;
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
			startGame();
			break;
		case INFO:
			InfoGame();
			break;
		case ACCOUNT:
			userLogin();
			break;
		case QUIT:
			cout << user_name + "님이 지어주신 집은 " << r << "의 크기입니다! 감사합니다";
			return 0;
		}
	}
	return 0;
}