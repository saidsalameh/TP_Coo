#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;


/*class Departement{

	int numero;
	float prix_m2;
	
	public:
		Departement(json& data){data["numero"];data["prix_m2"];}
		Departement(int id){
			cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/Departement/"+ std::to_string(id)}); 
			json j =json::parse(r.text);
			numero = j["numero"];
			prix_m2 = j["prix_m2"];
		}
	
		friend std::ostream& operator << (
			std::ostream& out, const Departement& p) {
		  	return out << "Numero de Departement : " << p.numero << " / " << "Prix en m² : " << p.prix_m2; 
		}
}; */
// Modifictaion le 26/11

// Class Departement 

class Departement{

	public:
		int numero_Departement;
		float prix_m2_Departement;
		Departement(int numero,int prix_m2):numero_Departement(numero), prix_m2_Departement(prix_m2){}
		Departement(json data):numero_Departement(data["numero"]), prix_m2_Departement(data["prix_m2"]){}
		Departement(int id){
		std::string link = "http://localhost:8000/Departement/" + 		std::to_string(id);
		cpr::Response r  = cpr::Get(cpr::Url(link));
		json data = json::parse(r.text);
		numero_Departement = data["numero"]; prix_m2_Departement = data["prix_m2"];
		}
/*		
		void afficher(){
	std::cout << "numero : " << this->numero_Departement << std::endl;
	std::cout << "prixm2 : " << this->prix_m2_Departement<< std::endl;}
	
*/		
		friend std::ostream& operator << (
			std::ostream& out, const Departement& p) {
		  	return out << "Numero de Departement : " << p.numero_Departement << " / " << "Prix en m² : " << p.prix_m2_Departement; }
		
};


//Departement::Departement(int numero, int prixm2) : numero_Departement(numero), prixm2_Departement(prixm2){}
//Departement::Departement(json data) : numero_Departement(data["numero"]), prixm2_(data["prixm2"]){}
/*Departement::Departement(int id)
{
	std::string link = "http://localhost:8000/departement/" + std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	numero_Departement = data["numero"]; prixm2_Departement = data["prixm2"];
}
*/
// Class Ingredient

class Ingredient{

	public :
		
		Ingredient(int id){
	std::string link = "http://localhost:8000/Ingredients/" + std::to_string(id);
	std::cout<<link<<std::endl;
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	nom_Ingredient = data["nom"];
}
		std::string nom_Ingredient;
		friend std::ostream& operator << (
			std::ostream& out, const Ingredient& p) {
		  	return out << "Nom Ingredient : " << p.nom_Ingredient; }

};

// Constructeur Ingredient

/*Ingredient::Ingredient(int id){
	std::string link = "http://localhost:8000/ingredient/" + std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	nom_Ingredient = data["nom"];
}
*/
// Class Prix
class Prix
{
	public :
		Prix(int id){
	std::string link = "http://localhost:8000/prix/" + std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	ingredient = std::make_unique<Ingredient>(data["ingredient"]); 
	departement = std::make_unique<Departement>(data["departement"]);
	prix_P = data["prix"];
}
		
		std::unique_ptr<Ingredient> ingredient;
		std::unique_ptr<Departement> departement;
		int prix_P;
		std::string nom_Ingredient;
		friend std::ostream& operator << (
			std::ostream& out, const Prix& p) {
		  	return out << "Prix : " << p.prix_P; }
		
};

// Constructeur Prix

/*Prix::Prix(int id)
{
	std::string link = "http://localhost:8000/prix/" + std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	ingredient_ = std::make_unique<Ingredient>(fich["ingredient"]); 
	departement_ = std::make_unique<Departement>(fich["departement"]);
	prix_P = data["prix"];
}
*/
// Class Machine 

class Machine
{
	public :
		Machine(int id){
	std::string link = "http://localhost:8000/machine/" + std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	nom_Machine = data["nom"]; prix_Machine = data["prix"];
}
	
		std::string nom_Machine;
		int prix_Machine;
		friend std::ostream& operator << (
			std::ostream& out, const Machine& p) {
		  	return out << "Prix : " << p.nom_Machine; }
		
};

