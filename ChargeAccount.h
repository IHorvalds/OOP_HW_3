#pragma once
#include "Account.h"
class ChargeAccount :
	public Account
{
private:
	unsigned short freeTransactionsLeft = 3;
public:
	void SetFreeTransactions(unsigned short &ftl);
	unsigned short& GetFreeTransactionsLeft();

	void AddTransaction(Transaction& t) override;
	void AddTransaction(Transaction&& t) override;

	//static void LoadFromFile(std::ifstream& f);

	std::istream& read(std::istream& input) override;
	std::ostream& print(std::ostream& output) override;
};

