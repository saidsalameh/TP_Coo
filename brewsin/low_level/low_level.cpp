#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>


using json = nlohmann::json;


class Departement{

	int numero;
	float prix_m2;
	
	public:
		//Departement(int x,float y) : numero{x}, prix_m2{y} {}
		
		//Departement(json& data):data{"numero"},data{"prix_m2"}{}
		Departement(json& data){data["numero"];data["prix_m2"];}
		Departement(int& id){
		cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/Departement/"+ std::string id}); 
		}
		
		friend std::ostream& operator << (
			std::ostream& out, const Departement& p) {
		  return out << "Numero de Departement : " << p.numero << " / " << "Prix en m² : " << p.prix_m2; 
		}

		void to_json(json& data, const Departement& p) {
        data = json{{"numero", p.numero}, {"prix par m² ", p.prix_m2}};
        }
}



auto main() -> int{
	
	//std::cout << Departement{46,1750} << "\n"; 
	cpr::Response r = cpr::Get(cpr::Url{"http://localhost:8000/Departement/1"});
	json j =json::parse(r.text);
	
	Departement{j};
	
	/*std::cout << "Dep num : " << numero1 << std::endl;
	std::cout << "Dep prix : " << prix << std::endl;
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
