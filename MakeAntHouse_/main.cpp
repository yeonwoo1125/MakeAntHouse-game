#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h> //Ŀ�� �̵�
#include<conio.h> //_getch()
#include<stdbool.h> //boolean Ÿ�� ���
#include<time.h> //���� �Լ� ���
#include<string>
//#include<mysql.h> //mysql ���� �Լ� ���
#pragma comment(lib, "winmm.lib") // timeGetTime() �Լ� ����� ���� ���̺귯��

using namespace std;
#define MAGIC_KEY 224 //�����¿� ȭ��ǥ�� ���� �� ����Ǿ� ������ ����
#define SPACE 32 //�����̽� Ű ��
#define ENTER 13 //���� Ű ��
#define ESC 27 //esc Ű ��

string user_name; //����� �̸�
string plz_space = "[�����̽��� ���͸� �����ּ���.]";
int houseSize = 10; //������ ũ��

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

//ȭ�� �׸��� �Լ�
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

//�޴� ����
GUEST selectGuest();
LOGIN SelectLogin();
MENU ReadyGame();


//�̴ϰ���
bool RockPaperScissors();
bool QuizGame();
bool upDownGame();
void timingGame();

//��
void InfoGame();
void startGame();
int userLogin();
int readyStart();


//�α��� ����
void CreateAccount();
bool LoginAccount();
int QuestionAccount();

void gotoxy(int x, int y) { //Ŀ���� Ư�� ��ġ�� �̵���Ű�� �Լ�
	COORD Pos;
	Pos.X = 2 * x; //1ĭ���ٴ� 2ĭ�� �������� �ڿ�������
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//�ܼ� ũ��, Ÿ��Ʋ
void SetConsoleVIew() {
	system("mode con:cols=100 lines=30"); //���� 50, ���� 20
	system("title Make Ant House By Yeonwoo"); //Ÿ��Ʋ
}

class ant { //���������� ������ ���� ��ü
private :
	int ant_x, ant_y;
	int input = 0;
	char feed = '*';
	int feed_x;
	int feed_y;
	int feedCnt = 3; //�⺻������ ���� 3�� ����
public:
	ant() : ant_x(0), ant_y(0),feed_x(0),feed_y(0){} //������ ���� ��ġ�� �� ������ ���ؾ���
	int getFeedCnt() { //���� �������� ������ ������ ��
		return feedCnt;
	}
	void ranFeed() {
		feed_x = rand() % ant_x; //������ ���ο� ���� ���� - >������ ���μ��κ��� ���� ����
		feed_y = rand() % ant_y;

		for (int i = 0; i < feedCnt; i++) {
			gotoxy(feed_x, feed_y);
			cout << feed;
			Sleep(5000); //5�ʸ��� ���� ����
			feedCnt++;
		}
	}

	void moveInHouse() { //������ �ȿ��� ������
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
	void collisonCheck() { //���̰� ������ ���� ���� ���
		//���� ���� �ΰ� �̻��̸� ���� ���� ��� �ش� ���⿡ �ִ� ������ �̵�
		//���� ���ٸ� �׳� ���̻� ������ ��������
		
	}
	void eatFeed() { //���̰� ���̸� ���� ��� - ���̸� ����� �̴ϰ��� ���� 
		//���� �� ����, ������ ��ǥ�� ����(*) ����
		//��ǥ�� ��ĥ ���, �̴ϰ��� ����
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
				cout << "���ʽ� ����";
				cout << "��� ������ŭ ���� Ŀ���ϴ�.";
				timingGame();
				break;
			}
		}
	}
	void drawAntHouse(int r) {
		//system("cls");
		//�⺻ �� �׸���
		gotoxy(1, 3);
		cout << "���� ũ�� : " << r << endl;

		//���� ���� ũ�� �̻��̸� ������ ������ ���� ������ ����ǰ� ����

		//gotoxy(10, 6);
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
		ranFeed();
		moveInHouse();
		eatFeed();
	}
		//system("pause>null");
	~ant() {}
};

