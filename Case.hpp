#ifndef CASE_HPP  // Garde d'en-tête
#define CASE_HPP

#include <vector>
#include <iostream>

using namespace std;

class Case 
{
public:
	Case();
	~Case();
	Case(std::string nom, std::string description);

	vector<string> getVoisinsVisible() const;
	void AjouterVoisin(const string piece_voisine, bool visible, int direction);

private:
	friend class Logique;
	friend class Plateau;
	std::string nom_;
	std::string description_;
	std::vector<std::pair<string, bool>> voisins_;
};

Case::Case()
{
}

Case::~Case()
{
}

Case::Case(std::string nom, std::string description) : nom_(nom), description_(description) 
{
	for (int i = 0; i < 4; i++) {
		voisins_.push_back(std::make_pair("", false));
	}
}

void Case::AjouterVoisin(const string piece_voisine, bool visible, int direction) {


	if (voisins_[direction].first == "") {
	    voisins_[direction].first = piece_voisine;
	 	voisins_[direction].second = visible;
	}
	else {
	 	throw runtime_error("La case a déjà un voisin dans cette direction.");
	}
}

vector<string> Case::getVoisinsVisible() const {
	vector<string> resultat = {"","","",""};
	for (int i = 0; i < 4;i++) {
		if (voisins_[i].second) {
			resultat[i]=voisins_[i].first;
		}
	}
	return resultat;
}

#endif
