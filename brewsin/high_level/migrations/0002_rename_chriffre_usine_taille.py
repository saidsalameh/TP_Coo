# Generated by Django 4.2.5 on 2023-09-28 12:10

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ("high_level", "0001_initial"),
    ]

    operations = [
        migrations.RenameField(
            model_name="usine",
            old_name="chriffre",
            new_name="taille",
        ),
    ]