ant a1;
class Login { //������ �α��� �� ���� ���� �� ���� ���� �� ���� ����
	string user_account;
	int user_id;
	string user_password;
	bool loginCheck = false; //�α��� ���� ���� �ľ�
	string idHint;
	string pwHint;
public:
	Login() {
		this->user_id = (rand() % 100000); //���� ���̵� ����
	}
	void setIdHint(string idHint) {
		this->idHint = idHint;
	}
	string getIdHint() {
		return idHint;
	}
	void setPwHint(string pwHint) {
		this->pwHint = pwHint;
	}
	string getPwHint() {
		return pwHint;
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

	bool checkUser(string acc, string pw) { //����ڰ� �Է��� ������ �ִ� �������� üũ
		int input=0;
		if (getuserAcc() == acc && getuserPw() == pw) {
			loginCheck = true;
			system("cls");
			gotoxy(21, 12);
			cout << "�α��� ����" ;
			gotoxy(16, 15);
			cout << plz_space;
			system("pause>null");
			return true;   
		}
			else if (getuserPw() != pw || getuserAcc() != acc) {
				system("cls");
				gotoxy(21, 9);
				cout << "�α��� ����" << endl;
				gotoxy(14, 11);
				cout << "�ٽ� �õ��Ͻ÷��� �����̽��� �����ּ���." << endl;
				gotoxy(14, 12);
				cout << "�����̽��� ������ �α����� ��õ��մϴ�." << endl;
				gotoxy(17, 13);
				cout << "�����÷��� ESC�� �����ּ���.";
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
						cout << "���� �Է� : ";
						cin >> acc;
						gotoxy(16, 10);
						cout << "��й�ȣ �Է� : ";
						cin >> pw;
						checkUser(acc, pw);
					}
				}
				return false;
			}
	}
	~Login() {}
};

bool checkGuest() { //�Խ�Ʈ�� �α��� �Ұ��� ����
	DrawGuestLogin();
	while (true) {
		switch (selectGuest()) { //������ �޾� �Ǵ�
		case LOGIN_USER:
			LoginAccount();
			break;
		case START:
			system("cls");
			startGame();
			break;
		case QUITGUEST:
			return 0;
		}
	}
}


//���� �޴� �׸���
void DrawReadyGame() {
	system("cls");    //ȭ���� Ŭ���� ���ִ� �Լ� �Դϴ�.
	gotoxy(15, 4);
	cout << "**************************************";
	gotoxy(15, 5);
	cout << "*                                    *";
	gotoxy(15, 6);
	cout << "*              ��������              *";
	gotoxy(15, 7);
	cout << "*        �������� ���������         *";
	gotoxy(15, 8);
	cout << "*                                    *";
	gotoxy(15, 9);
	cout << "**************************************";
	gotoxy(22, 12);
	cout << "���ӽ���";
	gotoxy(22, 13);
	cout << "���Ӽ���";
	gotoxy(22, 14);
	cout << "�� �� ��" << endl;
	gotoxy(22, 15);
	cout << "�� �� ��" << endl;

	gotoxy(17, 19);
	cout << plz_space;
}

//���� ���� �׸���
void DrawFirstInfoGame()
{
	system("cls");
	gotoxy(3, 3);
	cout << "****************";
	gotoxy(3, 4);
	cout << "*   ���Ӽ���   *";
	gotoxy(3, 5);
	cout << "****************";

	gotoxy(3, 8);
	cout << "���̵��� �ٸ��� ���ļ� ���� ���� ���ϰ� �־��!";
	gotoxy(3, 9);
	cout << "����� ���̵��� �� ����� �� ���������� ���ھ��..";
	gotoxy(3, 10);
	cout << "���� ����� ����� �����ؿ�!";
	gotoxy(3, 12);
	cout << "1) ���ϴ� ���� ������ ����ּ���.";
	gotoxy(3, 13);
	cout << "2) ���� ����� ���� ������ ������ ���ּ���.";
	gotoxy(3, 14);
	cout << "3) ���ӿ��� �̱�� ����ؼ� ���� ���� �� ������,";
	gotoxy(3, 15);
	cout << "   ���� ���ٸ� �� �̻� ���� ���� ���ؿ�.";
	gotoxy(3, 19);
	cout << "�׷� �� ��Ź�ؿ�!!";
	gotoxy(38, 22);
	cout << "���� ������";
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
	cout << "*   ��������   *";
	gotoxy(3, 5);
	cout << "****************";

	gotoxy(3, 8);
	cout << "������ ó�� �����Ͻô� ���� ȸ�������� ���ּ���.(�α���->ȸ������)";
	gotoxy(3, 9);
	cout << "�̹� ������ �����Ѵٸ� �α����� �� �� ������ �����ϸ� �˴ϴ�.";
	gotoxy(3, 10);
	cout << "������ �Ҿ������ ���, ���� ã�⸦ ���� ������ ã���ּ���.(�α���->���� ã��)";
	gotoxy(3, 11);
	cout << "�α��� ���� ������ �ϰ� �ʹٸ� �Խ�Ʈ �α����� ���� ������ ����ּ���.";
	gotoxy(3, 13);
	cout << "���� ó�� ������ �����ϸ�, �̴ϰ����� ���� �⺻ ũ���� �������� ��� �˴ϴ�.";
	gotoxy(3, 14);
	cout << "�������� �����Ǵ� ������ ���̸� ������ �̴ϰ����� �� �� �ֽ��ϴ�. ";
	gotoxy(3, 15);
	cout << "������ ���� �ð� ���̸� ���� ������ ���̰� ���� ���� ������ �����ϼ���.";
	gotoxy(3, 19);
	cout << "�׷� ��ſ� �ð� �Ǽ���!";
	gotoxy(16, 22);
	cout << plz_space;
}


