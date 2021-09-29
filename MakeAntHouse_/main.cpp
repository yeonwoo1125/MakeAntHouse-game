#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h> //Ŀ�� �̵�
#include<conio.h> //_getch()
#include<stdbool.h> //boolean Ÿ�� ���
#include<time.h> //���� �Լ� ���
#include<string>
//#include<mysql.h> //mysql ���� �Լ� ���

using namespace std;
#define MAGIC_KEY 224 //�����¿� ȭ��ǥ�� ���� �� ����Ǿ� ������ ����
#define SPACE 32 //�����̽� Ű ��
#define ENTER 13 //���� Ű ��
#define ESC 27 //esc Ű ��

string user_name; //����� �̸�
string plz_space = "[�����̽��� ���͸� �����ּ���.]";
int houseSize=0; //������ ũ��

enum GUEST {
	LOGIN_USER,
	START
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
void DrawLogin();
GUEST selectGuest();
LOGIN SelectLogin();
MENU ReadyGame();
void drawGuestLogin();

//�̴ϰ���
bool RockPaperScissors();
bool QuizGame();
bool upDownGame();

//��
void InfoGame();
void startGame();
int userLogin();
void printRect(int r);
void readyStart();

//�α��� ����
void CreateAccount();
bool LoginAccount();
void QuestionAccount();




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
	//���̴� �԰� �����̱⸸ �� �״°� ������
	//���� �ð� ���̸� ���� ������ �����
private :
	int ant_x, ant_y;
	int input = 0;
	char feed = '*';
	int feed_x;
	int feed_y;
public:
	ant() : ant_x(0), ant_y(0),feed_x(0),feed_y(0){}
	void ranFeed() {
		feed_x = rand() % ant_x; //������ ���ο� ���� ���� - >������ ���μ��κ��� ���� ����
		feed_y = rand() % ant_y;
		gotoxy(feed_x, feed_y);
		cout << feed;
		
	}
	void eatFeed() { //���̸� ���� -> �̴� ���� ����
		//���� �� ����, ������ ��ǥ�� ����(*) ����
		//��ǥ�� ��ĥ ���, �̴ϰ��� ����
		//(i == 1 || i == r || j == 1 || j == r)

		//case 0 -> RockPaperScissors
		//case 1 -> QuizGame
		//case 2 -> upDownGame
		if (ant_x == feed_x && ant_y==feed_y) { 
			int miniGame;
			miniGame = rand() % 3;
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
			}
		}
		
	}
	void moveInHouse() { //������ �ȿ��� ������
		while (true) {
			input = _getch();
			system("cls");
			if (input == MAGIC_KEY) {
				input = _getch();
				switch (input)
				{
				case UP:
					ant_y--;
					break;
				case DOWN:
					ant_y++;
					break;
				case RIGHT:
					ant_x++;
					break;
				case LEFT:
					ant_x--;
					break;
				}
			}
			gotoxy(ant_x, ant_y);
			cout << "*";
		}
	}

	~ant() {}
};


class Login { //������ �α��� �� ���� ���� �� ���� ���� �� ���� ����
	string user_account;
	int user_id;
	string user_password;
public:
	Login() {
		this->user_id = (rand() % 100000); //���� ���̵� ����
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

	bool checkUser(string acc, string pw) { //����ڰ� �Է��� ������ �ִ� �������� üũ
		int input=0;
		if (getuserAcc() == acc && getuserPw() == pw) {
			system("cls");
			gotoxy(21, 12);
			cout << "�α��� ����" ;
			gotoxy(17, 15);
			cout << plz_space;
			system("pause>null");
			return true;   
		}
			else if (getuserPw() != pw || getuserAcc() != acc) {
				gotoxy(15, 18);
				cout << "�α��� ����" << endl;
				cout << "�ٽ� �õ��Ͻ÷��� �����̽��� �����ּ���." << endl;
				cout << "�����̽��� ������ �α����� ��õ��մϴ�." << endl;
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
						gotoxy(15, 8);
						cout << "���� �Է� : ";
						cin >> acc;
						gotoxy(15, 10);
						cout << "��й�ȣ �Է� : ";
						cin >> pw;
						checkUser(acc, pw);
					}
					
				}
				return false;
			}

	}
	bool checkLogin() {
		if (checkUser(getuserAcc(),getuserPw())) { //checkUser�� true�� �α��� ������, �ٷ� �θ��� �Ű������� ��� �ȵ�
			system("cls");
			return true;
		}
		return false;
	}
	~Login() {}
};

