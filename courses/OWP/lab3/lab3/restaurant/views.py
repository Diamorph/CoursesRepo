from django.shortcuts import render

# Create your views here.
import json
from django.shortcuts import render_to_response ,redirect , render

rest_list = []
'''
def parseFIle(filename):
    file = open("Phone.json", "r")
    phones = json.load(file);
    print (phones)
    for i in phones:
        phone_list.append(Phone().parseFromDict(i))
    file.close()
    print(phone_list)
parseFIle("Phone.json")
'''

def getJson(request):
    file = open("Restaurants.json", "r")
    print("Error")
    rest = json.load(file)
    return rest

def show(request):
    rest = getJson("Restaurants.json")
    return render( request , "all.html" , {'rest': rest})

def get(request , path):
    rests = getJson("Restaurants.json")
    rest = {}
    for i in rests:
        if i['id'] == int(path):
            rest = i
            break
    return render(request , "restaurant.html" , {'rest': rest})