// Constructeur Machine 

/*Machine::Machine(int id)
{
	std::string link = "http://localhost:8000/machine/" + std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	nom_Machine = data["nom"]; prix_Machine = data["prix"];
}
*/
// Class Quantite Ingredient

class QuantiteIngredient
{
	public :
		QuantiteIngredient(int id){
	std::string link = "http://localhost:8000/quantiteingredient/" + 		std::to_string(id);
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

// Constructeur QuantiteIngredient

/*QuantiteIngredient::QuantiteIngredient(int id)
{
	std::string link = "http://localhost:8000/quantiteingredient/" + 		std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	ingredient_ = std::make_unique<Ingredient>(fich["ingredient"]); 
	quantite_Ingredient = data["quantite"];
}
*/
// Class Action 

class Action
{
	std::unique_ptr<Machine> machine_A;
		std::string commande_A;
		int duree_A;
		std::unique_ptr<QuantiteIngredient> ingredients_A;
		std::unique_ptr<Action> action1;
	public :
		Action(int id){
		std::string link = "http://localhost:8000/action/" + std::to_string(id);
		cpr::Response r  = cpr::Get(cpr::Url(link));
		json data = json::parse(r.text);
		machine_A = std::make_unique<Machine>(data["machine"]); 
		commande_A = data["commande"];
		duree_A = data["duree"];
		ingredients_A = std::make_unique<QuantiteIngredient>(data["ingredients"]); 
		action1 = std::make_unique<Action>(data["action"]); 
	
	
}
/*		friend std::ostream& operator << (
		std::ostream& out, const Action& p) {
		return out << "machine_A : " << p.machine_A << " / " << "commande_A : " << p.commande_A << " / " <<  "duree_A : " << p.duree_A << " / " << "action1 : " << p.action1 ; }
		
		//std::optional<std::unique_ptr<Action>> action_A;*/		
};

// Constructeur Action
/*
Action::Action(int id)
{
	std::string link = "http://localhost:8000/action/" + std::to_string(id);
	cpr::Response r  = cpr::Get(cpr::Url(link));
	json data = json::parse(r.text);
	machine_A = std::make_unique<Machine>(data["machine"]); 
	commande_A = data["commande"];
	duree_A = data["duree"];
	ingredients_A = std::make_unique<QuantiteIngredient>(data["ingredients"]); 
	action1 = std::make_unique<Action>(data["action"]); 
}
*/
// Class Recette

class Recette
{
	public :
		Recette(int id);
	
		std::string nom_Recette;
		std::unique_ptr<Action> action_Recette;	
		
};

// Constructeur Recette



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


// Fin modifictaion du 26/11

auto main() -> int{
	
	//std::cout << Departement{46,1750} << "\n"; 
	cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/Departement/3"});
	json data =json::parse(r.text);
	std::cout << "Reponse HTTP :" << std::endl;
    	std::cout << r.text << "\n";   
	Departement d{3};
	Ingredient I{6};
	Prix P{15};
	Machine M{3};
	
	
	std::cout << "I : " << I << std::endl;
	std::cout << "P : " << P << std::endl;
	std::cout << "M : " << M << std::endl;
	std::cout << "d : " << d << std::endl;
	
	/*std::cout << "Dep num : " << numero1 << std::endl;
	std::cout <<  "Dep prix : " << prix << std::endl;
	std::cout << j;*/
	
	
	return 0;
}




/* class Departement{
1
	int numero;
	float prix_m2;
	int id;
	json data;
	public:
		Departement(int x,float y) : numero{x}, prix_m2{y} {}
		friend std::ostream& operator << (
			std::ostream& out, const Departement& p) {
		  return out << "Numero de Departement : " << p.numero << " / " << "Prix en m² : " << p.prix_m2; 
		}
		
		data ()
		void to_json(json& data, const Departement& p) {
        data = json{{"numero", p.numero}, {"prix par m² ", p.prix_m2}};
        }

}; */


