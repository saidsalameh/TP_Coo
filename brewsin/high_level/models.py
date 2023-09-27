from django.db import models

# Create your models here.

class Departement(models.Model):
	numero = models.IntegerField()
	prix_m2 = models.IntegerField()
	def __str__(self):
		return self.numero

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
		return self.quantite
	
class Machine(models.Model):
	nom = models.CharField(max_length=100)
	prix = models.IntegerField()
	def __str__(self):	
		return self.nom
	
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
		return self.machine
	
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
	chriffre = models.IntegerField()
	machines = models.ManyToManyField(Machine)
	recettes = models.ManyToManyField(Recette)
	stocks = models.ManyToManyField(QuantiteIngredient)
	def __str__(self):	
		return self.departement
	def __str__(self):	
		return self.machine

class Prix(models.Model):
	ingredient= models.ForeignKey(
					Ingredient, # ou "self"
					on_delete=models.PROTECT,
					# blank=True, null=True,
					# related_name="+",
				)	
	departement= models.ForeignKey(
					Departement, # ou "self"
					on_delete=models.PROTECT,
					# blank=True, null=True,
					# related_name="+",
				)
	prix = models.IntegerField()
	def __str__(self):	
		return self.prix





	
	
