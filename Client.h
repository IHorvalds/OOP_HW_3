#pragma once
#include <string>
#include <vector>
#include <istream>
#include <ostream>

#include "NotFoundException.h"
#include "Typedefs.h"

class Client
{
private:
    static ID lastID;
    ID _id;
    std::string _name, _surname;
    std::vector<Account*> _accounts;

    static std::vector<Client*> AllClients;
    static Client* Bank;

    static ID NewID();
public:
    Client();
    Client(std::string& name, std::string& surname);
    Client(const Client& c);
    Client(Client&& c) noexcept;
    Client& operator=(Client& c);
    Client& operator=(Client&& c);
    static Client* GetBankClient();

    ~Client();

    ID& GetID();

    std::vector<Account*>& GetAccounts();
    void AddAccount(Account* a);
    std::string GetName();

    static void AddClient(Client* c);
    static std::vector<Client*>& GetAllClients();
    static Client& FindClient(ID id);
    static void ClearClients();
    std::istream& read(std::istream& input);
    std::ostream& print(std::ostream& output);

    friend std::istream& operator>>(std::istream& input, Client& c);
    friend std::ostream& operator<<(std::ostream& output, Client& c);
};