bool checkGuest() { //�Խ�Ʈ�� �α��� �Ұ��� ����
	drawGuestLogin();
	while (true) {
		switch (selectGuest()) { //������ �޾� �Ǵ�
		case LOGIN_USER:
			return LoginAccount();

		case START:
			system("cls");
			startGame();
			break;
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
	cout << "���� ����";
	gotoxy(22, 13);
	cout << "���� ����";
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
//�α��� ȭ�� �׸���
void DrawLogin() {

	system("cls");    //ȭ���� Ŭ���� ���ִ� �Լ�

	gotoxy(22, 12);
	cout << "�� �� ��";
	gotoxy(22, 13);
	cout << "ȸ�� ����";
	gotoxy(22, 14);
	cout << "���� ã��" << endl;
	gotoxy(22, 15);
	cout << "�� �� ��" << endl;

	gotoxy(17, 19);
	cout << plz_space;
}

//�Խ�Ʈ �α��� ȭ�� �׸���
void drawGuestLogin() {
	system("cls");
	gotoxy(17, 8);
	cout << "�Խ�Ʈ�� �α��� �Ͻðڽ��ϱ�?";
	gotoxy(13, 9);
	cout << "�Խ�Ʈ�� �α��� �� ���� ���� �� ������� �ʽ��ϴ�.";
	gotoxy(23, 12);
	cout << "�� �� ��";
	gotoxy(23, 13);
	cout << "���ӽ���";

	gotoxy(18, 17);
	cout << plz_space;
}




GUEST selectGuest() {
	int y = 0; //Ŀ���� y ��ġ
	int input = 0; //Ű���� �Է��� ���� ����
	while (true) { //���� ����

		//DrawUserCursor �Լ�
		if (y <= 0) { //Ŀ���� ���� �׸� �ö󰡰�
			y = 0;
		}
		else if (y >= 1) { //Ŀ���� �Ʒ��� �׸� ��������
			y = 1;
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
//���� ����
//user�� ����, �̺�Ʈ�� �߻��� ������ ���� ��Ű�ų� �ø��ų� �ν��� �� ����
//�̺�Ʈ : �̴ϰ��� �̺�Ʈ(�������� �߻�)




//������ �׸���
void printRect(int r) {

	system("cls");
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
			if (i == 1 || i == r || j == 1 || j == r)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}

	system("pause>null");
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
			Sleep(1500); //1.5�ʸ� ��ٸ�
		}

		if (lose_cnt == 2) {
			gotoxy(14, 15);
			cout << "�� �̻� ���� ���� ���ؿ� �Ф�";
			Sleep(2000);
			system("cls");
			DrawGameOver();
			if (houseSize < 2 || rand() % 10 % 3 == 0) {//���� ��� 3�� ����� ��쿡�� ���� Ŀ��
		
				houseSize += rand() % 5 + 1;
			}

			else {//���� ��쿡�� ����  �۾���
				
				houseSize -= rand() % 4 + 1;
			}
			printRect(houseSize);
			return false;

		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "���� ���� �� �־��!";
			Sleep(2000);
			system("cls");
			houseSize += rand() % 7 + 2;
			printRect(houseSize);
			system("pause>null");
			return true;
		}

		Sleep(1500);
		system("cls"); //ȭ�� �����
	}
}

//���� ����
bool QuizGame() {
	string quiz[] = { "���ѹα��� ������?(�α���) : ", "3 * 3 = ", " 3 * 5 + 9 = ","�����ϴ� �뷡�� �����ּ���! : ","2 + 3 * 5 = ",
		"�ξ��̰� ������ �� ���� �Ҹ���?(������) : ","���󿡼� ���� ������ ����?(�ױ���) : ","4 / 2 + 6 = " };
	string answer[] = { "����","9","24","","17","÷�ξ�", "�����ӱ�", "8" };
	string q, user_answer;
	int i;
	int win_cnt = 0;
	int lose_cnt = 0;


	while (true) {
		gotoxy(23, 3);
		cout << "���� ����";

		i = rand() % 9;
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
			if (i == 3 && user_answer != "") {
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
			if (houseSize < 2 || rand() % 10 % 3 == 0) {//���� ��� 3�� ����� ��쿡�� ���� Ŀ��
				int tmp = rand() % 5 + 1;
				houseSize += tmp;
			}

			else {//���� ��쿡�� ����  �۾���
				int tmp = rand() % 4 + 1;
				houseSize -= tmp;
			}
			printRect(houseSize);
			return false;
		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "���� ���� �� �־��!";
			houseSize += rand() % 7 + 2;
			printRect(houseSize);
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
	int cnt = 1;
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
			printRect(houseSize);
			return true;
		}
		if (cnt == 5) {
			system("cls");
			gotoxy(10, 10);
			cout << "���̰� �� ���� " << com_sel << "�Դϴ�. ���� ���� �� �����Ф�";
			Sleep(1500);
			system("cls");
			DrawGameOver();
			houseSize += rand() % 4 + 1;
			printRect(houseSize);
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

//���� ���� ��
void InfoGame() {
	DrawFirstInfoGame();
	DrawSecondeInfoGame();
	system("pause>null");
}

Login* user = new Login();
ant a1;
//���� ���� ��
void startGame() {
	//���� ������ �����µ� ���� �α����� �ȵǾ� ������ �Խ�Ʈ �α����̳İ� ���� -> ��� ���� �ȵ�
	//�Խ�Ʈ �ƴ϶� �׷��� �α��� ȭ�� ���� -> ���� ������ ȸ������ �� -> ���� ���� �ϰ� �ٷ� �̸� �Է� �� �̴� ���Ӻ���..
	//�α��� �����ϸ� ���ݱ��� ���� �� ������� -> 0�̸� ���� ��
	readyStart();
	if (houseSize != 0) printRect(houseSize);
	else {
		cout << "�̴ϰ��� ����";
	}
	system("pause>null");

}
void readyStart() {
	if (!(user->checkLogin())) { //�α����� �ȵǾ� ������ �Խ�Ʈ �α��� ���� ����
		checkGuest();
	}
	else { //�α��� �Ǿ� ������ �ٷ� ���� �� �ϴµ� �̸��� ������ �̸� �Է� �κк��� / ��� �����ϸ� ó������ ����� �� ����
		if (user_name == "") DrawStartGame();
		system("cls");
	}
}

void CreateAccount() {//���� ����
	system("cls");
	string acc;
	string pw;
	gotoxy(10, 8);
	cout << "������ ������ ������ �Է� : ";
	cin >> acc;
	user->setUserAcc(acc); //������ ����
	gotoxy(10, 10);
	cout << "������ ������ ��й�ȣ �Է� : ";
	cin >> pw;
	user->setUserPw(pw);
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
void QuestionAccount() { //���� ã�� �� ����

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
			userLogin();
			break;
		case QUESTION:
			QuestionAccount();
			break;
		case QUITLOGIN :
			ReadyGame();
			break;
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
			cout << user_name + "���� �����ֽ� ���� " << houseSize << "�� ũ���Դϴ�! �����մϴ�";
			delete user;
			return 0;
		}
	}
	return 0;
}