#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

class Departement{

	public:
		int numero_Departement;
		float prix_m2_Departement;
		Departement(int numero,int prix_m2):numero_Departement(numero), prix_m2_Departement(prix_m2){}
		//Departement(json data):numero_Departement(data["numero"]), prix_m2_Departement(data["prix_m2"]){}
		Departement(int id){
		std::string link = "http://localhost:8000/Departement/" + 		std::to_string(id);
		cpr::Response r  = cpr::Get(cpr::Url(link));
		json data = json::parse(r.text);
		numero_Departement = data["numero"]; prix_m2_Departement = data["prix_m2"];
		}
		
		friend std::ostream& operator << (
			std::ostream& out, const Departement& p) {
		  	return out << "Numero de Departement : " << p.numero_Departement << " / " << "Prix en m² : " << p.prix_m2_Departement; }
		
};




class Ingredient{

	public :
		
		Ingredient(int id){
	std::string link = "http://localhost:8000/Ingredient/" + std::to_string(id);
	cpr::Response r = cpr::Get(cpr::Url(link));
        json data = json::parse(r.text);
	nom_Ingredient = data["nom"];
}	
		std::string nom_Ingredient;
		friend std::ostream& operator << (
			std::ostream& out, const Ingredient& p) {
		  	return out << "Nom Ingredient : " << p.nom_Ingredient; }

};


class Prix
{
	public :
		Prix(int id)
		{
			std::string link = "http://localhost:8000/Prix/" + std::to_string(id);
        		cpr::Response r = cpr::Get(cpr::Url(link));
        		json data = json::parse(r.text);
			ingredient = std::make_unique<Ingredient>(data["ingredient"]); 
			departement = std::make_unique<Departement>(data["departement"]);
			Prix_ = data["prix"];
			
			
		}
	int Prix_;		
	std::unique_ptr<Ingredient>ingredient;
	std::unique_ptr<Departement>departement;
	friend std::ostream& operator << (std::ostream& out, const Prix& p) 
	{
		return out <<"departement : " << *p.departement << " / " <<" prix : " << p.Prix_ << " / " << *p.ingredient << "ingredient";
	}
		
};

class Machine
{
	public :
		Machine(int id){
	std::string link = "http://localhost:8000/Machine/" + std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	nom_Machine = data.at("nom").get<std::string>();
	prix_Machine = data.at("prix").get<int>();
	//nom_Machine = data["nom"]; 
	//prix_Machine = data["prix"];

}
	
		std::string nom_Machine; 
		int prix_Machine;
		friend std::ostream& operator << (std::ostream& out, const Machine& p) {
		  	return out << "machine: " << p.nom_Machine << "/" << "prix :" << p.prix_Machine; }
		
};

class QuantiteIngredient
{
	public :
		QuantiteIngredient(int id){
	std::string link = "http://localhost:8000/QuantiteIngredient/" + 		std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	ingredient = std::make_unique<Ingredient>(data["ingredient"]); 
	quantite_Ingredient = data["quantite"];
}
		
		std::unique_ptr<Ingredient> ingredient;
		int quantite_Ingredient;
		friend std::ostream& operator << (
			std::ostream& out, const QuantiteIngredient& p) {
		  	return out << "Prix : " << p.quantite_Ingredient; }		
};


class Action
{		
		public :
			std::unique_ptr<Machine> machine_A;
			std::string commande_A;
			int duree_A;
			std::vector<std::unique_ptr<QuantiteIngredient>> ingredients_A;
			std::optional<std::unique_ptr<Action>> action1;
			//std::unique_ptr<QuantiteIngredient> ingredients_A;
			//std::unique_ptr<Action> action1;
	
		Action(int id){
		std::string link = "http://localhost:8000/Action/" + std::to_string(id);
		cpr::Response r  = cpr::Get(cpr::Url(link));
		json data = json::parse(r.text);
		machine_A = std::make_unique<Machine>(data["machine"]); 
		commande_A = data["commande"];
		duree_A = data["duree"];
		for (const auto &ingredient: (data["ingredients"])) 
		{
		ingredients_A.push_back(std::make_unique<QuantiteIngredient>(ingredient));
		}

	
}
		friend std::ostream& operator << (
		std::ostream& out, const Action& p) {
		return out << "machine : " << p.machine_A->nom_Machine << " / " << "commande : " << p.commande_A << " / " <<  "duree : " << p.duree_A  ; }
		
	
};


class Recette
{
	public :
	
		std::string nom_Recette ;
		std::unique_ptr<Action> action1;
		Recette(int id)
		{
			std::string link = "http://localhost:8000/Recette/" + std::to_string(id);
			cpr::Response r  = cpr::Get(cpr::Url(link));
			json data = json::parse(r.text);
			nom_Recette = data["nom"];
			action1 = std::make_unique<Action>(data["action1"]);
		}
		friend std::ostream& operator << (
			std::ostream& out, const Recette& p) {
		  	return out << "Recette : " << p.nom_Recette << " / " << "Action recette : " << p.action1->commande_A; }
			
		
};


class Usine
{
	public :
		Usine(int id);
	
		std::unique_ptr<Departement> departement_Usine;
		int taille_Usine;
		std::vector<std::unique_ptr<Machine>> machines_Usine;
		std::vector<std::unique_ptr<Recette>> recettes_Usine;
		std::vector<std::unique_ptr<QuantiteIngredient>> stocks_Usine;
		
};


auto main() -> int{
	
	cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/Departement/3"});
	json data =json::parse(r.text); 
	Departement D{3};
	Ingredient I{4};
	Prix P{15};
	Machine M{3};
	Action A{4};
	Recette R{2};
	
	std::cout << "D : " << D << std::endl;
	std::cout << "I : " << I << std::endl;
	std::cout << "P : " << P << std::endl;
	std::cout << "M : " << M << std::endl;
	std::cout << "A : " << A << std::endl;
	std::cout << "R : " << R << std::endl;
	
	
	return 0;
}





