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
	string nom = (position_->voisins_)[orientation].first;
	shared_ptr<Case> newPosition = plateau_.rechercherCaseParNom(nom);
	if (newPosition == nullptr) {
		cout << "Impossible d'aller par là bas" << endl;
	}
	else {
		position_ = newPosition;
		cout << endl;
		AfficherCase(*position_);
	}
}

bool Logique::EstValide(string entree) {
	vector<string> valides = { "N", "S", "E", "W", "n", "e", "s", "w", "look", "LOOK", "USE","use" };
	auto it = std::find(valides.begin(), valides.end(), entree);
	return (it != valides.end());
}

void Logique::AppelJoueur() {
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
	cout << "-- " + piece.nom_ +" --" << endl << piece.description_ << endl;	
	vector<string> voisins = piece.getVoisinsVisible();

	for(int i =0; i<4; i++){
		if(voisins[i] != "" ){
			cout << voisins[i] + " --> " + directionNames[i];
			cout << endl;
		}
	}
}

void Logique::LancerJeu() {
	int compteur = 0;
	AfficherCase(*position_);
	while (true) {
		AppelJoueur();
		compteur++;
	}
}


void Logique::InitialisationJeu(){
 
	plateau_.ajouterCase("Couloir", "Vous entrez dans le couloir du Restaurant Ratatouille");
	plateau_.ajouterCase("Reception", "Bienvenue, passez commande et dirigez vous dans le salon");
	plateau_.ajouterCase("Cuisine", "Hum, voici la cuisine où notre chef étoilé dévoile son talent");
	plateau_.ajouterCase("Grenier", "C'est dans ce grenier que se cache le secret de ce restaurant : les rats !");
	plateau_.ajouterCase("Salon", "Le salon est la pièce principale, vous pouvez profiter du séjour ici.");
	plateau_.ajouterCase("Cave à Vin", "La cave à vin, pièce très intéressante...");
	plateau_.ajouterCase("Catacombes", "Vous ne devriez probablement pas être là..");

	
	auto Couloir = plateau_.rechercherCaseParNom("Couloir");
	auto Recep = plateau_.rechercherCaseParNom("Reception");
	auto Cuisine = plateau_.rechercherCaseParNom("Cuisine");
	auto Grenier = plateau_.rechercherCaseParNom("Grenier");
	auto Salon = plateau_.rechercherCaseParNom("Salon");
	auto CaveVin = plateau_.rechercherCaseParNom("Cave à Vin");
	auto Catacombes = plateau_.rechercherCaseParNom("Catacombes");


	(*Couloir).AjouterVoisin("Reception", true, 0);
	(*Recep).AjouterVoisin("Couloir", true, 2);
	(*Recep).AjouterVoisin("Cuisine", true, 0);
	(*Recep).AjouterVoisin("Salon", true, 3);
	(*Salon).AjouterVoisin("Reception", true, 1);
	(*Cuisine).AjouterVoisin("Reception", true, 2);
	(*Cuisine).AjouterVoisin("Grenier", true, 0);
	(*Cuisine).AjouterVoisin("Cave à Vin", true, 1);
	(*Grenier).AjouterVoisin("Cuisine", true, 2);
	(*CaveVin).AjouterVoisin("Cuisine", true, 3);
	(*CaveVin).AjouterVoisin("Catacombes", false, 1);
	(*Catacombes).AjouterVoisin("Cave à Vin", true, 3);


	position_ = Couloir;

}





