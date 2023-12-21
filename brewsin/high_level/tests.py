from django.test import TestCase

# Create your tests here.


from .models import Machine
from .models import Departement
from .models import Ingredient
from .models import QuantiteIngredient
from .models import Prix
from .models import Usine
'''
class MachineModelTests(TestCase):
    def test_usine_creation(self):
        self.assertEqual(Machine.objects.count(), 0)
        Machine.objects.create(nom="four",prix=1_000)
        self.assertEqual(Machine.objects.count(), 1)
'''
class MachineModelTests(TestCase):
    def test_usine_creation(self):
        dep = Departement.objects.create(numero = 31, prixm2 = 2000)
        four = Machine.objects.create(nom="four",prix = 15000)
        malaxeur = Machine.objects.create(nom="Batteur",prix = 8001)
        eau = Ingredient.objects.create(nom="Eau")
        sel = Ingredient.objects.create(nom="Sel")

        stock_eau = QuantiteIngredient.objects.create(ingredient = eau, quantite = 100)
        stock_sel = QuantiteIngredient.objects.create(ingredient = sel, quantite = 30)

        Prix.objects.create(ingredient = eau, departement = dep, prix = 20)
        Prix.objects.create(ingredient = sel, departement = dep, prix = 10)

        usine = Usine.objects.create(departement = dep, taille = 50)
        usine.machines.add(four)
        usine.machines.add(malaxeur)
        usine.stocks.add(stock_eau)
        usine.stocks.add(stock_sel)
