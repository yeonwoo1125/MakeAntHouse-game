#define _CRT_SECURE_NO_WARNINGS
#include<mysql.h>
#include<iostream>
#include <cstdio>
using namespace std;

#pragma comment(lib, "libmySQL.lib")
#define DB_HOST "localhost"   //ȣ��Ʈ �̸� �Ǵ� IP �ּ�(�⺻ : localhost)
#define DB_USER "root" //MySQL login id(mysql -u ���⾲�°� -p)
#define DB_PASS "yeanwoo0619"   //�н�����
#define DB_NAME "makeAntHouse_db"   //�����ͺ��̽� �̸�
#define CHOP(x) x[strlen(x)-1] = ' '

int main(void) {
    MYSQL* connection = NULL, conn;
    MYSQL_RES* sql_result;
    MYSQL_ROW sql_row;
    int query_stat;
    char acc[40];
    char pw[40];
    char acc_ans[40];
    char pw_anw[40];
    char nickName[40];
    char houseSize[5];
    char query[255];
    char name[20];

    mysql_init(&conn);

    //Mysql �����ͺ��̽� �������� ���� �õ�.
    connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);

    //C++�� mysql�� �������� �ʾ��� ��� �����޼���
    //con���� : MYSQL* ���� �ڵ� (= ù ��° �Ķ����)/����: NULL
    if (connection == NULL) {
        //fprintf -> stderr�� ����Ϳ� ���� �޼����� �����ִ� �ڵ�(������ ���Ͽ� �ۼ��ϴ� �ڵ�)
        //mysql_error�� ���� mysql���� ������ error�� �ٷ� �� �� �ִ�.
        fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
        return 1;
    }

    //mysql_query�Լ� : mysql�ܼ�â�� ���� ��ɾ �Է��ϴ� �Լ�
    //select�� => �ܼ�â�� ���
    query_stat = mysql_query(connection, "select * from login_user");
    if (query_stat != 0) {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    //mysql�� ���� ����� �����Ѵ�.(��ü��)
    sql_result = mysql_store_result(connection);

    //printf("ID ��й�ȣ\n");

    //���� ����� ���پ� �ҷ��� �ܾ� �ϳ��ϳ��� ������. ���� ������ 0, ������ �����Ͱ� ->> ���ܾ �迭�� ����
    while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
        for (int i = 0; i < 7; i++)
            printf("%s \n", sql_row[i]);   //���
    }

    //mysql_store_result�� ���� �޸𸮸� ��ü��Ŵ-> ��ġ malloc�� free����
    mysql_free_result(sql_result);

    //���� ����
    printf("\nInsert value \n");
    printf("���̵� : ");
    fgets(acc, 40, stdin);
    //�Է¹��� ���ڿ��� �� �κ� ������ ������ �� ����� �����ִ� ����
    CHOP(acc);

    printf("��й�ȣ :");
    fgets(pw, 40, stdin);
    CHOP(pw);

    printf("���̵� ��Ʈ :");
    fgets(acc_ans, 40, stdin);
    CHOP(acc_ans);

    printf("��� ��Ʈ :");
    fgets(pw_anw, 40, stdin);
    CHOP(pw_anw);

    printf("�̸� :");
    fgets(name, 20, stdin);
    CHOP(name);

    printf("���� :");
    fgets(nickName, 40, stdin);
    CHOP(nickName);


    //db���� �ۼ�
    //sprint : query�� "insert into login values ('%s', '%s')", name, passwor������ ����
    sprintf(query, "insert into login_user(user_acc, user_pw, user_acc_ans, user_pw_ans,user_name, user_nickname) values ('%s', '%s','%s','%s','%s','%s')", acc, pw, acc_ans, pw_anw, name, nickName);
    query_stat = mysql_query(connection, query);
    if (query_stat != 0) {
        fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
        return 1;
    }

    mysql_close(connection);
}