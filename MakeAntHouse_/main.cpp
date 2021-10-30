#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h> //Ŀ�� �̵�
#include<conio.h> //_getch()
#include<stdbool.h> //boolean Ÿ�� ���
#include<time.h> //���� �Լ� ���
#include<string>
#include <cstring>
#include<fstream> //����ó��
#include <mmsystem.h> //���� �ֱ�
#include <thread> //thread 

#pragma comment(lib, "winmm.lib") 

using namespace std;

#define MAGIC_KEY 224 //�����¿� ȭ��ǥ�� ���� �� ����Ǿ� ������ ����
#define SPACE 32 //�����̽� Ű ��
#define ENTER 13 //���� Ű ��
#define ESC 27 //esc Ű ��

int cntAcc = 0;
string plz_space = "[ �����̽��� ���͸� �����ּ���. ]";
string plz_key = "[ �ƹ� Ű�� �����ּ���. ]";

//���� ó��
ofstream ofs("antHouse.txt", ios::app);
FILE* fp1;

//�Խ�Ʈ �α��� �޴�
enum GUEST {
	LOGIN_USER,
	START,
	QUITGUEST
};

//�α��� �޴�
enum LOGIN {
	CREATE,
	FIND,
	QUESTION,
	QUITLOGIN
};

//���� �޴�
enum MENU {
	GAMESTART = 0,
	INFO,
	QUIT,
	ACCOUNT
};

//Ű���� ����Ű ��
enum KEYBOARD {
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};

//�ܼ�â ����
void SetConsoleVIew_main();
void fullScreen();

//ȭ�� �׸��� �Լ�
void DrawFirstInfoGame();
void DrawSecondeInfoGame();
void DrawStartGame();
void DrawGameOver();
void DrawGamePass();
void DrawStartMiniGame();
void DrawDieAnt();

//����ã��
void DrawFIndAcc();
void FindId();
void FindPw();

void DrawRetryId();
void DrawRetryPwAnswer();

//�޴� ����
GUEST selectGuest();
void DrawGuestLogin();
LOGIN SelectLogin();
void DrawLogin();
MENU ReadyGame();
void DrawReadyGame();

//�̴ϰ���
bool RockPaperScissors();
bool QuizGame();
bool upDownGame();
void timingGame();

//��
void InfoGame();
void startGame();
int userLogin();

//���� ���� �غ�
int checkReady();
int checkGuest();
void readyStart();

//�α��� ����
int CreateAccount();
void LoginAccount();
int QuestionAccount();
bool checkSameAccount();
bool checkCntAcc();

//����ó��
void getFileData();
void setFileData(string acc, string pw, string name, string idAnswer, int pwAnswer);

//���� �Դ� �Լ�
void eatFeed();

//�����带 ���� �Լ�
int threadStart();

