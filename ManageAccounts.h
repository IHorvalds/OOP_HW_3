#pragma once
#include "SavingsAccount.h"
#include "ChargeAccount.h"
#include "Client.h"

#include <ostream>
#include <unordered_map>
#include <vector>

template <class T>
class ManageAccounts
{
private:
	std::unordered_map<ID, std::vector<T*>> map;
public:
	ManageAccounts();
	std::ostream& print(std::ostream& output);
	std::unordered_map<ID, std::vector<T*>> GetMap();
	template <class T>
	friend std::ostream& operator<<(std::ostream& output, ManageAccounts<T>& ma);
};

template <>
class ManageAccounts<SavingsAccount>
{
private:
	std::unordered_map<ID, std::vector<SavingsAccount*>> map;
public:
	ManageAccounts();
	std::unordered_map<ID, std::vector<SavingsAccount*>> GetMap();
	/*template <class T>
	friend std::ostream& operator<<(std::ostream& output, ManageAccounts<SavingsAccount>& ma);*/
};

template <class T>
inline ManageAccounts<T>::ManageAccounts() {
	for (auto a : Account::GetAllAccounts()) {
		T* t_account = dynamic_cast<T*>(a);
		if (t_account) {
			if (map.find(t_account->GetOwner().GetID()) != map.end()) {
				map[t_account->GetOwner().GetID()].push_back(t_account);
			} else {
				map[t_account->GetOwner().GetID()] = std::vector<T*>({ t_account });
			}
		}
	}
}

inline ManageAccounts<SavingsAccount>::ManageAccounts() {
	for (auto a : Account::GetAllAccounts()) {
		SavingsAccount* t_account = dynamic_cast<SavingsAccount*>(a);
		if (t_account) {
			if (map.find(t_account->GetOwner().GetID()) != map.end()) {
				map[t_account->GetOwner().GetID()].push_back(t_account);
			} else {
				map[t_account->GetOwner().GetID()] = std::vector<SavingsAccount*>({ t_account });
			}
		}
	}
}

template<class T>
inline std::ostream& ManageAccounts<T>::print(std::ostream& output) {
	for (auto a : map) {
		output << Client::FindClient(a.first).GetName() << "\n";
		for (auto ac : a.second) {
			output << *ac << "\n";
		}
	}
	return output;
}

template<class T>
inline std::unordered_map<ID, std::vector<T*>> ManageAccounts<T>::GetMap() {
	return map;
}

inline std::unordered_map<ID, std::vector<SavingsAccount*>> ManageAccounts<SavingsAccount>::GetMap() {
	return map;
}

template<class T>
inline std::ostream& operator<<(std::ostream& output, ManageAccounts<T>& ma) {
	for (auto a : ma.GetMap()) {
		output << Client::FindClient(a.first).GetName() << "\n";
		for (auto ac : a.second) {
			output << *ac << "\n";
		}
	}
	return output;
}


inline std::ostream& operator<<(std::ostream& output, ManageAccounts<SavingsAccount>& ma) {
	for (auto a : ma.GetMap()) {
		for (auto ac : a.second) {
			if (ac->GetExpiry() == twelve) {
				output << *ac << "\n";
			}
		}
	}
	return output;
}