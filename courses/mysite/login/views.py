from django.contrib import auth
from django.shortcuts import render
from django.shortcuts import render_to_response ,redirect , HttpResponse #render
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm
# Create your views here.


def register(request):
    if request.method == "POST":
        try:
            user = User.objects.get(username=request.POST['username'])
            if user is not None:
                return render(request, 'register.html', {'login_error': 'User with such name is already exists'})
        except:
            if request.POST['password'] == request.POST['password2']:
                user = User.objects.create_user(username=request.POST['username'], password=request.POST['password'])
                user.save()
                return login(request)
            else:
                return render(request,'register.html', {'pass_error': 'Passwords are not similar'})
    else:
        return render(request, 'register.html', {})






def login(request):
    args = {}
    if request.method == 'POST':
        username = request.POST.get('username'  , '')
        password = request.POST.get('password' , '')
        user = auth.authenticate(username=username , password=password)
        print(username)
        print(password)
        request.session.set_expiry(300000)
        request.session['login'] = True
        if ("login" not in request.session):
            auth.logout(request)
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