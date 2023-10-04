"""
URL configuration for brewsin project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from high_level import views


urlpatterns = [
    path("admin/", admin.site.urls),
    path("Prix/<int:pk>",views.DepartementDetailView.as_view(),name="Prix",),

]
urlpatterns = [
    path("admin/", admin.site.urls),
    path("Departement/<int:pk>",views.DepartementDetailView.as_view(),name="Departement",),

]
urlpatterns = [
    path("admin/", admin.site.urls),
    path("Ingredient/<int:pk>",views.DepartementDetailView.as_view(),name="Ingredient",),

]
urlpatterns = [
    path("admin/", admin.site.urls),
    path("QuantiteIngredient/<int:pk>",views.DepartementDetailView.as_view(),name="QuantiteIngredient",),

]
urlpatterns = [
    path("admin/", admin.site.urls),
    path("Machine/<int:pk>",views.DepartementDetailView.as_view(),name="Machine",),

]
urlpatterns = [
    path("admin/", admin.site.urls),
    path("Action/<int:pk>",views.DepartementDetailView.as_view(),name="Action",),

]

urlpatterns = [
    path("admin/", admin.site.urls),
    path("Recette/<int:pk>",views.DepartementDetailView.as_view(),name="Recette",),

]
urlpatterns = [
    path("admin/", admin.site.urls),
    path("Usine/<int:pk>",views.DepartementDetailView.as_view(),name="Usine",),

]




