#pragma once
#include "Typedefs.h"
#include "Transaction.h"

#include <ctime>
#include <string>
#include <vector>
#include <istream>
#include <ostream>

class Account
{
private:
    static ID lastID;
    ID _accountId;
    float balanceInBaseCurrency;
    std::string baseCurrency;
    ID _ownerID;
    time_t openingDate; // seconds since Epoch
    std::vector<ID> transactions;

    static Account* sharedInstance;

    static ID NewID();

    static std::vector<Account*> AllAccounts;


    Account(const Account& a);
    Account(ID id, float balance, std::string baseCurrency, ID ownerID, time_t opening, std::vector<ID> transactions);

public:
    Account();
    Account(float& b, Client& c, std::string& baseCurrency, time_t& d);
    Account(float& b, Client& c, std::string& baseCurrency, Date& d);
    Account& operator=(const Account& a);

    virtual ~Account();

    static Account* AutoAccount();

    ID& GetID();

    float GetBalanceInBaseCurrency();
    float SetBalanceInBaseCurrency(float& b);
    const std::string& GetBaseCurrency();

    Client& GetOwner();
    void SetOwner(Client& c);

    Date GetOpeningDate();
    void SetOpeningDate(Date& d);
    void SetOpeningDate(time_t t);

    unsigned int GetNumberOfTransactions();
    std::vector<ID>& GetTransactions();
    virtual void AddTransaction(Transaction& t);
    virtual void AddTransaction(Transaction&& t);

    static std::vector<Account*>& GetAllAccounts();
    static Account& FindAccount(ID id);
    static void AddAccount(Account* a);

    virtual std::istream& read(std::istream& input);
    virtual std::ostream& print(std::ostream& output);

    static void LoadFromFile(std::ifstream& f);

    friend std::istream& operator>>(std::istream& input, Account& a);
    friend std::ostream& operator<<(std::ostream& output, Account& a);
};