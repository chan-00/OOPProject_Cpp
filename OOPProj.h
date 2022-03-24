#ifndef __OOPProj__
#define __OOPProj__

enum {ratingA = 7, ratingB = 4, ratingC = 2};
#include "BoundCheckArray.h"
#include "StringClass.h"

class MinZero {
public:
	void report();
};

class ConMoney {		//계좌 잔고보다 더 많은 돈을 출금할 때 예외처리
public:
	void report();
};

class Account {
private:
	//계좌id, 잔액, 고객이름 변수
	int id;
	int money;
	String name;
public:
	Account();
	Account(int id, int money, const char* cname);
	Account(const Account& acc);
	Account& operator=(const Account& acc);
	void SetID(int id);
	virtual void SetMoney(int money) = 0;
	void Set(int money);
	void SetName(const char* name);
	int GetID() const;
	int GetMoney() const;
	virtual void GetMoney(int money) = 0;
	String GetName() const;
};

class AccountHandler {
private:
	AccArray<Account*> acc;
	int accLen;
	int selectAccount;
public:
	AccountHandler();
	int ShowMenu();
	void MakeAccount();
	void MakeNormalAccount();
	void MakeHighCreditAccount();
	void Deposit();
	void Withdraw();
	void PrintAll() const;
	~AccountHandler();
};

class NormalAccount :public Account {
private:
	int interest;		//이자율
public:
	NormalAccount(int id, int money, const char* name, int cinterest);
	void SetMoney(int money);
	void GetMoney(int money);
};

class HighCreditAccount :public Account {
private:
	int interest;		//이자율
	int rating;			//신용 등급
public:
	HighCreditAccount(int id, int money, const char* name, int cinterest, int crating);
	void SetMoney(int money);
	void GetMoney(int money);
};

#endif