from django.shortcuts import render
from django.views.generic import DetailView
from json import dumps
from .models import Departement
from .models import Ingredient
from .models import QuantiteIngredient
from .models import Machine
from .models import Action
from .models import Recette
from .models import Usine
from .models import Prix
from django.http import HttpResponse

# Create your views here.

class DepartementDetailView(DetailView):
    model = Departement
    def render_to_response(self, context, **response_kwargsse):
        return HttpResponse(dumps(self.object.json()))

class IngredientDetailView(DetailView):
    model = Ingredient
    def render_to_response(self, context, **response_kwargsse):
        return HttpResponse(dumps(self.object.json()))
               
class QuantiteIngredientDetailView(DetailView):
    model = QuantiteIngredient
    def render_to_response(self, context, **response_kwargsse):
        return HttpResponse(dumps(self.object.json()))
        
class MachineDetailView(DetailView):
    model = Machine
    def render_to_response(self, context, **response_kwargsse):
        return HttpResponse(dumps(self.object.json()))
        
class ActionDetailView(DetailView):
    model = Action
    def render_to_response(self, context, **response_kwargsse):
        return HttpResponse(dumps(self.object.json()))

class RecetteDetailView(DetailView):
    model = Recette
    def render_to_response(self, context, **response_kwargsse):
        return HttpResponse(dumps(self.object.json()))
        
class UsineDetailView(DetailView):
    model = Usine
    def render_to_response(self, context, **response_kwargsse):
        return HttpResponse(dumps(self.object.json()))
        
class PrixDetailView(DetailView):
    model = Prix
    def render_to_response(self, context, **response_kwargsse):
        return HttpResponse(dumps(self.object.json()))
