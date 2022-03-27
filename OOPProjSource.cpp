#include<iostream>
#include<cstring>
#include "OOPProj.h"

using std::cout;
using std::cin;
using std::endl;

void MinZero::report() {
	cout << "입력한 돈의 액수가 0보다 작습니다." << endl;
}

void ConMoney::report() {
	cout << "계좌의 잔액이 부족합니다....." << endl;
}

Account::Account() {
	id = 0;
	money = 0;
}

Account::Account(int id, int money, const char* cname) {
	this->id = id;
	this->money = money;
	name.SetString(cname);
}

Account::Account(const Account& acc):id(acc.id), money(acc.money) {
	name.SetString(acc.name);
}

Account& Account::operator=(const Account& acc) {
	id = acc.GetID();
	money = acc.GetMoney();
	name.SetString(acc.name);

	return *this;
}

void Account::SetID(int id) {
	this->id = id;
}

void Account::Set(int money) {
	this->money = money;
}

void Account::SetName(const char* name) {
	this->name.SetString(name);
}

int Account::GetID() const {
	return id;
}

int Account::GetMoney() const {
	return money;
}

String Account::GetName() const {
	return name;
}

NormalAccount::NormalAccount(int id, int money, const char* name, int cinterest):Account(id, money, name), interest(cinterest) {}

void NormalAccount::SetMoney(int money) {
	if (money >= 0) {
		money += (int)(money * ((double)interest / 100));
		Account::Set(Account::GetMoney() + money);
		cout << money;
	}
	else
		throw MinZero();
}

void NormalAccount::GetMoney(int money) {
	if (money >= 0) {
		if (Account::GetMoney() - money >= 0) {
			Account::Set(Account::GetMoney() - money);
			cout << money << "원 만큼 출금되었고, 잔액은 " << Account::GetMoney() << "원 만큼 남았습니다." << endl;
		}
		else
			throw ConMoney();
	}
	else
		throw MinZero();
}

HighCreditAccount::HighCreditAccount(int id, int money, const char* name, int cinterest, int crating):Account(id, money, name), interest(cinterest), rating(crating) {}

void HighCreditAccount::SetMoney(int money) {
	if (money >= 0) {
		switch (rating) {
		case 1:
			money += (int)(money * ((double)(interest + ratingA) / 100));
			break;
		case 2:
			money += (int)(money * ((double)(interest + ratingB) / 100));
			break;
		case 3:
			money += (int)(money * ((double)(interest + ratingC) / 100));
		}
		Account::Set(Account::GetMoney() + money);
		cout << money;
	}
	else
		throw MinZero();
}

void HighCreditAccount::GetMoney(int money) {
	if (money >= 0) {
		if (Account::GetMoney() - money >= 0) {
			Account::Set(Account::GetMoney() - money);
			cout << money << "원 만큼 출금되었고, 잔액은 " << Account::GetMoney() << "원 만큼 남았습니다." << endl;
		}
		else
			throw ConMoney();
	}
	else
		throw MinZero();
}

AccountHandler::AccountHandler(): accLen(0) {}

int AccountHandler::ShowMenu() {
	int menu;

	cout << "-----Menu-----" << endl;
	cout << "1. 계좌 개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
	cout << "선택 : ";
	cin >> menu;

	return (menu >= 1 && menu <= 5) ? menu : 6;
}

void AccountHandler::MakeAccount() {
	int selectAccount;

	if (accLen >= 50)
		cout << "현재 만들어진 계좌의 수가 최대치(50개)가 넘어가므로 새로 계좌를 만들 수 없습니다....";
	else {
		cout << "[계좌종류선택]" << endl;
		cout << "1. 보통예금계좌  2. 신용신뢰계좌" << endl << "선택 : ";
		cin >> selectAccount;

		if (selectAccount == 1)
			MakeNormalAccount();
		else if (selectAccount == 2)
			MakeHighCreditAccount();

		cout << "계좌가 생성되었습니다...." << endl;
	}
}

void AccountHandler::MakeNormalAccount() {
	char name[15];
	int id, money, interest, rating;		//계좌id, 입금액, 이자율, 신용등급값

	cout << "[보통예금계좌 개설]" << endl << "계좌ID : ";
	cin >> id;
	cout << "이름 : ";
	cin >> name;
	cout << "입금액 : ";
	cin >> money;
	cout << "이자율 : ";
	cin >> interest;

	acc[accLen++] = new NormalAccount(id, money, name, interest);
}

void AccountHandler::MakeHighCreditAccount() {
	char name[15];
	int id, money, interest, rating;		//계좌id, 입금액, 이자율, 신용등급값

	cout << "[신용신뢰계좌 개설]" << endl << "계좌ID : ";
	cin >> id;
	cout << "이름 : ";
	cin >> name;
	cout << "입금액 : ";
	cin >> money;
	cout << "이자율 : ";
	cin >> interest;
	cout << "신용등급(1toA, 2toB, 3toC) : ";
	cin >> rating;

	acc[accLen++] = new HighCreditAccount(id, money, name, interest, rating);
}

void AccountHandler::Deposit() {
	char name[15];
	int money, i;
	cout << "입금할 계좌의 고객명을 입력해 주세요. : ";
	cin >> name;

	for (i = 0; i < accLen; i++)
		if (strcmp(acc[i]->GetName().GetString(), name) == 0)
			break;
	
	if (i >= accLen)
		cout << "검색한 이름으로 만들어진 계좌가 없습니다.....";
	else {
		try {
			cout << "[입 금]" << endl << "입금액 : ";
			cin >> money;
			acc[i]->SetMoney(money);
			cout << "원 만큼 검색한 고객님의 계좌로 입금되었습니다." << endl;
		}
		catch (MinZero& m) {
			m.report();
		}
	}
}

void AccountHandler::Withdraw() {
	char name[15];
	int money, i;
	cout << "출금할 계좌의 고객명을 입력해 주세요. : ";
	cin >> name;

	for (i = 0; i < accLen; i++)
		if (strcmp(acc[i]->GetName().GetString(), name) == 0)
			break;

	if (i >= accLen)
		cout << "검색한 이름으로 만들어진 계좌가 없습니다.....";
	else {
		try {
			cout << "[출 금]" << endl << "출금액 : ";
			cin >> money;
			acc[i]->GetMoney(money);
		}
		catch (MinZero& m) {
			m.report();
		}
		catch (ConMoney& c) {
			c.report();
		}
	}
}

void AccountHandler::PrintAll() const {
	cout << "<계좌 정보 출력>" << endl << endl;
	for (int i = 0; i < accLen; i++) {
		cout << "[계좌 " << i + 1 << "번]" << endl;
		cout << "계좌ID : " << acc[i]->GetID() << endl;
		cout << "고객명 : " << acc[i]->GetName().GetString() << endl;
		cout << "잔액 : " << acc[i]->GetMoney() << endl << endl;
	}
}

AccountHandler::~AccountHandler() {
	for (int i = 0; i < accLen; i++)
		delete acc[i];
}