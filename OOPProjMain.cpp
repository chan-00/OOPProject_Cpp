#include<iostream>
#include<cstring>
#include<cstdlib>
#include<Windows.h>
#include "OOPProj.h"

using std::cout;
using std::cin;
using std::endl;

int main(void) {
	AccountHandler acc;
	int menu;

	while (1) {
		system("cls");
		menu = acc.ShowMenu();

		system("cls");
		if (menu == 1)
			acc.MakeAccount();
		else if (menu == 2)
			acc.Deposit();
		else if (menu == 3)
			acc.Withdraw();
		else if (menu == 4) {
			acc.PrintAll();
			Sleep(5000);
		}
		else if (menu == 5)
			break;
		else if (menu == 6)
			cout << "메뉴를 잘못 입력했습니다, 다시 똑바로 입력해 주세요." << endl;

		Sleep(2000);
	}
	cout << "프로그램이 종료됩니다...." << endl;

	return 0;
}