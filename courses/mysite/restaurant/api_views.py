from django.shortcuts import render
from django.http import HttpResponse
import json
from django.shortcuts import render, get_object_or_404 ,render_to_response
from restaurant.models import Cold_Dishes, First_Courses, Salad, Hot_Appetizers
from django.contrib import auth
from django.shortcuts import render_to_response ,redirect , HttpResponse #render
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm
# Create your views here.


# Create your views here.

def add(request):
    result = "OK!"
    error_api = "Error"
    if request.method == "POST" and request.POST['name'] and request.POST['weight'] and request.POST['price'] and request.POST['consist']and request.FILES['image']:
        cd = Cold_Dishes.objects.create(name=request.POST['name'],
                                  weight=request.POST['weight'],
                                  price=request.POST['price'],
                                  consist=request.POST['consist'],
                                  image=request.FILES['image'],
                                  )
        response_data = cd.dict()
        request.session['has_posted_already'] = True
        return HttpResponse(json.dumps({'dishes': response_data}), content_type="application/json")
    return HttpResponse(json.dumps({'Status': 'error2'}), content_type="application/json")


def get(request):
    if request.method == "GET":
        return HttpResponse(json.dumps([i.dict() for i in Cold_Dishes.objects.all()]), content_type='application/json')

def Cold_Dishes_id(request,id):
    if request.method == "GET":
        return HttpResponse(json.dumps(Cold_Dishes.objects.get(id=int(id)).dict()), content_type='application/json')


def delete(request,id):
    result = "Successful del"
    if request.method == "POST":
        cd = Cold_Dishes.objects.get(id=int(id))
        Cold_Dishes.objects.get(id=int(id)).delete()
        response_data = cd.dict()
        request.session['has_deleted_already'] = True
        return HttpResponse(json.dumps({'dishes': response_data}), content_type="application/json")
    return HttpResponse(json.dumps({'Status': 'error2'}), content_type="application/json")