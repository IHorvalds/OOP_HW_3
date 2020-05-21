#include "Client.h"
#include "Typedefs.h"
#include <typeinfo>
#include <algorithm>
#include <unordered_map>
#include "Account.h"
#include <iostream>

ID Client::lastID = 1;

ID Client::NewID() {
    lastID++;
    return lastID;
}

Client::Client() {
    _id = NewID();
    _name = "";
    _surname = "";
}

Client::Client(std::string& name, std::string& surname) {
    _id = NewID();
    _name = name;
    _surname = surname;
}

Client::Client(const Client& c) {
    _id = c._id;
    _name = c._name;
    _surname = c._surname;

    for (Account* a : c._accounts) { // we're copying a client. They should have the same accounts
        _accounts.push_back(a);
    }
}

Client& Client::operator=(Client& c) {
    _id = c._id;
    _name = c._name;
    _surname = c._surname;

    for (Account* a : c._accounts) { // we're copying a client. They should have the same accounts
        _accounts.push_back(a);
    }
    return *this;
}

Client& Client::operator=(Client&& c) {
    _id = c._id;
    _name = c._name;
    _surname = c._surname;

    for (Account* a : c._accounts) { // we're copying a client. They should have the same accounts
        _accounts.push_back(a);
    }
    return *this;
}

Client* Client::Bank;
Client* Client::GetBankClient() {
    if (Bank == NULL) {
        std::string n = "Bank", s = "GNB";
        Bank = new Client(n, s);
        Bank->_id = 0;
    }
    return Bank;
}

Client::~Client() {
    for (Account* a : _accounts) {
        delete a;
    }
}

ID& Client::GetID() {
    return _id;
}

std::vector<Account*>& Client::GetAccounts() {
    return _accounts;
}

void Client::AddAccount(Account* a) {
    _accounts.push_back(a);
}

std::string Client::GetName() {
    return (_name + " " + _surname);
}

std::vector<Client*> Client::AllClients;
void Client::AddClient(Client* c) {
    Client::AllClients.push_back(c);
}
std::vector<Client*>& Client::GetAllClients() {
    return Client::AllClients;
}

Client& Client::FindClient(ID id) {
    std::vector<Client*>::iterator c = std::find_if(Client::AllClients.begin(), Client::AllClients.end(), [id](Client* c1) -> bool {
        return c1->_id == id;
    });

    if (c != Client::AllClients.end()) {
        return **c;
    }

    throw NotFoundException("Client", id);
}

void Client::ClearClients() {
    for (auto c : Client::AllClients) {
        delete c;
    }
}

std::istream& Client::read(std::istream& input) {
    std::cout << "Name Surname\n";
    input >> this->_name >> this->_surname;
    return input;
}

std::ostream& Client::print(std::ostream& output) {
    output << "Client " << _id << "\n";
    output << "Name: " << _name << " " << _surname << "\n";
    
    std::unordered_map<std::string, float> availableAmounts;
    for (auto a : _accounts) {
        if (availableAmounts.find(a->GetBaseCurrency()) == availableAmounts.end()) {
            availableAmounts[a->GetBaseCurrency()] = a->GetBalanceInBaseCurrency();
        } else {
            availableAmounts[a->GetBaseCurrency()] += a->GetBalanceInBaseCurrency();
        }
    }
    output << "Available balances: \n";
    for (auto a : availableAmounts) {
        output << a.second << " " << a.first << "\n";
    }

    return output;
}

Client::Client(Client&& c) noexcept {
    _id = c._id;
    _name = c._name;
    _surname = c._surname;

    for (Account* a : c._accounts) { // we're copying a client. They should have the same accounts
        _accounts.push_back(a);
    }
}

std::istream& operator>>(std::istream& input, Client& c) {
    return c.read(input);
}

std::ostream& operator<<(std::ostream& output, Client& c) {
    return c.print(output);
}
