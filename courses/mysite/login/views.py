from django.contrib import auth
from django.shortcuts import render
from django.shortcuts import render_to_response ,redirect , HttpResponse #render
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm
# Create your views here.

# def register(request):
#      args = {}
#      args['form'] = UserCreationForm
#      if request.POST:
#          newuser_form  =  UserCreationForm(request.POST)
#          if newuser_form.is_valid():
#              newuser_form.save()
#              newuser = auth.authenticate(username = newuser_form.cleaned_data['username'] , password  = newuser_form.cleaned_data['password2'])
#              auth.login(request , newuser)
#              newuser.save()
#              print(newuser)
#              return redirect('/')
#          else:
#              args['form'] =  newuser_form
#      return render(request , "register.html" , args)

def register(request):
    if request.method == "POST":
        user = User.objects.create_user(username=request.POST['username'], password=request.POST['password'])
        if user is not None:
            return render_to_response('login.html', {'error': 'We have a user with such name'})
        else:
            user = User.objects.create_user(request.POST['username'], request.POST['password'])

            user.save()
            custom_user = User.objects.create(User=user)
            custom_user.save()
    else:
        return render_to_response('register.html', {})






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
    #auth.logout(request)
   # response = redirect('/')
   # response.set_cookie(request, "You are logout")
   # return response
    auth.logout(request)
    return redirect('/')