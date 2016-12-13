from django import forms

class Restaurants_Form(forms.Form):
    image = forms.ImageField()