//���� ȭ�� �׸���
//��� ���� �� ������ ���� ó������ ����
void DrawStartGame() {
	if (user_name == "") {
		system("cls");
		gotoxy(14, 9);
		cout << "���̵��� �ٸ��� ���� ���� ���� ���ϰ� �־��!";
		gotoxy(15, 10);
		cout << "����� ���̵��� ���� ������ָ� ���ھ��.";
		gotoxy(13, 11);
		cout << "���̵鿡�� ����� �̸��� �˷��ָ� ������ �Ұſ���.";
		gotoxy(15, 12);
		cout << " ����� �̸��� �����ΰ���? : ";
		cin >> user_name;
	}
}
//���� �״� ��� - ���� ���� �׸���
void DrawDieAnt() { //�������� 0���� �۾����� ���, ���̸� ���� �ʾ��� ���
	if (a1.getFeedCnt() > 9) {
		gotoxy(18, 10);
		cout << user_name << "���� ���̰� �����׾����ϴ�.";
		gotoxy(18, 11);
		cout << user_name << "���� ���� ũ��� "<<houseSize<<"�Դϴ�.";
		gotoxy(18, 14);
		DrawGameOver();
	}
	else if (houseSize <= 0) {
		gotoxy(18, 10);
		cout << user_name << "���� ���� �ν��� ���̰� �̻縦 �����ϴ�.";
		gotoxy(18, 12);
		DrawGameOver();
	}
}

//�̴ϰ��� ���� ȭ�� �׸���
void DrawStartMiniGame() {
	system("cls");
	gotoxy(15, 8);
	cout << "--------------------------";
	gotoxy(15, 9);
	cout << "|   ���� ���� �����Ƿ�   |";
	gotoxy(15, 10);
	cout << "|  �̴ϰ����� �����մϴ� |";
	gotoxy(15, 11);
	cout << "--------------------------";
	gotoxy(14, 14);
	cout << plz_space;
	system("pause>null");
}

//���� ���� �׸���
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
//���� ��� �׸���
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
//�α��� ȭ�� �׸���
void DrawLogin() {

	system("cls");    //ȭ���� Ŭ���� ���ִ� �Լ�

	gotoxy(22, 12);
	cout << "�� �� ��";
	gotoxy(22, 13);
	cout << "ȸ������";
	gotoxy(22, 14);
	cout << "����ã��";
	gotoxy(22, 15);
	cout << "�� �� ��";

	gotoxy(17, 19);
	cout << plz_space;
}

//�Խ�Ʈ �α��� ȭ�� �׸���
void DrawGuestLogin() {
	system("cls");
	gotoxy(17, 8);
	cout << "�Խ�Ʈ�� �α��� �Ͻðڽ��ϱ�?";
	gotoxy(13, 9);
	cout << "�Խ�Ʈ�� �α��� �� ���� ���� �� ������� �ʽ��ϴ�.";
	gotoxy(23, 12);
	cout << "�� �� ��";
	gotoxy(23, 13);
	cout << "���ӽ���";
	gotoxy(23, 14);
	cout << "�� �� ��";

	gotoxy(18, 17);
	cout << plz_space;
}
//����ã�� ȭ�� �׸���
void DrawFIndAcc() {
	system("cls");
	gotoxy(15, 13);
	cout << "���� ã��";
	gotoxy(27, 13);
	cout << "��й�ȣ ã��";
	gotoxy(15, 15);
	cout << "�α��� �ϱ�";
	gotoxy(27, 15);
	cout << "�������� ����";
}
//���̵� ã�� ȭ�� �׸���
void DrawFindId() {}

