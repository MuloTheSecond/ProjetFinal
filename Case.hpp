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

	std::string getNom() const;
	std::string getDescription() const;
	std::vector<std::pair<std::shared_ptr<Case>, bool>> getVoisins() const;

	vector<shared_ptr<Case>> getVoisinsVisible() const;
	void AjouterVoisin(const shared_ptr<Case> piece_voisine, bool visible, int direction);
	//void afficherVoisins() const;

private:
	std::string nom_;
	std::string description_;
	std::vector<std::pair<std::shared_ptr<Case>, bool>> voisins_;

	//std::vector<std::shared_ptr<Case>> voisins_ = { nullptr, nullptr, nullptr, nullptr };
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
		voisins_.push_back(std::make_pair(shared_ptr<Case>(nullptr), false));
	}
}

std::string Case::getNom() const {
	return nom_;
}

std::string Case::getDescription() const {
	return description_;
}

void Case::AjouterVoisin(const shared_ptr<Case> piece_voisine, bool visible, int direction){
	

    if (voisins_[direction].first == nullptr) {
        voisins_[direction].first = piece_voisine;
		voisins_[direction].second = visible;
    }
	else {
		throw runtime_error("La case a déjà un voisin dans cette direction.");
	}
    
}

/*void Case::AjouterVoisin(const shared_ptr<Case>& piece_voisine, int direction){
	if (voisins_[direction]==nullptr) {
		voisins_[direction] = piece_voisine;
	}

}*/

std::vector<std::pair<std::shared_ptr<Case>, bool>> Case::getVoisins() const{
	return voisins_;
}

vector<shared_ptr<Case>> Case::getVoisinsVisible() const {
	vector<shared_ptr<Case>> resultat = {nullptr,nullptr,nullptr,nullptr};
	for (int i = 0; i < 4;i++) {
		if (voisins_[i].second) {
			resultat[i]=voisins_[i].first;
		}
	}
	return resultat;
}

// Débugage
/*void Case::afficherVoisins() const {
	cout << "Voisins de la case '" << nom_ << "':" << endl;
	for (const auto& voisin : voisins_) {
		if (voisin != nullptr) {
			cout << "- " << voisin->getNom() << endl;
		}
	}
}*/

#endif
