#pragma once

#include "Typedefs.h"
#include "Date.h"
#include <vector>
#include <istream>
#include <ostream>

class Transaction
{
private:
	static ID lastID;

	ID _transactionID;
	float amountSent, amountReceived;
	float conversionRate;
	Client* fromClient, *toClient;
	Account* fromAccount, *toAccount;
	Date transactionTime;
	bool foreignBank;

	static ID NewID();

	static std::vector<Transaction*> AllTransactions;

public:
	Transaction();
	// no copy constructor needed. We're actually copying the pointers. We want the same objects referenced
	Transaction(float& amountSent, float& conversionRate, Account* fromAccount, Account* toAccount, Date& transactionTime, bool foreignBank);

	~Transaction() = default; // We're not deleting clients, nor accounts when deleting a transaction

	ID& GetID();

	float GetSentAmount();
	float GetReceivedAmount();
	Date& GetTransactionDate();
	Account* GetSenderAccount();
	Account* GetReceiverAccount();

	static std::vector<Transaction*>& GetAllTransactions();
	static Transaction& Find(ID id);
	static void AddTransaction(Transaction& t);
	static void ClearTransactions();

	friend std::istream& operator>>(std::istream& input, Transaction& t);
	friend std::ostream& operator<<(std::ostream& output, Transaction& t);
};

