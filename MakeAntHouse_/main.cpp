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

string user_name = ""; //����� �̸�
string plz_space = "[�����̽��� ���͸� �����ּ���.]";
int r; //������ ũ��


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

class Login { //������ �α��� �� ���� ���� �� ���� ���� �� ���� ����
	string user_account;
	int user_id;
	string user_password;
public:

	Login() {
		this->user_id = (rand() % 100000); //���� ���̵� ����
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
	void checkUser(string acc, string pw) { //����ڰ� �Է��� ������ �ִ� �������� üũ
		if (getuserAcc() == acc && getuserPw() == pw) cout << "�α��� ����" << endl;
		else if (getuserAcc() == acc && getuserPw() != pw) cout << "��й�ȣ�� Ȯ���ϼ���" << endl;
		else if (getuserAcc() != acc) cout << "�������� �ʴ� ����" << endl;
		else cout << "������������" << endl;
	}
	void checkGuest() { //�Խ�Ʈ�� �α��� �Ұ��� ����
		system("cls");
		gotoxy(17,10);
		cout << "�Խ�Ʈ�� �α��� �Ͻðڽ��ϱ�?";
		gotoxy(13, 11);
		cout << "�Խ�Ʈ�� �α��� �� ���� ���� �� ������� �ʽ��ϴ�.";
		gotoxy(23, 12);
		cout << "�� �� ��";
		gotoxy(23, 13);
		cout << "���ӽ���";
		while (true) {
			switch (selectGuest()) { //������ �޾� �Ǵ�
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
void DrawInfoGame()
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

	gotoxy(18, 19);
	cout << plz_space;
}



//Ŀ�� ������ ���
void DrawUserCursor(int& y)
{
	if (y <= 0)        //Ŀ���� ���� �׸� �ö󰡰� 
	{
		y = 0;
	}
	else if (y >= 2) //Ŀ���� �Ʒ��� �׸� ��������
	{
		y = 2;
	}

	gotoxy(9, 8 + y); //��ġ����
	cout << ">";
}
LOGIN selectGuest() {
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
		gotoxy(22, 13 + y); //��ġ����
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
void antHouse(int r) {
	system("cls");
	//�⺻ �� �׸���
	gotoxy(1, 3);
	cout << "���� ũ�� : " << r << endl;


	//���� ���� ũ�� �̻��̸� ������ ������ ���� ������ ����ǰ� ����

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
			if (r < 2 || rand() % 10 % 3 == 0) {//���� ��� 3�� ����� ��쿡�� ���� Ŀ��
				int tmp = rand() % 5 + 1;
				r += tmp;
			}

			else {//���� ��쿡�� ����  �۾���
				int tmp = rand() % 4 + 1;
				r -= tmp;
			}
			antHouse(r);
			return false;

		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "���� ���� �� �־��!";
			Sleep(2000);
			system("cls");
			r += rand() % 7 + 2;
			antHouse(r);
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
			if (r < 2 || rand() % 10 % 3 == 0) {//���� ��� 3�� ����� ��쿡�� ���� Ŀ��
				int tmp = rand() % 5 + 1;
				r += tmp;
			}

			else {//���� ��쿡�� ����  �۾���
				int tmp = rand() % 4 + 1;
				r -= tmp;
			}
			antHouse(r);
			return false;
		}
		else if (win_cnt == 2) {
			gotoxy(14, 15);
			cout << "���� ���� �� �־��!";
			r += rand() % 7 + 2;
			antHouse(r);
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
			r += rand() % 7 + 2;
			antHouse(r);
			return true;
		}
		if (cnt == 5) {
			system("cls");
			gotoxy(10, 10);
			cout << "���̰� �� ���� " << com_sel << "�Դϴ�. ���� ���� �� �����Ф�";
			Sleep(1500);
			system("cls");
			DrawGameOver();
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
	DrawInfoGame();
	system("pause>null");
}

//���� ���� ��
void startGame() {
	//���� ������ �����µ� ���� �α����� �ȵǾ� ������ �Խ�Ʈ �α����̳İ� ���� -> ��� ���� �ȵ�
	//�Խ�Ʈ �ƴ϶� �׷��� �α��� ȭ�� ���� -> ���� ������ ȸ������ �� -> ���� ���� �ϰ� �ٷ� �̸� �Է� �� �̴� ���Ӻ���..
	//�α��� �����ϸ� ���ݱ��� ���� �� ������� -> 0�̸� ���� ��

	
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
void CreateAccount() {//���� ����
	system("cls");

	string acc;
	string pw;
	gotoxy(10, 8);
	cout << "������ ������ ������ �Է� : ";
	cin >> acc;
	user.setUserAcc(acc); //������ ����
	gotoxy(10, 10);
	cout << "������ ������ ��й�ȣ �Է� : ";
	cin >> pw;
	user.setUserPw(pw);
	gotoxy(14, 10);
	cout << "������ �����Ǿ����ϴ�.";
} 
void LoginAccount() {//������ ���� Ȯ��, �α����ϱ�
	system("cls");
	string acc;
	string pw;
	cout << "���� �Է� : ";
	cin >> acc;
	cout << endl;
	cout << "��й�ȣ �Է� : ";
	cin >> pw;
	user.checkUser(acc, pw);
} 
void DeleteAccount() {//���� ����

} 
void QuestionAccount() { //���� ã�� �� ����

}

//�α��� ��
int userLogin() {

	DrawLogin();
	while (true) {
		switch (SelectLogin()) { //������ �޾� �Ǵ�
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
			cout << user_name + "���� �����ֽ� ���� " << r << "�� ũ���Դϴ�! �����մϴ�";
			return 0;
		}
	}
	return 0;
}