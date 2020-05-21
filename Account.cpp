#include "Account.h"
#include "Client.h"
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

ID Account::lastID = 1;
Account* Account::sharedInstance = NULL;
std::vector<Account*> Account::AllAccounts;

ID Account::NewID() {
    Account::lastID++;
    return Account::lastID;
}

Account::Account() : balanceInBaseCurrency(0.0f), baseCurrency("RON") { // this will only get called once, when we instantiate sharedInstance
    _accountId = NewID();
    openingDate = time(0);
    _ownerID = 0;
}

Account::Account(float& b, Client& c, std::string& baseCurrency, time_t& d) :
    balanceInBaseCurrency(b), baseCurrency(baseCurrency), _ownerID(c.GetID()), openingDate(d) {
    _accountId = NewID();
}

Account::Account(float& b, Client& c, std::string& baseCurrency, Date& d) :
    balanceInBaseCurrency(b), baseCurrency(baseCurrency), _ownerID(c.GetID()), openingDate(d.secondsSinceEpoch) {
    _accountId = Account::NewID();
}

Account::Account(ID id, float balance, std::string baseCurrency, ID ownerID, time_t opening, std::vector<ID> transactions) {
    _accountId = id;
    balanceInBaseCurrency = balance;
    baseCurrency = baseCurrency;
    _ownerID = ownerID;
    openingDate = opening;
    transactions = transactions;
}
//
//Account::Account(const Account& a) : baseCurrency(a.baseCurrency), _owner(a._owner) {
//    _accountId = a._accountId;
//    balanceInBaseCurrency = a.balanceInBaseCurrency;
//    openingDate = time(0);
//}

Account& Account::operator=(const Account& a) {
    _accountId = a._accountId;
    _ownerID = a._ownerID;
    return *this;
}

Account::~Account() {} // not deleting _owner because he or she might have other accounts

Account* Account::AutoAccount() { // this will return a shared instance
    if (sharedInstance == NULL) {
        sharedInstance = new Account(0, 100000000.00, "RON", 0, 1, std::vector<ID>());
    }
    return sharedInstance;
}

ID& Account::GetID() {
    return _accountId;
}

float Account::GetBalanceInBaseCurrency() {
    return balanceInBaseCurrency;
}

float Account::SetBalanceInBaseCurrency(float& b) {
    balanceInBaseCurrency = b;
    return b;
}

const std::string& Account::GetBaseCurrency() {
    return this->baseCurrency;
}

Client& Account::GetOwner() {
    try {
        return Client::FindClient(_ownerID);
    } catch (NotFoundException e) {
        throw e;
    }
}

void Account::SetOwner(Client& c) {
    _ownerID = c.GetID();
}

Date Account::GetOpeningDate() {
    Date d = Date(openingDate);
    return d;
}

void Account::SetOpeningDate(Date& d) {
    openingDate = d.secondsSinceEpoch;
}

void Account::SetOpeningDate(time_t t) {
    openingDate = t;
}

unsigned int Account::GetNumberOfTransactions() {
    return transactions.size();
}

std::vector<ID>& Account::GetTransactions() {
    return transactions;
}

void Account::AddTransaction(Transaction& t) {
    if (t.GetSenderAccount()->_accountId == this->_accountId) {
        transactions.push_back(t.GetID());
        balanceInBaseCurrency -= t.GetSentAmount();
        return;
    }
    if (t.GetReceiverAccount()->_accountId == this->_accountId) {
        transactions.push_back(t.GetID());
        balanceInBaseCurrency += t.GetReceivedAmount();
        return;
    }
    
    std::cout << "Transaction between invalid accounts." << "\n";
}

void Account::AddTransaction(Transaction&& t) {
    if (t.GetSenderAccount()->_accountId == this->_accountId) {
        transactions.push_back(t.GetID());
        balanceInBaseCurrency -= t.GetSentAmount();
        return;
    }
    if (t.GetReceiverAccount()->_accountId == this->_accountId) {
        transactions.push_back(t.GetID());
        balanceInBaseCurrency += t.GetReceivedAmount();
        return;
    }

    std::cout << "Transaction between invalid accounts." << "\n";
}

std::vector<Account*>& Account::GetAllAccounts() {
    return Account::AllAccounts;
}

Account& Account::FindAccount(ID id) {
    std::vector<Account*>::iterator a = std::find_if(Account::AllAccounts.begin(), Account::AllAccounts.end(), [id](Account* a1) {
        return a1->_accountId == id;
    });
    if (a != Account::AllAccounts.end()) {
        return **a;
    }
    throw NotFoundException("Account", id);
}

void Account::AddAccount(Account* a) {
    Account::AllAccounts.push_back(a);
    a->GetOwner().AddAccount(a);
}

std::istream& Account::read(std::istream& input) {
    ID ownerID;
    float balance;
    std::string baseCurrency;
    time_t t;
    std::cout << "Owner's ID | balance | currency | opening time (seconds since 1900. 0 for now)\n";
    input >> ownerID >> balance >> baseCurrency >> t;
    _ownerID = ownerID;
    balanceInBaseCurrency = balance;
    this->baseCurrency = baseCurrency;
    if (t)
        openingDate = t;
    else
        openingDate = time(0);

    Account::AddAccount(this);

    return input;
}

std::ostream& Account::print(std::ostream& output) {
    output << "Account ID: " << _accountId << ": \nOwner: " << Client::FindClient(_ownerID).GetName() << "\nBalance: " << balanceInBaseCurrency << " " << baseCurrency << "\n\tTransactions: \n";
    for (size_t i = 0; i < transactions.size(); i++) {
        try {
            output << "\t" << i+1 << ". " << Transaction::Find(transactions[i]) << "\n";
        } catch (NotFoundException nfe) {
            std::cout << nfe.what() << "\n";
        }
        
    }
    return output;
}

void Account::LoadFromFile(std::ifstream& f) { // failed experiment...
    ID id, ownerID;
    float balance;
    std::string baseCurrency;
    time_t opening;

    int lineNumber = 0;
    std::string line;
    while (std::getline(f, line)) {
        if (!(lineNumber % 2)) {
            f >> id >> balance >> baseCurrency >> ownerID >> opening;
            
        } else {
            std::istringstream is(line);
            std::vector<ID> transactions = std::vector<ID>(std::istream_iterator<ID>(is), std::istream_iterator<ID>());
            Account::AllAccounts.push_back(&Account(id, balance, baseCurrency, ownerID, opening, transactions));
        }

        lineNumber++;
    }
}

std::istream& operator>>(std::istream& input, Account& a) {
    return a.read(input);;
}

std::ostream& operator<<(std::ostream& output, Account& a) {
    return a.print(output);
}
