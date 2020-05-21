#include "ChargeAccount.h"

void ChargeAccount::SetFreeTransactions(unsigned short &ftl) {
	freeTransactionsLeft = ftl;
}

unsigned short& ChargeAccount::GetFreeTransactionsLeft() {
	return freeTransactionsLeft;
}

void ChargeAccount::AddTransaction(Transaction& t) {
	Account::AddTransaction(t);
	if (freeTransactionsLeft > 0) {
		this->GetTransactions().push_back(t.GetID());
		freeTransactionsLeft--;
	} else {
		this->GetTransactions().push_back(t.GetID());
		float commission = t.GetSentAmount() * 0.25f;
		float conversionRate = 1.0f;
		float currentBalance = GetBalanceInBaseCurrency() - commission;
		SetBalanceInBaseCurrency(currentBalance);
	}
}

void ChargeAccount::AddTransaction(Transaction&& t) {}

std::istream& ChargeAccount::read(std::istream& input) {
	Account::read(input);
	input >> freeTransactionsLeft;
	return input;
}

std::ostream& ChargeAccount::print(std::ostream& output) {
	Account::print(output);
	output << "Free transactions left: " << freeTransactionsLeft << "\n";
	return output;
}