//���콺 ��ǥ 
void gotoxy(int x, int y) { //Ŀ���� Ư�� ��ġ�� �̵���Ű�� �Լ�
	COORD Pos;
	Pos.X = 2 * x; //1ĭ���ٴ� 2ĭ�� �������� �ڿ�������
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//�ܼ� ũ��, Ÿ��Ʋ
void SetConsoleVIew_main() {
	system("mode con:cols=100 lines=30"); //���� 50, ���� 30
	system("title Make Ant House By Yeonwoo"); //Ÿ��Ʋ
}

//��üȭ��
void fullScreen() {
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

//�α��� �� �ʿ��� ��
class Login { //������ �α��� �� ���� ���� �� ���� ���� �� ���� ����
	string user_account; //��������
	string user_password; //���
	bool loginCheck=false; //�α��� ���� ���� �ľ�
	string idAnswer; //���̵� ��Ʈ
	int pwAnswer; //��� ��Ʈ
	string user_name; //�̸�
	int houseSize; //������ ũ��
	string user_Nickname; //����� ����, �ΰ��� �� ���Ǵ� �̸�
public:                        
	Login() {
		this->houseSize = 8;
	}
	void setUserNickname(string n) { this->user_Nickname = n; }
	string getUserNickname() { return user_Nickname; }
	void setHouseSize(int h) { this->houseSize += h; }
	int getHouseSize() { return houseSize; }
	void setUserName(string userName) { this->user_name = userName; }
	string getUserName() { return user_name; }
	void setIdAnswer(string idAns) { this->idAnswer = idAns; }
	string getIdAnswer() { return idAnswer; }
	void setPwAnswer(int pwAns) { this->pwAnswer = pwAns; }
	int getPwAnswer() { return pwAnswer; }
	void setUserAcc(string userAcc) { this->user_account = userAcc; }
	string getUserAcc() { return user_account; }
	string getUserPw() { return user_password; }
	void setUserPw(string userPw) { this->user_password = userPw; }
	void setLoginCheck(bool loginCheck) { this->loginCheck = loginCheck; }
	bool getLoginCheck() { return loginCheck; }

	bool checkUser(string acc, string pw) { //����ڰ� �Է��� ������ �ִ� �������� üũ
		int input = 0;
		if (getUserAcc() == acc && getUserPw() == pw) {
			this->setLoginCheck(true);
			system("cls");
			gotoxy(21, 12);
			cout << "�α��� ����";
			gotoxy(18, 15);
			cout << plz_key;
			system("pause>null");
			return true;
		}
		else if (getUserPw() != pw || getUserAcc() != acc) {
			this->setLoginCheck(false);
			system("cls");
			gotoxy(21, 9);
			cout << "�α��� ����" << endl;
			gotoxy(15, 11);
			cout << "�ٽ� �õ��Ͻ÷��� �����̽��� �����ּ���." << endl;
			gotoxy(15, 12);
			cout << "�����̽��� ������ �α����� ��õ��մϴ�." << endl;
			gotoxy(17, 13);
			cout << "�����÷��� ESC�� �����ּ���.";
			while (true) {
				input = _getch();
				if (input == ESC) { return false; }
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
					this->checkUser(acc, pw);
				}
			}
			return false;
		}

	}
	~Login() {}
	
};
Login *user[3];
Login player;

//���� ��ü
class Ant { //���������� ������ ���� ��ü
private:
	int ant_x, ant_y;
	int input = 0;
	string antShape = "@@@";
	bool checkEatFeed = false;
public:
	Ant() : ant_x(8), ant_y(6) {}
	int getAntX() { return ant_x; }
	int getAntY() { return ant_y; }
	
	int moveInHouse() { //������ �ȿ��� ������
		while (true) {
			input = _getch();
			if (input == MAGIC_KEY) {
				input = _getch();
				switch (input)
				{
				case UP:
					gotoxy(ant_x, ant_y); //���̰� ������ �ڸ� �����
					cout << "   ";
					if (ant_y < 5) ant_y = 4; //���̶� �浹üũ
					else ant_y--;
					gotoxy(ant_x, ant_y);
					cout << antShape;
					eatFeed();
					break;
				case DOWN:
					gotoxy(ant_x, ant_y);
					cout << "   ";
					if (ant_y > player.getHouseSize() + 1) ant_y = player.getHouseSize() + 2;
					else ant_y++;
					gotoxy(ant_x, ant_y);
					cout << antShape;
					eatFeed();
					break;
				case RIGHT:
					gotoxy(ant_x, ant_y);
					cout << "   ";
					if (ant_x > player.getHouseSize() + 3) ant_x = player.getHouseSize() + 4;
					else ant_x++;
					gotoxy(ant_x, ant_y);
					cout << antShape;
					eatFeed();
					break;
				case LEFT:
					gotoxy(ant_x, ant_y);
					cout << "   ";
					if (ant_x < 9) ant_x = 8;
					else ant_x--;
					gotoxy(ant_x, ant_y);
					cout << antShape;
					eatFeed();
					break;
				case ESC:
					return 0;
				}
			}
		}
	}

	void drawAntHouse(int r) {
		//�⺻ �� �׸���
		/*gotoxy(5, 2);
		cout << "���� ũ�� : " << r << endl;*/

		gotoxy(7, 3);
		for (int i = 0; i < r; i++) { //�� ����
			cout << "��";
		}
		for (int i = 0; i < r - 1; i++) { //���� 1
			gotoxy(7, 4 + i);
			cout << "��";
		}
		for (int i = 0; i < r - 1; i++) { //���� 2
			gotoxy(6 + r, 4 + i);
			cout << "��";
		}
		gotoxy(7, 3 + r);
		for (int i = 0; i < r; i++) { //�� �Ʒ���

			cout << "��";
		}
	}
	~Ant() {}
};
Ant a1;

//���� ��ü
class Feed {
private:
	int feed_x, feed_y;
	int feedCnt = 3; //�⺻������ ���� 3�� ����
	char feedShape = '*';
	
public://���� �������� ������ ������ ��
	int getFeedCnt() { return feedCnt; }
	int getFeedX() { return feed_x; }
	int getFeedY() { return feed_y; }
	void setFeedCnt(int n) { feedCnt -= n; }
	int ranFeed() {
		while(true) {
			if (getFeedCnt() > 9) 
				DrawDieAnt();
			feed_x = rand() % player.getHouseSize()+4; //������ ���ο� ���� ���� - >������ ���μ��κ��� ���� ����
			feed_y = 4 + rand() % player.getHouseSize() +3;
			gotoxy(feed_x, feed_y);
			cout << feedShape;
			Sleep(5000);
			feedCnt++;
		}
		 //5�ʸ��� ���� ����
		return 0;
	}	
};
Feed f1;

//���̰� ���̸� ���� ��� - ���̸� ����� �̴ϰ��� ���� 
void eatFeed() { 
	//��ǥ�� ��ĥ ���, �̴ϰ��� ����
	//case 0 -> RockPaperScissors
	//case 1 -> QuizGame
	//case 2 -> upDownGame
	//case 3 -> timingGame
	if (a1.getAntX() == f1.getFeedX() && a1.getAntY() ==f1.getFeedY()) {
		f1.setFeedCnt(1);
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

//���Ͽ� �����ϱ�
void setFileData(string acc, string pw, string name, string idAnswer, int pwAnswer) {
	ofs << acc << " "; //name txt���Ͽ� ����
	ofs << pw << " "; //pw txt���Ͽ� ����
	ofs << name << " "; //name txt���Ͽ� ����
	ofs << idAnswer << " "; //idAnswer txt���Ͽ� ����
	ofs << pwAnswer << " ";
	ofs.close();
}
//���Ͽ� ����� ���� �����ͼ� �����ϱ�
void getFileData() {
	string acc, pw, name, accAn, pwAn, h;
	int cnt = 0;
	fp1 = fopen("antHouse.txt", "r");

	while (!feof(fp1)) {
		user[cnt] = new Login;
		fscanf(fp1, "%s %s %s %s %s %s", &acc, &pw, &name, &accAn, &pwAn, &h);
		user[cnt]->setUserAcc(acc);
		user[cnt]->setUserPw(pw);
		user[cnt]->setUserName(name);
		user[cnt]->setIdAnswer(accAn);
		user[cnt]->setPwAnswer(stoi(pwAn));
		user[cnt]->setHouseSize(stoi(h));
		cnt++;

	}
	fclose(fp1);
}

//�Խ�Ʈ�� �α��� �Ұ��� ����
int checkGuest() { 
	DrawGuestLogin();

	while (true) {
		switch (selectGuest()) { //������ �޾� �Ǵ�
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

//���� �޴� �׸���
void DrawReadyGame() {
	system("cls");    //ȭ���� Ŭ���� ���ִ� �Լ� �Դϴ�.
	gotoxy(15, 3);
	cout << "**************************************";
	gotoxy(15, 4);
	cout << "*                                    *";
	gotoxy(15, 5);
	cout << "*              ��������              *";
	gotoxy(15, 6);
	cout << "*        �������� ���������         *";
	gotoxy(15, 7);
	cout << "*                                    *";
	gotoxy(15, 8);
	cout << "**************************************";
	gotoxy(22, 11);
	cout << "���ӽ���";
	gotoxy(22, 13);
	cout << "���Ӽ���";
	gotoxy(19, 15);
	cout << "ȸ������ �� ����ã��" << endl;
	gotoxy(22, 17);
	cout << "�� �� ��" << endl;

	gotoxy(16, 22);
	cout << plz_space;
}

//���� ���� �׸���
void DrawFirstInfoGame()
{
	system("cls");
	gotoxy(3, 1);
	cout << "��������������������������";
	gotoxy(3, 3);
	cout << "   ���Ӽ���";
	gotoxy(3, 5);
	cout << "��������������������������";

	gotoxy(3, 10);
	cout << "���̵��� ���ο� ������ �̻縦 �Ծ��.";
	gotoxy(3, 11);
	cout << "���� ������ ��� ���� ���̸� �����ּ���!";
	gotoxy(3, 14);
	cout << "���̿��� ���̸� ���̰�, ���� ������ ���� ������ ���ּ���.";
	gotoxy(3, 15);
	cout << "�� ���ų� ħ���ڰ� ���� ���� ������ ���� �����ּ���.";
	gotoxy(3, 16);
	cout << "������ ���� ���̰� ����� �Ծ��ּ���. ���� ���� ������ ���� ���� �ֽ��ϴ�.";
	gotoxy(3, 17);
	cout << "���� �԰� ���� �� ���� �����ּ���!";
	gotoxy(3, 18);
	cout << "����� ������ ���� ���� ū ���� �ǵ��� Ű���ּ���.";

	gotoxy(38, 24);
	cout << "���� ������";
	gotoxy(37, 24);
	cout << ">";
	system("pause>null");
}
//���� ���� �׸���
void DrawSecondeInfoGame()
{
	system("cls");
	gotoxy(3, 1);
	cout << "��������������������������";
	gotoxy(3, 3);
	cout << "   ��������";
	gotoxy(3, 5);
	cout << "��������������������������";

	gotoxy(3, 9);
	cout << "������ ó�� �����Ͻô� ���� ȸ�������� ���ּ���.(�α���->ȸ������)";
	gotoxy(3, 10);
	cout << "�̹� ������ �����Ѵٸ� �α����� �� �� ������ �����ϸ� �˴ϴ�.";
	gotoxy(3, 12);
	cout << "������ �Ҿ������ ���, ���� ã�⸦ ���� ������ ã���ּ���.(�α���->���� ã��)";
	gotoxy(3, 13);
	cout << "�α��� ���� ������ �ϰ� �ʹٸ� �Խ�Ʈ �α����� ���� ������ ����ּ���.";
	gotoxy(3, 15);
	cout << "���� ó�� ������ �����ϸ�, �̴ϰ����� ���� �⺻ ũ���� �������� ��� �˴ϴ�.";
	gotoxy(3, 16);
	cout << "�������� �����Ǵ� ������ ���̸� ������ �̴ϰ����� �� �� �ֽ��ϴ�. ";
	gotoxy(3, 17);
	cout << "������ ���� �ð� ���̸� ���� ������ ���̰� ���� ���� ������ �����ϼ���.";
	gotoxy(3, 18);
	cout << "���� ������ ���� �ʹ� �۾����ٸ� ���̰� �̻簥 ���� ������ �� �������ּ���.";
	gotoxy(3, 20);
	cout << "�׷� ��ſ� �ð� �Ǽ���!";
	gotoxy(17, 24);
	cout << plz_key;
}


//���� ȭ�� �׸���
void DrawStartGame() {
	string n;
	if (player.getUserNickname().empty()) {
		system("cls");
		gotoxy(14, 9);
		cout << "���̵��� �ٸ��� ���� ���� ���� ���ϰ� �־��!";
		gotoxy(15, 10);
		cout << "����� ���̵��� ���� ������ָ� ���ھ��.";
		gotoxy(13, 11);
		cout << "���̵鿡�� ����� �̸��� �˷��ָ� ������ �Ұſ���.";
		gotoxy(15, 12);
		cout << " ����� �̸��� �����ΰ���? : ";
		cin >> n;
		player.setUserNickname(n);
	}
}

//���� �״� ��� - ���� ���� �׸���
void DrawDieAnt() { //�������� 0���� �۾����� ���, ���̸� ���� �ʾ��� ���
	if (f1.getFeedCnt() > 9) {
		gotoxy(18, 10);
		cout << player.getUserNickname() << "���� ���̰� �����׾����ϴ�.";
		gotoxy(18, 11);
		cout << player.getUserNickname() << "���� ���� ũ��� " << player.getHouseSize() << "�Դϴ�.";
		gotoxy(18, 14);
		DrawGameOver();
		
	}
	else if (player.getHouseSize() <= 0) {
		gotoxy(18, 10);
		cout << player.getUserNickname() << "���� ���� �ν��� ���̰� �̻縦 �����ϴ�.";
		gotoxy(18, 12);
		DrawGameOver();
	}
}

//�̴ϰ��� ���� ȭ�� �׸���
void DrawStartMiniGame() {
	system("cls");
	gotoxy(17, 8);
	cout << "|------------------------|";
	gotoxy(17, 9);
	cout << "|   ���� ���� �����Ƿ�   |";
	gotoxy(17, 10);
	cout << "|  �̴ϰ����� �����մϴ� |";
	gotoxy(17, 11);
	cout << "|------------------------|";
	gotoxy(17, 14);
	cout << plz_key;
	//return 0;
}

//���� ���� �׸���
void DrawGameOver() {
	gotoxy(18, 8);
	cout << "|-----------------|";
	gotoxy(18, 9);
	cout << "|                 |";
	gotoxy(18, 10);
	cout << "| G A M E O V E R |";
	gotoxy(18, 11);
	cout << "|                 |";
	gotoxy(18, 12);
	cout << "|-----------------|";
	gotoxy(17, 15);
	cout << plz_key;
	system("pause>null");
}

//���� ��� �׸���
void DrawGamePass() {
	gotoxy(18, 8);
	cout << "|-----------------|";
	gotoxy(18, 9);
	cout << "|                 |";
	gotoxy(18, 10);
	cout << "| G A M E P A S S |";
	gotoxy(18, 11);
	cout << "|                 |";
	gotoxy(18, 12);
	cout << "|-----------------|";
	gotoxy(17, 14);
	cout << plz_key;
	system("pause>null");
}

//�α��� ȭ�� �׸���
void DrawLogin() {
	system("cls");    //ȭ���� Ŭ���� ���ִ� �Լ�
	gotoxy(17, 3);
	cout << "******************************" ;
	gotoxy(17, 4);
	cout << "*                            *";
	gotoxy(17, 5);
	cout << "*   ȸ������ ��  ���� ã��   *";
	gotoxy(17, 6);
	cout << "*                            *";
	gotoxy(17, 7);
	cout << "******************************";

	gotoxy(22, 12);
	cout << "ȸ������";
	gotoxy(22, 14);
	cout << "����ã��";
	gotoxy(22, 16);
	cout << "�� �� ��";

	gotoxy(17, 22);
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

	gotoxy(17, 17);
	cout << plz_space;
}

//���̵� �ٽ� �Է�
void DrawRetryId() {
	gotoxy(16, 10);
	cout << "�������� 10�� �̳��� �Է����ּ���.";
	gotoxy(17, 17);
	cout << plz_key;
	system("pause>null");
}

//��й�ȣ �ٽ� �Է�
void DrawRetryPwAnswer() {
	gotoxy(15, 10);
	cout << "�¾ ���� 1~12 �� ���ڷ� �Է����ּ���.";
	gotoxy(17, 17);
	cout << plz_key;
	system("pause>null");
}

//���� 3�������� ���弼��
bool checkCntAcc() {
	return true;
}

//����ã�� ȭ�� �׸���
void DrawFIndAcc() {
	system("cls");
	gotoxy(20, 3);
	cout << "*****************";
	gotoxy(20, 4);
	cout << "*               *";
	gotoxy(20, 5);
	cout << "*   ���� ã��   *";
	gotoxy(20, 6);
	cout << "*               *";
	gotoxy(20, 7);
	cout << "*****************";
	gotoxy(15, 13);
	cout << "������ ã��";
	gotoxy(27, 13);
	cout << "��й�ȣ ã��";
	gotoxy(15, 15);
	cout << "�α��� �ϱ�";
	gotoxy(27, 15);
	cout << "�� �� ��";

	gotoxy(17, 20);
	cout << plz_space;
	
}

//���̵� ã�� ȭ�� �׸���
void FindId() {
	string answer;
	int input = 0;
	system("cls");
	gotoxy(20, 3);
	cout << "******************";
	gotoxy(20, 4);
	cout << "*   ���̵�ã��   *";
	gotoxy(20, 5);
	cout << "******************";
	while (true) {
		system("cls");
		if (player.getUserAcc().empty()) {
			gotoxy(18, 11);
			cout << "���� ������ �������ּ���.";
			gotoxy(18, 14);
			cout << plz_key;
			system("pause>null");
			break;
		}

		gotoxy(14, 8);
		cout <<"������ ���� ���� �Ͻø� ��Ʈ�� �����˴ϴ�.";
		gotoxy(14, 10);
		cout << "���� �����ϴ� ������? : ";
		cin >> answer;

		if (player.getIdAnswer() == answer) {
			gotoxy(15, 12);
			cout << player.getUserName() << "���� ���̵�� " << player.getUserAcc()<<"�Դϴ�";
			gotoxy(18, 17);
			cout << plz_key;
			system("pause>null");
			break;
		}

		else {
			gotoxy(20, 16);
			cout << "�ٽ� �Է����ּ���.";
			gotoxy(18, 17);
			cout << "ESC�� ������ �����մϴ�.";

			input = _getch();
			if (input == ESC) break;
			else continue;
		}
	}
}

//��й�ȣ ã�� ȭ�� �׸���
void FindPw() {
	int answer;
	string userId;
	int input = 0;
	system("cls");
	gotoxy(20, 3);
	cout << "********************";
	gotoxy(20, 4);
	cout << "*   ��й�ȣã��   *";
	gotoxy(20, 5);
	cout << "********************";
	while (true) {
		system("cls");
		if (player.getPwAnswer()==NULL) {
			gotoxy(18, 11);
			cout << "���� ������ �������ּ���.";
			gotoxy(16, 14);
			cout << plz_key;
			system("pause>null");
			break;
		}

		gotoxy(15, 10);
		cout << "���̵� �Է����ּ���. : ";
		cin >> userId;
		gotoxy(15, 12);
		cout << "������ ���� ���� �Ͻø� ��Ʈ�� �����˴ϴ�.";
		gotoxy(15, 13);
		cout << "�¾ ����? (�α���) :  ";
		cin >> answer;

		if (player.getUserAcc() == userId && player.getPwAnswer() == answer) {
			gotoxy(15, 15);
			cout << player.getUserName() << "���� ��й�ȣ�� " << player.getUserPw();
			gotoxy(16, 14);
			cout << plz_key;
			system("pause>null");
			break;
		}

		else {
			gotoxy(20, 15);
			cout << "�ٽ� �Է����ּ���.";
			gotoxy(18, 16);
			cout << "ESC�� ������ �����մϴ�.";

			input = _getch();
			if (input == ESC) break;
			else continue;
		}
	}
}

GUEST selectGuest() {
	int y = 0; //Ŀ���� y ��ġ
	int input = 0; //Ű���� �Է��� ���� ����
	while (true) { //���� ����

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
		else if (y >= 4) { //Ŀ���� �Ʒ��� �׸� ��������
			y = 4;
		}
		gotoxy(21, 12 + y); //��ġ����
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
			}
		}
		//���� �޴� ��
		else if (input == SPACE || input == ENTER) { //Ű���尡 �����̽��� ���
			switch (y) { //y��ġ�� ���� �Ǵ�
			case 0:
				return CREATE;
			case 2:
				return QUESTION;
			case 4:
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

		if (y <= 0) { //Ŀ���� ���� �׸� �ö󰡰�
			y = 0;
		}
		else if (y >= 6) { //Ŀ���� �Ʒ��� �׸� ��������
			y = 6;
		}


		if (y == 4) {
			gotoxy(18, 11 + y); //��ġ����
			cout << ">";
		}
		else {
			gotoxy(21, 11 + y); //��ġ����
			cout << ">";
		}
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
			}
		}
		//���� �޴� ��
		else if (input == SPACE || input == ENTER) { //Ű���尡 �����̽��� ���
			switch (y) { //y��ġ�� ���� �Ǵ�
			case 0:
				return GAMESTART;
			case 2:
				return INFO;
			case 4:
				return ACCOUNT;
			case 6:
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
		cout << win_cnt << "�� " << lose_cnt << "�� ";
		gotoxy(14, 10);
		cout << player.getUserNickname() << " : ";
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

			player.setHouseSize(-rand() % 5 + 1);
			
			if (player.getHouseSize() <= 0) DrawDieAnt();
			return false;

		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "���� ���� �� �־��!";
			Sleep(2000);
			system("cls");
			DrawGamePass();
			player.setHouseSize(rand() % 7 + 2);
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
			if (user_answer == "") { //���� ""�� ��� ������ ����ó�� 
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
			
			system("cls");
			DrawGameOver();
			player.setHouseSize(-rand() % 5 + 1);
			if (player.getHouseSize() <= 0) DrawDieAnt();
			return false;
		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "���� ���� �� �־��!";
			
			system("cls");
			DrawGamePass();
			player.setHouseSize(rand() % 7 + 2);
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
			player.setHouseSize(rand() % 7 + 2);
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
			player.setHouseSize(-rand() % 5 + 1);
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

//������ �����ϴ� �κ�
int threadStart() {
	thread t1(&Ant::moveInHouse,a1);
	thread t2(&Feed::ranFeed,f1);

	t1.join();
	t2.join();
	
	return 0;
}

//���� ���� ��
void startGame() { //�Խ�Ʈ �α��� �� ���� ���� �κ�, ������ �̴ϰ����ؾ���
		system("cls");
		if (player.getUserNickname().empty()) {// �г����� ���� ���, ó�� �α��� �� ���
			DrawStartGame(); //�г��� ���� �� �̴ϰ��� ����
			DrawStartMiniGame();
			system("pause>null");
			startGame();
		}
		if (RockPaperScissors()) {
			system("cls");
			a1.drawAntHouse(player.getHouseSize());
			threadStart();
		}
		else {
			system("cls");
			a1.drawAntHouse(player.getHouseSize());
			threadStart();
		}
}

//���� ���� �� �α��� üũ, �Ͽ콺 ������, �Խ�Ʈ �α��� ���� ����
void readyStart() { 
	system("cls");
	if ((player.getLoginCheck())) { //�α��� ����
		if (player.getUserNickname().empty()) {// �г����� ���� ���, ó�� �α��� �� ���
			DrawStartGame(); //�г��� ���� �� �̴ϰ��� ����
			startGame();
		} // �α����� �Ǿ� ������ �ٷ� �� �׸��� ���� �����ϱ�
		a1.drawAntHouse(player.getHouseSize());
		a1.moveInHouse();
	}
	else { //�α����� �ȵ��� ���
		checkReady(); //�Խ�Ʈ �α��� ���� ����
	}
	system("cls");
}

//�Խ�Ʈ �α��� �� 
int checkReady() {
	switch (checkGuest()) {
	case 0: return 0;
	case 1: startGame();
	case 2: LoginAccount();
	}
}

//���̵� �ߺ� üũ
bool checkSameAccount() {
	for (int i = 0; i < cntAcc; i++) {
		if (user[i]->getUserAcc() == user[i+1]->getUserAcc()) {
			return false;
		}
	}
	return true;
}

//���� ����
int CreateAccount() {
	system("cls");
	string acc;
	string pw;
	string idAnswer;
	int pwAnswer;
	string name;

	while (true) {
		gotoxy(12, 8);
		cout << "������ ������ ������ �Է�(10�� �̳�) : ";
		cin >> acc;
		if (acc.length() > 10) {
			system("cls");
			DrawRetryId();
		}
		else {
			break;
		}
		system("cls");
	}

	gotoxy(12, 10);
	cout << "������ ������ ��й�ȣ �Է� : ";
	cin >> pw;
	
	gotoxy(12, 12);
	cout << "�̸� �Է� : ";
	cin >> name;
	
	gotoxy(12, 14);
	cout << "������ �Ҿ������ ��츦 �����, ������ ������ּ���. ";
	gotoxy(12, 15);
	cout << "���� �����ϴ� ������? : ";
	cin >> idAnswer;
	

	while (true) {
		gotoxy(12, 8);
		cout << "������ ������ ������ �Է�(10�� �̳�) : "<<acc;
		gotoxy(12, 10);
		cout << "������ ������ ��й�ȣ �Է� : "<<pw;
		gotoxy(12, 12);
		cout << "�̸� �Է� : "<<name;
		gotoxy(12, 14);
		cout << "������ �Ҿ������ ��츦 �����, ������ ������ּ���. ";
		gotoxy(12, 15);
		cout << "���� �����ϴ� ������? : "<<idAnswer;

		gotoxy(12, 17);
		cout << "�¾ ����? (����) : ";
		cin >> pwAnswer;
		if (pwAnswer > 0 && pwAnswer <= 12) {
			break;
		}
		else {
			system("cls");
			DrawRetryPwAnswer();
		}
		system("cls");
	}
	player.setUserAcc(acc);
	player.setUserName(name);
	player.setUserPw(pw);
	player.setIdAnswer(idAnswer);
	player.setPwAnswer(pwAnswer);

	if (checkSameAccount() && checkCntAcc()) {
		setFileData(acc, name, pw, idAnswer, pwAnswer);
		system("cls");
		gotoxy(18, 12);
		cout << "������ �����Ǿ����ϴ�.";
		gotoxy(17, 17);
		cout << plz_key;
		system("pause>null");
	}
	return 0;
}

//������ ���� Ȯ��, �α����ϱ�
void LoginAccount() {
	system("cls");
	string acc;
	string pw;
	gotoxy(15, 8);
	cout << "���� �Է� : ";
	cin >> acc;
	gotoxy(15, 10);
	cout << "��й�ȣ �Է� : ";
	cin >> pw;

	player.checkUser(acc, pw);
}

//���� ã�� �� ����
int QuestionAccount() { 
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
		gotoxy(14 + x, 13 + y); //��ġ����
		cout << ">";

		input = _getch();
		//����� ����Ű�� ���� ���
		if (input == MAGIC_KEY) { //224�� ����
			switch (_getch()) //�ѹ� �� ����
			{
			case UP: //��
				y -= 2;
				break;
			case DOWN: //�Ʒ�
				y += 2;
				break;
			case LEFT:
				x -= 12;
				break;
			case RIGHT:
				x += 12;
				break;
			}
		}
		//���� �޴� ��
		else if (input == SPACE || input == ENTER) { //Ű���尡 �����̽��� ���
			switch (y + x) { //y���� x���� ���� ���� ���� �Ǵ�
			case 0:
				FindId();
				break;
			case 2:
				LoginAccount();
				break;
			case 12:
				FindPw();
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
		case CREATE:
			CreateAccount();
			break;
		case QUESTION:
			QuestionAccount();
			break;
		case QUITLOGIN:
			return 0;
		}
	}
}

//���� ����
int main() {
	//���� �� ����� �����Ͱ� ������ �����ͼ� ����
	if (fp1 != NULL) getFileData();

	srand((unsigned int)time(NULL));
	SetConsoleVIew_main(); 

	while (true) {
		switch (ReadyGame()) { 
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
			ofs << player.getHouseSize() << endl;
			ofs.close();
			delete[] user;
			return 0;
		}
	}
	return 0;
}