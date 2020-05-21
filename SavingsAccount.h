#pragma once
#include "Account.h"

enum InterestRateExpiry
{
	three, six, twelve
};

class SavingsAccount :
	public Account
{
private:
	float interestRate;
	Date startPeriod;
	InterestRateExpiry expiry;
	
	SavingsAccount(const SavingsAccount&);
	SavingsAccount(const SavingsAccount&&);
public:
	SavingsAccount();
	SavingsAccount(float& b, Client& c, std::string& baseCurrency, time_t& d, InterestRateExpiry e, float& interestRate);
	SavingsAccount(float& b, Client& c, std::string& baseCurrency, Date& d, InterestRateExpiry e, float& interestRate);

	Date GetExpiryDate();

	void ResetStartPeriod(Date& start);
	void ResetPeriod(Date& start, InterestRateExpiry e);
	InterestRateExpiry GetExpiry();
	float GetInterestRate();
	void SetInterestRate(float& x);

	std::istream& read(std::istream& input) override;
	std::ostream& print(std::ostream& output) override;
};

