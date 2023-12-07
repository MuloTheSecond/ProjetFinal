#include <vector>
#include <iostream>
#include "Plateau.hpp"
#include "Case.hpp"
#include <string>
#include <unordered_map>

// Gameplay + affichages
class Logique
{
public:
	Logique();
	~Logique();
	void InitialisationJeu();
	void AfficherCase(Case piece);
	void MajUI(string entree);
	bool EstValide(string entree);
	void AppelJoueur();
	void Avancer(string direction);
	void LancerJeu();


private:
	Plateau plateau_;
	shared_ptr<Case> position_;
	unordered_map<int, string> directionNames = {
		{0, "Nord (N)"},
		{1, "Est (E)"},
		{2, "Sud (S)"},
		{3, "Ouest (O)"}
	};

	unordered_map<string, int> directions = {
		{"N",0},
		{"E",1},
		{"S",2},
		{"O",3},
		{"n",0},
		{"e",1},
		{"s",2},
		{"o",3}
	};
};

Logique::Logique()
{
}

Logique::~Logique()
{
}

void Logique::Avancer(string direction) {
	int orientation = directions[direction];
	shared_ptr<Case> newPosition = position_->getVoisins()[orientation].first;
	if (newPosition == nullptr) {
		cout << "Impossible d'aller par là bas" << endl;
	}
	else {
		position_ = newPosition;
	}

}

bool Logique::EstValide(string entree) {
	vector<string> valides = { "N", "S", "E", "W", "n", "e", "s", "w", "look", "LOOK", "USE","use" };
	auto it = std::find(valides.begin(), valides.end(), entree);
	return (it != valides.end());
}

void Logique::AppelJoueur() {
	AfficherCase(*position_);
	string commande;
	cout << "> ";
	cin >> commande;
	if (EstValide(commande)) {
		if (commande.size() == 1) {
			Avancer(commande);
		}
		else if (commande == "look" || commande == "LOOK") {
			AfficherCase(*position_);
		}
	}
}

void Logique::AfficherCase(Case piece){
	cout << "-- " + piece.getNom() +" --" << endl << piece.getDescription() << endl;	
	vector<shared_ptr<Case>> voisins = piece.getVoisinsVisible();

	for(int i =0; i<4; i++){
		if(voisins[i] != nullptr ){
			cout << voisins[i]->getNom() + " --> " + directionNames[i];

			cout << endl;
		}
	}
}

void Logique::LancerJeu() {
	while (true) {
		AppelJoueur();
	}
}


void Logique::InitialisationJeu(){
 
	shared_ptr<Case> Couloir = make_shared<Case>("Couloir", "Vous entrez dans le couloir du Restaurant Ratatouille");
	shared_ptr<Case> Recep = std::make_shared<Case>("Reception", "Bienvenue, passez commande et dirigez vous dans le salon");
	shared_ptr<Case> Cuisine = std::make_shared<Case>("Cuisine", "Hum, voici la cuisine où notre chef étoilé dévoile son talent");
	shared_ptr<Case> Grenier = std::make_shared<Case>("Grenier", "C'est dans ce grenier que se cache le secret de ce restaurant : les rats !");
	shared_ptr<Case> Salon = std::make_shared<Case>("Salon", "Le salon est la pièce principale, vous pouvez profiter du séjour ici.");
	shared_ptr<Case> CaveVin = std::make_shared<Case>("Cave à Vin", "La cave à vin, pièce très intéressante...");
	shared_ptr<Case> Catacombes = std::make_shared<Case>("Catacombes", "Vous ne devriez probablement pas êre là..");


	plateau_.ajouterCase(Couloir);
	plateau_.ajouterCase(Recep);
	plateau_.ajouterCase(Cuisine);
	plateau_.ajouterCase(Grenier);
	plateau_.ajouterCase(Salon);
	plateau_.ajouterCase(CaveVin);
	plateau_.ajouterCase(Catacombes);
	

	(*Couloir).AjouterVoisin(Recep, true, 0);
	(*Recep).AjouterVoisin(Couloir, true, 2);
	(*Recep).AjouterVoisin(Cuisine, true, 0);
	(*Recep).AjouterVoisin(Salon, true, 3);
	(*Salon).AjouterVoisin(Recep, true, 1);
	(*Cuisine).AjouterVoisin(Recep, true, 2);
	(*Cuisine).AjouterVoisin(Grenier, true, 0);
	(*Cuisine).AjouterVoisin(CaveVin, true, 1);
	(*Grenier).AjouterVoisin(Cuisine, true, 2);
	(*CaveVin).AjouterVoisin(Cuisine, true, 3);
	(*CaveVin).AjouterVoisin(Catacombes, false, 1);
	(*Catacombes).AjouterVoisin(CaveVin, true, 3);

	position_ = Couloir;

}





