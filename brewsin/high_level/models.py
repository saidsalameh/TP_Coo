from django.db import models

# Create your models here.

class Departement(models.Model):
	numero = models.IntegerField()
	prix_m2 = models.IntegerField()
	
	def __str__(self):
		return str((f'Departement {self.numero}'))

class Ingredient(models.Model):
	nom = models.CharField(max_length=100)
	def __str__(self):
		return self.nom
	

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
		return self.ingredient.prix_set.get(departement__numero=departement).prix * self.quantite
	
class Machine(models.Model):
	nom = models.CharField(max_length=100)
	prix = models.IntegerField()
	def __str__(self):	
		return self.nom
	def costs(self):
		return self.prix
	
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
		return self.commande
	
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
		for i in self.machines :
			_somme = _somme + i.prix
		return _somme
		
	def costs_stocks(self):
		_somme = 0
		for i in self.stocks :
			_somme = _somme + (i.ingredient.prix) * (i.quantite)
		return _somme	
			
	def __str__(self):	
		return f"{self.departement}"
	def costs(self):
		return (self.departement.prix_m2 * self.taille) + self.costs_machines() + self.costs_stocks()


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
		return str(f"{self.ingredient} = {self.prix} euros dans le {self.departement} ")
	

	
