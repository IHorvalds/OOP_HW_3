#include <iostream>
#include "Client.h"
#include "SavingsAccount.h"
#include "ChargeAccount.h"
#include "ManageAccounts.h"

int main()
{
    std::cout << "Welcome to Hello World Bank!\n";
    Client* GNB = Client::GetBankClient();
    Client::AddClient(GNB);
    Account* GNBAccount = Account::AutoAccount();
    Account::AddAccount(GNBAccount);
    int command;
    bool should_continue = true;
    do {
        std::cout << "Meniu:\n";
        std::cout << "0. Exit.\n";
        std::cout << "1. Add a client.\n";
        std::cout << "2. Add a savings account.\n";
        std::cout << "3. Add a charge account.\n";
        std::cout << "4. Perform a transaction.\n";
        std::cout << "5. Print clients.\n";
        std::cout << "6. Find client by id.\n";
        std::cout << "7. Print all accounts.\n";
        std::cout << "8. Print savings accounts.\n";
        std::cout << "9. Print charge accounts.\n";
        std::cout << "10. Find account by id.\n";
        std::cout << "11. Print a client's transactions.\n";

        std::cin >> command;
        switch (command) {
        case 0:
        should_continue = false;
        std::cout << "Bye.\n";
        break;

        case 1:
        {
            Client * c = new Client();
            std::cin >> *c;
            Client::AddClient(c);
            std::cout << *c << "\n";
        }
        break;

        case 2:
        {
            SavingsAccount* sa = new SavingsAccount();
            std::cin >> *sa;
            std::cout << *sa << "\n";
        }
        break;

        case 3:
        {
            ChargeAccount *ca = new ChargeAccount();
            std::cin >> *ca;
            std::cout << *ca << "\n";
        }
        break;

        case 4:
        {
            Transaction *t = new Transaction();
            std::cin >> *t;
            Transaction::AddTransaction(*t);
            std::cout << *t << "\n";
        }
        break;

        case 5:
        {
            for (auto c : Client::GetAllClients()) {
                std::cout << *c << "\n";
            }
        }
        break;

        case 6:
        {
            ID i;
            std::cout << "Type an ID to search for: ";
            std::cin >> i;
            try {
                std::cout << Client::FindClient(i) << "\n";
            } catch (NotFoundException nfe) {
                std::cout << nfe.what() << "\n";
            }
        }
        break;

        case 7:
        {
            for (auto a : Account::GetAllAccounts()) {
                std::cout << *a << "\n";
            }
        }
        break;

        case 8:
        {
            ManageAccounts<SavingsAccount> mas;
            std::cout << mas << "\n";
        }
        break;

        case 9:
        {
            ManageAccounts<ChargeAccount> mac;
            std::cout << mac << "\n";
        }
        break;

        case 10:
        {
            try {
                ID id;
                std::cin >> id;
                std::cout << Account::FindAccount(id) << "\n";
            } catch (NotFoundException nfe2) {
                std::cout << nfe2.what();
            }
        }
        break;

        case 11:
        {
            ID id;
            std::cout << "Client's ID: ";
            std::cin >> id;
            Client& c = Client::FindClient(id);
            std::cout << c.GetName() << "\n";
            for (auto a : c.GetAccounts()) {
                std::cout << *a << "\n";
            }
        }
        break;
        }
    } while (should_continue);

    Client::ClearClients(); // also clears all accounts
    Transaction::ClearTransactions();
    

    return 0;
}
