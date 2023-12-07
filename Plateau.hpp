#ifndef PLATEAU_HPP  // Garde d'en-tête
#define PLATEAU_HPP

#include <vector>
#include "Case.hpp"

class Plateau 
{
public:
	Plateau();
	~Plateau();
	shared_ptr<Case> rechercherCaseParNom(std::string nom);


	void ajouterCase(shared_ptr<Case> nouvelleCase);

private:
	vector<shared_ptr<Case>> cases_;
};

Plateau::Plateau()
{
}

Plateau::~Plateau()
{

}

void Plateau::ajouterCase(shared_ptr<Case> nouvelleCase) {
	cases_.push_back(nouvelleCase);
}

shared_ptr<Case> Plateau::rechercherCaseParNom(std::string nom) {
	for (auto ptrCase : cases_) {
		if (ptrCase->getNom() == nom) {
			return ptrCase;
		}
	}
}

#endif