#include "Transaction.h"
#include "Account.h"
#include "Client.h"
#include <algorithm>
#include "NotFoundException.h"
#include <iostream>

ID Transaction::lastID = 0;

ID Transaction::NewID() {
	Transaction::lastID++;
	return Transaction::lastID;
}

Transaction::Transaction() {
	_transactionID = NewID();
	amountReceived = amountSent = conversionRate = 0.0f;
	fromClient = toClient = NULL;
	fromAccount = toAccount = NULL;
	time_t t(0);
	transactionTime = Date(t);
	foreignBank = false;
}

Transaction::Transaction(float& amountSent, float& conversionRate, Account* fromAccount, Account* toAccount, Date& transactionTime, bool foreignBank) :
	conversionRate(conversionRate), foreignBank(foreignBank) {
	try {
		this->_transactionID = Transaction::NewID();
		this->amountSent = amountSent;
		this->amountReceived = amountSent * conversionRate;
		this->fromAccount = fromAccount;
		this->toAccount = toAccount;
		this->fromClient = &(fromAccount->GetOwner());
		this->toClient = &(toAccount->GetOwner());

		this->fromAccount->AddTransaction(*this);
		this->toAccount->AddTransaction(*this);
		time_t t(0);
		transactionTime = Date(t);

	} catch (NotFoundException nfe) {
		std::cout << nfe.what() << "\n";
	}
}

ID& Transaction::GetID() {
	return _transactionID;
}

float Transaction::GetSentAmount() {
	return amountSent;
}

float Transaction::GetReceivedAmount() {
	return amountReceived;
}

Date& Transaction::GetTransactionDate() {
	return transactionTime;
}

Account* Transaction::GetSenderAccount() {
	return fromAccount;
}

Account* Transaction::GetReceiverAccount() {
	return toAccount;
}

std::vector<Transaction*> Transaction::AllTransactions;
std::vector<Transaction*>& Transaction::GetAllTransactions() {
	return Transaction::AllTransactions;
}

Transaction& Transaction::Find(ID id) {
	std::vector<Transaction*>::iterator t1 = std::find_if(Transaction::AllTransactions.begin(), Transaction::AllTransactions.end(), [id](Transaction* t) {
		return t->_transactionID == id;
	});
	if (t1 != Transaction::AllTransactions.end()) {
		return **t1;
	}
	throw NotFoundException("Account", id);
}

void Transaction::AddTransaction(Transaction& t) {
	Transaction::AllTransactions.push_back(&t);
}

void Transaction::ClearTransactions() {
	for (auto t : Transaction::AllTransactions) {
		delete t;
	}
}

std::istream& operator>>(std::istream& input, Transaction& t) {
	ID from, to;
	std::cout << "Sender account ID | Receiver account ID | Amount sent | Conversion Rate | Foreign Bank";
	input >> from >> to;
	try {
		t.fromAccount = &Account::FindAccount(from);
		t.toAccount = &Account::FindAccount(to);
		t.fromClient = &t.fromAccount->GetOwner();
		t.toClient = &t.toAccount->GetOwner();
	} catch (NotFoundException nfe) {
		std::cout << nfe.what() << "\n";
	}
	input >> t.amountSent >> t.conversionRate >> t.foreignBank;
	t.amountReceived = t.amountSent * t.conversionRate;

	t.toAccount->AddTransaction(t);
	t.fromAccount->AddTransaction(t);
	return input;
}

std::ostream& operator<<(std::ostream& output, Transaction& t) {
	output << "Transferred " << t.amountSent << t.fromAccount->GetBaseCurrency() << " from account " << t.fromAccount->GetID()
		<< " to account " << t.toAccount->GetID() << "( " << t.amountReceived << t.toAccount->GetBaseCurrency() << " ) on " 
		<< t.transactionTime.day << "." << t.transactionTime.month << "." << t.transactionTime.year;
	return output;
}