//��й�ȣ ã�� ȭ�� �׸���
void DrawFindPw() {}

GUEST selectGuest() {
	int y = 0; //Ŀ���� y ��ġ
	int input = 0; //Ű���� �Է��� ���� ����
	while (true) { //���� ����
		
		//DrawUserCursor �Լ�
		if (y <= 0) { //Ŀ���� ���� �׸� �ö󰡰�
			y = 0;
		}
		else if (y >= 2) { //Ŀ���� �Ʒ��� �׸� ��������
			y = 2;
		}
		gotoxy(22, 12 + y); //��ġ����
		cout << ">";

		input = _getch();
		//����� ����Ű�� ���� ���
		if (input == MAGIC_KEY) { //224�� ����
			//system("cls");
			switch (_getch()) //�ѹ� �� ����

			{
			case UP: //��
				--y;
				break;
			case DOWN: //�Ʒ�
				++y;
				break;
			}
		}
		//���� �޴� ��
		else if (input == SPACE || input == ENTER) { //Ű���尡 �����̽��� ���
			switch (y) { //y��ġ�� ���� �Ǵ�
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
	int y = 0; //Ŀ���� y ��ġ
	int input = 0; //Ű���� �Է��� ���� ����
	while (true) { //���� ����
		DrawLogin(); //�غ�ȭ�� �׸���

		//DrawUserCursor �Լ�
		if (y <= 0) { //Ŀ���� ���� �׸� �ö󰡰�
			y = 0;
		}
		else if (y >= 3) { //Ŀ���� �Ʒ��� �׸� ��������
			y = 3;
		}
		gotoxy(21, 12 + y); //��ġ����
		cout << ">";

		input = _getch();
		//����� ����Ű�� ���� ���
		if (input == MAGIC_KEY) { //224�� ����
			switch (_getch()) //�ѹ� �� ����
			{
			case UP: //��
				--y;
				break;
			case DOWN: //�Ʒ�
				++y;
				break;
			}
		}
		//���� �޴� ��
		else if (input == SPACE || input == ENTER) { //Ű���尡 �����̽��� ���
			switch (y) { //y��ġ�� ���� �Ǵ�
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
	int y = 0; //Ŀ���� y ��ġ
	int input = 0; //Ű���� �Է��� ���� ����
	while (true) { //���� ����
		DrawReadyGame(); //�غ�ȭ�� �׸���

		//DrawUserCursor �Լ�
		if (y <= 0) { //Ŀ���� ���� �׸� �ö󰡰�
			y = 0;
		}
		else if (y >= 3) { //Ŀ���� �Ʒ��� �׸� ��������
			y = 3;
		}

		gotoxy(21, 12 + y); //��ġ����
		cout << ">";

		input = _getch();
		//����� ����Ű�� ���� ���
		if (input == MAGIC_KEY) { //224�� ����
			switch (_getch()) //�ѹ� �� ����
			{
			case UP: //��
				--y;
				break;
			case DOWN: //�Ʒ�
				++y;
				break;
			}
		}
		//���� �޴� ��
		else if (input == SPACE || input == ENTER) { //Ű���尡 �����̽��� ���
			switch (y) { //y��ġ�� ���� �Ǵ�
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

//�̴� ����
// ����������
bool RockPaperScissors() {

	string user_select;
	string RPS[] = { "����","����","��","����","����","��","����","����","��","����","����","��" };
	string com_select;
	int win_cnt = 0;
	int lose_cnt = 0;

	while (true) {
		gotoxy(23, 3);
		cout << "����������";
		gotoxy(14, 8);
		cout << "���� ���� �� �߿� �ϳ��� ��� �Է����ּ���.";
		gotoxy(37, 5);
		cout << win_cnt << "�� " << lose_cnt << "�� " ;
		gotoxy(14, 10);
		cout << user_name << " : ";
		cin >> user_select;


		com_select = RPS[rand() % 12]; //��ǻ�ʹ� ���������� �� �ϳ��� �������� ������
		gotoxy(14, 12);
		cout << "���� ���� : " << com_select;

		if (user_select == "����") { //������ ������ ����� ���
			if (com_select == "����") {

				gotoxy(14, 14);
				cout << "�����ϴ�.";
				lose_cnt++;
			}
			else if (com_select == "��") {
				gotoxy(14, 14);
				cout << "�̰���ϴ�.";
				win_cnt++;
			}
			else if (com_select == "����") {
				gotoxy(14, 14);
				cout << "�����ϴ�.";
			}
		}
		else if (user_select == "����") { //������ ������ ����� ���
			if (com_select == "��") {
				gotoxy(14, 14);
				cout << "�����ϴ�.";
				lose_cnt++;
			}
			else if (com_select == "����") {
				gotoxy(14, 14);
				cout << "�̰���ϴ�.";
				win_cnt++;
			}
			else if (com_select == "����") {
				gotoxy(14, 14);
				cout << "�����ϴ�.";
				
			}
		}
		else if (user_select == "��") { //������ ���� ����� ���
			if (com_select == "����") {
				gotoxy(14, 14);
				cout << "�����ϴ�.";
				lose_cnt++;
			}
			else if (com_select == "����") {
				gotoxy(14, 14);
				cout << "�̰���ϴ�.";
				win_cnt++;
			}
			else if (com_select == "��") {
				gotoxy(14, 14);
				cout << "�����ϴ�.";
			}
		}
		else {
			gotoxy(14, 14);
			cout << "�߸� ������ϴ�.";
		}

		if (lose_cnt == 2) {
			gotoxy(14, 15);
			cout << "�� �̻� ���� ���� ���ؿ� �Ф�";
			Sleep(2000);
			system("cls");
			DrawGameOver();
			
			houseSize -= rand() % 5 + 1;	
			return false;

		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "���� ���� �� �־��!";
			Sleep(2000);
			system("cls");
			DrawGamePass();
			houseSize += rand() % 7 + 2;
			system("pause>null");
			return true;
		}
		Sleep(1000);
		system("cls"); //ȭ�� �����
	}
}

//���� ����
bool QuizGame() {
	string quiz[] = { "���ѹα��� ������?(�α���) : ", "3 * 3 = ", " 3 * 5 + 9 = ","�����ϴ� �뷡�� �����ּ���! : ","2 + 3 * 5 = ",
		"�ξ��̰� ������ �� ���� �Ҹ���?(������) : ","���󿡼� ���� ������ ����?(�ױ���) : ","4 / 2 + 6 = ","7 * 8 / 4 = ","����� �������� ���� �̸���? (������) : ", "�����ϴ� ������ ? : " };
	string answer[] = { "����","9","24","","17","÷�ξ�", "�����ӱ�", "8", "14","�����","" };
	string q, user_answer;
	int i;
	int win_cnt = 0;
	int lose_cnt = 0;

	while (true) {
		gotoxy(23, 3);
		cout << "���� ����";

		i = rand() % 11;
		q = quiz[i];
		gotoxy(14, 10);
		cout << q;
		cin >> user_answer;

		if (user_answer == answer[i]) {
			gotoxy(22, 12);
			cout << "�����Դϴ�!";
			win_cnt++;
		}
		else {
			if (user_answer== "") { //���� ""�� ��� ������ ����ó�� 
				gotoxy(22, 12);
				cout << "�����Դϴ�!";
				win_cnt++;
			}
			gotoxy(22, 12);
			cout << "Ʋ�Ƚ��ϴ�.";
			lose_cnt++;
		}

		if (lose_cnt == 2) {
			gotoxy(14, 15);
			cout << "�� �̻� ���� ���� ���ؿ� �Ф�";
			houseSize -= rand() % 5 + 1;
			system("cls");
			DrawGameOver();
			return false;
		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "���� ���� �� �־��!";
			houseSize += rand() % 7 + 2;
			system("cls");
			DrawGamePass();
			return true;
		}
		Sleep(1500);
		system("cls"); //ȭ�� �����
	}
}

//���ٿ� ����
bool upDownGame() {
	int com_sel = rand() % 50 + 1;
	int user_sel;
	int cnt = 0;
	while (cnt <= 5) {
		gotoxy(21, 3);
		cout << "���ٿ� ����";
		gotoxy(11, 6);
		cout << "1~50 ������ �� �߿��� ���̰� ���ϴ� ���ڸ� ���纸����!";
		gotoxy(11, 7);
		cout << "��ȸ�� �� 5���Դϴ�. ���� ���̴� � ���� ��������? : ";

		cin >> user_sel;
		cnt++;
		if (com_sel == user_sel) {
			gotoxy(11, 10);
			cout << "���̰� �� ���� " << com_sel << "�Դϴ�! �����մϴ�~" << endl;
			houseSize += rand() % 7 + 2;
			DrawGamePass();
			return true;
		}
		if (cnt == 5) {
			system("cls");
			gotoxy(10, 10);
			cout << "���̰� �� ���� " << com_sel << "�Դϴ�. ���� ���� �� �����Ф�";
			Sleep(1500);
			system("cls");
			DrawGameOver();
			houseSize -= rand() % 5 + 1;
			return false;
		}

		else if (com_sel > user_sel) {
			gotoxy(11, 10);
			cout << "���̴� �� ū ���� ������ϴ�!";
			gotoxy(11, 11);
			cout << "���� ��ȸ�� " << 5 - cnt << "�� �Դϴ�!";
		}
		else if (com_sel < user_sel) {
			gotoxy(11, 10);
			cout << "���̴� �� ���� ���� ������ϴ�!";
			gotoxy(11, 11);
			cout << "���� ��ȸ�� " << 5 - cnt << "�� �Դϴ�!";
		}
		Sleep(1500);
		system("cls"); //ȭ�� �����
	}
}

//Ÿ�̹� ���߱� ����(���ʽ� ����) - ������ ���� Ŀ��
void timingGame() {
	timeBeginPeriod(1); //timer interrupt �ػ󵵸� 1�� ����
	char pointList[4][256] = { // ���� ����Ʈ
		{"Bad"},
		{"NoGood"},
		{"Good"},
		{"Grea"},
	};

	int g_timing[] = { 5, 10, 14, 17, 20, 25, 29, 34, 37 }; // Ÿ�̹�

	char userPoint[9][256] = { {" "} }; // ������ ���� ����ϴ� �迭

	double begin; // ó�� ���۽� �ð�
	double end; // ���α׷� ���� �� �ݺ����ȿ��� üũ�� �ð�
	double checkC; // begin - end ��
	int tIndex = 0; // �������� üũ
	begin = timeGetTime();

	cout << fixed; // ��� �Ҽ��� �ڸ��� ����
	cout.precision(3); // �Ҽ��� �� 3�ڸ����� ���

	while (1) {

		end = timeGetTime();
		checkC = (end - begin) / 1000; // ����ð� ���ϱ�

		cout << "Ÿ�̸� : " << checkC << endl;
		cout << endl;

		if (_kbhit()) {
			// fabs�� double�� ���밪 ���ϴ� �Լ��Դϴ�.
			if (fabs((double)g_timing[tIndex] - checkC) >= (double)1) { // ���� �Է� �ð��� 1���̻� ���̳� ��� 
				strcpy_s(userPoint[tIndex], strlen(pointList[0]) + 1, pointList[0]);
			}
			// 0.75���Ϸ� ���̳��� 0.5�� �ʰ��� ���̳����
			else if (fabs((double)g_timing[tIndex] - checkC) <= (double)0.75 && fabs((double)g_timing[tIndex] - checkC) > (double)0.5) {
				strcpy_s(userPoint[tIndex], strlen(pointList[1]) + 1, pointList[1]);
			}
			// 0.5���Ϸ� ���̳��� 0.25�� �ʰ��� ���̳����
			else if (fabs((double)g_timing[tIndex] - checkC) <= (double)0.5 && fabs((double)g_timing[tIndex] - checkC) > (double)0.25) {
				strcpy_s(userPoint[tIndex], strlen(pointList[2]) + 1, pointList[2]);
			}
			// 0.25 ���Ϸ� ���̳� ���
			else if (fabs((double)g_timing[tIndex] - checkC) <= (double)0.25) {
				strcpy_s(userPoint[tIndex], strlen(pointList[3]) + 1, pointList[3]);
			}

			_getch(); // ���� ����
			tIndex++; // �������� ���
		}

		// ������ �Է����� �ʾ��� ��� �ڵ����� Bad���� ����
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

		for (int i = 0; i < 9; i++) { // ���� ���������� ������ ������ ���
			cout << g_timing[i] << " Sec : " << userPoint[i] << endl;
		}

		if (tIndex == 9) // ���������� 8�� ������ ��� ����
			break;
		system("cls"); // �ܼ� �����
	}
	timeEndPeriod(1); // timer interrupt �ʱ�ȭ
}

//���� ���� ��
void InfoGame() {
	DrawFirstInfoGame();
	DrawSecondeInfoGame();
	system("pause>null");
}

Login* user = new Login();

//���� ���� ��
void startGame() {
	readyStart();

	if (houseSize == 10) {
		DrawStartMiniGame();
		system("pause>null");
		system("cls");
		if (user_name.empty()) DrawStartGame();

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

int readyStart() { //���� ���� �� �α��� üũ, �Ͽ콺 ������, �Խ�Ʈ �α��� ���� ����
	system("cls");
	if (!(user->getLoginCheck())) { //�α����� �ȵǾ� ������ �Խ�Ʈ �α��� ���� ����
		checkGuest();
	}
	else { //�α��� �Ǿ� ������ �ٷ� ���� �ϴµ� �̸��� ������ �̸� �Է� �κк��� / ��� �����ϸ� ó������ ����� �� ����
		if (user_name.empty()) DrawStartGame();
		system("cls");
	}
	return 0;
}

void CreateAccount() {//���� ����
	system("cls");
	string acc;
	string pw;
	string idHint, pwHint;
	gotoxy(10, 8);
	cout << "������ ������ ������ �Է� : ";
	cin >> acc;
	user->setUserAcc(acc); //������ ����
	gotoxy(10, 10);
	cout << "������ ������ ��й�ȣ �Է� : ";
	cin >> pw;
	user->setUserPw(pw);
	gotoxy(10,12);
	cout << "������ �Ҿ������ ��츦 �����, ��� ������ ������ּ���. ";
	gotoxy(10,13);
	cout << "���θ� �� �� �ִ� ��Ʈ�� �����ֽø� �˴ϴ�.";
	gotoxy(10, 14);
	cout << "������ ���� ��Ʈ�� �����ּ���. : ";
	cin >> idHint;
	user->setIdHint(idHint);
	gotoxy(10, 15);
	cout << "��й�ȣ�� ���� ��Ʈ�� �����ּ���. : ";
	cin >> pwHint;
	user->setPwHint(pwHint);
	system("cls");
	gotoxy(19, 12);
	cout << "������ �����Ǿ����ϴ�.";
	gotoxy(16, 14);
	cout << plz_space;
	system("pause>null");
} 

bool LoginAccount() {//������ ���� Ȯ��, �α����ϱ�
	system("cls");
	string acc;
	string pw;
	gotoxy(15, 8);
	cout << "���� �Է� : ";
	cin >> acc;
	gotoxy(15, 10);
	cout << "��й�ȣ �Է� : ";
	cin >> pw;
	return user->checkUser(acc, pw);
} 

int QuestionAccount() { //���� ã�� �� ����
	//���̵� ã��, ��й�ȣ ã��, �α����ϱ�, ȸ�������ϱ�
	int y = 0; //Ŀ���� y ��ġ
	int x = 0;
	int input = 0; //Ű���� �Է��� ���� ����
	while (true) { //���� ����
		DrawFIndAcc(); //�غ�ȭ�� �׸���
			
		if (y <= 0) { //Ŀ���� ���� �׸� �ö󰡰�
			y = 0;
		}
		else if (y >= 2) { //Ŀ���� �Ʒ��� �׸� ��������
			y = 2;
		}
		if (x <= 0) { //Ŀ���� �������� �׸�����
			x = 0;
		}
		else if (x >= 12) { //Ŀ���� ���������� �׸�����
			x = 12;
		}
		gotoxy(14+x, 13 + y); //��ġ����
		cout << ">";

		input = _getch();
		//����� ����Ű�� ���� ���
		if (input == MAGIC_KEY) { //224�� ����
			switch (_getch()) //�ѹ� �� ����
			{
			case UP: //��
				y-=2;
				break;
			case DOWN: //�Ʒ�
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
		//���� �޴� ��
		else if (input == SPACE || input == ENTER) { //Ű���尡 �����̽��� ���
			switch (y+x) { //y��ġ�� ���� �Ǵ�
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

//�α��� ��
int userLogin() {
	DrawLogin();
	while (true) {
		switch (SelectLogin()) { //������ �޾� �Ǵ�
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

//���� ����
int main() {
	srand((unsigned int)time(NULL));

	SetConsoleVIew(); //���α׷� ������ �� �ܼ� ũ��
	while (true) {
		switch (ReadyGame()) { //������ �޾� �Ǵ�
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
			delete user;
			//delete a1;
			return 0;
		}
	}
	return 0;
}