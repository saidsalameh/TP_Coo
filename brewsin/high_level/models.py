#Librairie à importer

from django.db import models
from json import dumps

# Create your models here.

class Departement(models.Model):
	numero = models.IntegerField()
	prix_m2 = models.IntegerField()
	
	def __str__(self):
		return str((f"Departement {self.numero}"))
	def json(self):
		return {"numero":self.numero,"prix_m2":self.prix_m2}
	def json_extended(self):
	    return self.json()
			
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#	
	 
class Ingredient(models.Model):
	nom = models.CharField(max_length=100)
	def __str__(self):
		return {self.nom}
	def json(self):
		return {"nom":self.nom}
	def json_extended(self):
		return self.json()
	
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
class QuantiteIngredient(models.Model):


	ingredient= models.ForeignKey(
					Ingredient, # ou "self"
					on_delete=models.PROTECT,
					# blank=True, null=True,
					# related_name="+",
				)	
	quantite = models.IntegerField()
	def __str__(self):
		return str((f'{self.ingredient} x{self.quantite}'))
	def costs(self,departement):
		print(f"{self=} {departement=} {self.ingredient=}")
		return self.ingredient.prix_set.get(departement__numero=departement).prix * self.quantite
	def json(self):
		return {"ingredient":self.ingredient.id,"quantite":self.quantite}
	def json_extended(self):
		return {"ingredient":self.ingredient.id,"quantite":self.quantite}	
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
class Machine(models.Model):
	nom = models.CharField(max_length=100)
	prix = models.IntegerField()
	def __str__(self):	
		return {self.nom}
	def costs(self):
		return self.prix
	def json(self):
		return {"nom":self.nom,"prix":self.prix}
	def json_extended(self):
		return self.json()
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
	
class Action(models.Model):
	machine = models.ForeignKey(
					Machine, # ou "self"
					on_delete=models.PROTECT,
					# blank=True, null=True,
					# related_name="+",
				)
	commande = models.CharField(max_length=100)
	duree = models.IntegerField()
	ingredients = models.ManyToManyField(QuantiteIngredient)
	action1 = models.ForeignKey(
					"self",
					on_delete=models.PROTECT,
					blank=True, null=True,
					# related_name="+",
				)
	def __str__(self):	
		return f"{self.commande}"
	def json(self):
		#return {"machine":self.machine.id,"commande":self.commande,"duree":self.duree,"ingredients":self.ingredients.id,"action1":self.action1}
		vec = {}
		vec['machine'] = self.machine.id
		vec['commande'] = self.commande
		vec['duree'] = self.duree
		
		ingredientsid = []
		for ingredient in self.ingredients.all() :
			ingredientsid.append(ingredient.id)
		vec['ingredients'] = ingredientsid

		if self.action1 is not None :
			vec['action'] = self.action1.id
		return vec
	def json_extended(self):
		vec = {}
		vec['machine'] = self.machine.id
		vec['commande'] = self.commande
		vec['duree'] = self.duree
		
		ingredientsid = []
		for ingredient in self.ingredients.all() :
			ingredientsid.append(ingredient.id)
		vec['ingredients'] = ingredientsid

		if self.action is not None :
			vec['action'] = self.action1.id
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

class Recette(models.Model):
	nom = models.CharField(max_length=100)
	action1 = models.ForeignKey(
					Action, # ou "self"
					on_delete=models.PROTECT,
					# blank=True, null=True,
					# related_name="+",
				)
	def __str__(self):	
		return self.nom
	def json(self):
		return {"nom":self.nom,"action1":self.action1.id}
	def json_extended(self):
		return {"nom":self.nom,"action1":self.action1.json()}	   

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
	
class Usine(models.Model):
	departement= models.ForeignKey(
					Departement, # ou "self"
					on_delete=models.PROTECT,
					# blank=True, null=True,
					# related_name="+",
				)
	taille = models.IntegerField()
	machines = models.ManyToManyField(Machine)
	recettes = models.ManyToManyField(Recette)
	stocks = models.ManyToManyField(QuantiteIngredient)
	def costs_machines(self):
		_somme = 0
		for i in self.machines.all() :
			_somme = _somme + i.prix
		return _somme
		
	def costs_stocks(self):
		_somme = 0
		for i in self.stocks.all() :
			_somme = _somme + (i.costs(self.departement.numero)) * (i.quantite)
		return _somme	
			
	def __str__(self):	
		return f"{self.departement}"
	def costs(self):
		return (self.departement.prix_m2 * self.taille) + self.costs_machines() + self.costs_stocks()
	def json(self):
		return {"departement":self.departement.id,"taille":self.taille,"machines":self.machines.id,"recettes":self.recettes,"stocks":self.stocks}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

class Prix(models.Model):
	ingredient= models.ForeignKey(
					Ingredient, # ou "self"
					on_delete=models.PROTECT,
					# blank=True, null=True,
					# related_name="+",
				)	
	departement = models.ForeignKey(
					Departement, # ou "self"
					on_delete=models.PROTECT,
					# blank=True, null=True,
					# related_name="+",
				)
	prix = models.IntegerField()
	def __str__(self):	
		return f"{self.ingredient.id} = {self.prix} euros dans le {self.departement}"

	def json(self):
		return{
		"departement": self.departement.id,
		"ingredient": self.ingredient.id,
		"prix": self.prix,
		
    }
	def json_extended(self):
		return self.json()	




	
