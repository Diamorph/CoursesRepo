from django.shortcuts import render
from django.http import HttpResponse
from django.shortcuts import render, get_object_or_404 ,render_to_response
from .models import Cold_Dishes, First_Courses, Salad, Hot_Appetizers
from django.contrib import auth


# Create your views here.

def cold_dishes(request, Cold_Dishes_id):
    return HttpResponse("You're looking at question %s." % Cold_Dishes_id)

def Cold_dish_id(request, id):
    return render_to_response("Cold_Dishes.html" , {'dishes': [Cold_Dishes.objects.get(id = int(id))], 'username':auth.get_user(request).username})


def Cold_dishes(request):
    args = {}
    if request.method == 'GET':
        return render_to_response("Cold_Dishes.html" , {'dishes': Cold_Dishes.objects.all(), 'username':auth.get_user(request).username} , args)

def First_courses(request):
    args = {}
    if request.method == 'GET':
        return render_to_response("First_courses.html", {'first_course': First_Courses.objects.all(),'username':auth.get_user(request).username}, args)

def Hot_appetizers(request):
    args = {}
    if request.method == 'GET':
        return render_to_response("Hot_Appetizers.html", {'hot': Hot_Appetizers.objects.all() , 'username':auth.get_user(request).username}, args)

def Salad_view(request):
    args = {}
    if request.method == 'GET':
        return render_to_response("Salad.html", {'salad': Salad.objects.all() , 'username':auth.get_user(request).username}, args)


def Main_view(request):
    if request.method == 'GET':
        return render_to_response("Salad.html", {'salad': Salad.objects.all() ,'username':auth.get_user(request).username}, {})
        #return HttpResponse(request , "You're looking at question." ,{})



def hot_view(request):

    return render_to_response("Hot_Appetizers.html" , {'hot': Hot_Appetizers.objects.all() , 'username' : auth.get_user(request).username})

def Menu(request):
    args = {}
    if request.method == 'GET':
        return render_to_response("menu.html", {'username':auth.get_user(request).username}, args)

