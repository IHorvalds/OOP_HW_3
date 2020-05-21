#include "SavingsAccount.h"
#include <iostream>

SavingsAccount::SavingsAccount() : Account() {
	time_t t = time(0);
	startPeriod = Date(t);
	expiry = three;
	interestRate = 0.0f;
}

SavingsAccount::SavingsAccount(float& b, Client& c, std::string& baseCurrency, time_t& d, InterestRateExpiry e, float& interestRate) : 
	Account(b, c, baseCurrency, d), expiry(e), interestRate(interestRate) {
	
	startPeriod = Date(d);
}

SavingsAccount::SavingsAccount(float& b, Client& c, std::string& baseCurrency, Date& d, InterestRateExpiry e, float& interestRate) :
	Account(b, c, baseCurrency, d), expiry(e), interestRate(interestRate), startPeriod(d) {}

Date SavingsAccount::GetExpiryDate() {
	Date d; // = startPeriod;
	time_t t = startPeriod.secondsSinceEpoch;
	switch (expiry) {
	case three:
		
		t += 60 * 60 * 24 * 90;
		d = Date(t);

	break;

	case six:
	
		t += 60 * 60 * 24 * 180; // adding 180 days

		d = Date(t);
	
	break;

	case twelve:

		t += 60 * 60 * 24 * 360; // adding 360 days

		d = Date(t);

	break;
	}
	return d;
}

void SavingsAccount::ResetStartPeriod(Date& start) {

	startPeriod = start;
}

void SavingsAccount::ResetPeriod(Date& start, InterestRateExpiry e) {

	startPeriod = start;
	expiry = e;
}

InterestRateExpiry SavingsAccount::GetExpiry() {
	return expiry;
}

float SavingsAccount::GetInterestRate() {
	return interestRate;
}

void SavingsAccount::SetInterestRate(float& x) {

	interestRate = x;
}

std::istream& SavingsAccount::read(std::istream& input) {
	Account::read(input); 
	std::cout << "Interest rate | period (3, 6, 12 months)\n";
	input >> interestRate;
	int a;
	input >> a;
	switch (a) {
	case 3:
	expiry = three;
	break;
	case 6:
	expiry = six;
	break;
	case 12:
	expiry = twelve;
	break;
	default:
	expiry = three;
	break;
	}
	return input;
}

std::ostream& SavingsAccount::print(std::ostream& output) {
	Account::print(output);
	output << "Start date: " << startPeriod.day << "." << startPeriod.month << "." << startPeriod.year << "\n";
	Date d = GetExpiryDate();
	output << "Expiry date: " << d.day << "." << d.month << "." << d.year << "\n";
	return output;
}
