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

def cold_dishes(request, Cold_Dishes_id):
    return HttpResponse("You're looking at question %s." % Cold_Dishes_id)

def Cold_dish_id(request, id):
    args = {}
    if request.method == 'GET':
        return HttpResponse(json.dumps(Cold_Dishes.objects.get(id = int(id)).dict()), content_type='application/json')
    #return render_to_response("Cold_Dishes.html" , {'dishes': [Cold_Dishes.objects.get(id = int(id))], 'username':auth.get_user(request).username})

def Cold_dishes(request):
    args = {}
    if request.method == 'GET':
        return HttpResponse(json.dumps([i.dict() for i in Cold_Dishes.objects.all()]), content_type='application/json')


        #return render_to_response("Cold_Dishes.html" , {'dishes': Cold_Dishes.objects.all(), 'username':auth.get_user(request).username} , args)

def Labs(request):
    args = {}
    if request.method == 'GET':
        return HttpResponse(json.dumps([i.dict() for i in Labs.objects.all()]), content_type='application/json')

def Lab_id(request, id):
    args = {}
    if request.method == 'GET':
        return HttpResponse(json.dumps(Labs.objects.get(id = int(id)).dict()), content_type='application/json')

def First_courses(request):
    args = {}
    if request.method == 'GET':
        return HttpResponse(json.dumps([i.dict() for i in First_Courses.objects.all()]), content_type='application/json')
    # args = {}
    # if request.method == 'GET':
    #     return render_to_response("First_courses.html", {'first_course': First_Courses.objects.all(),'username':auth.get_user(request).username}, args)


def First_course_id(request, id):
    args = {}
    if request.method == 'GET':
        return HttpResponse(json.dumps(First_Courses.objects.get(id = int(id)).dict()), content_type='application/json')


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



def register(request):
     args = {}
     args['form'] = UserCreationForm
     if request.POST:
         newuser_form  =  UserCreationForm(request.POST)
         if newuser_form.is_valid():
             newuser_form.save()
             newuser = auth.authenticate(username = newuser_form.cleaned_data['username'] , password  = newuser_form.cleaned_data['password2'])
             auth.login(request , newuser)
             newuser.save()
             print(newuser)
             return redirect('/')
         else:
             args['form'] =  newuser_form
     return render(request , "register.html" , args)






def login(request):
    args = {}
    if request.method == 'POST':
        username = request.POST.get('username'  , '')
        password = request.POST.get('password' , '')
        user = auth.authenticate(username=username , password=password)
        print(username)
        print(password)
        if user is not None and user.is_active:
            auth.login(request , user)
            return redirect('/')
        else:
            args['login_error'] = "User is not found"
            return render(request , 'login.html' , args)
    else:
        return render( request , 'login.html', args)




def logout(request):
    auth.logout(request)
    return redirect('/')