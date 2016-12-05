import json
from pprint import pprint


class Restaurant(object):
    def __init__(self, name=None, rate=None, check=None, city=None, date=None):
        self.name = name
        self.rate = rate
        self.check = check
        self.city = city
        self.date = date

    def parseFromDict(self, dict):
        self.__init__(dict.get("name"), dict.get("rate"), dict.get("check"), dict.get("city"), dict.get("date"))
        return self

    def toString(self):
        _str = ""
        _str += self.name + '\n'
        _str += str(self.rate) + '\n'
        _str += str(self.check) + '\n'
        _str += self.city + '\n'
        _str += self.date + '\n'
        return _str

    def toDict(self):
        return {'name': self.name, 'rate': self.rate, 'check': self.check , 'city': self.city , 'date': self.date}

def ParseFile(filename):
    file = open("Restaurants.json", "r")
    restaurants = json.load(file)
    print(restaurants)
    rest_list = []
    for i in restaurants:
        rest_list.append(Restaurant().parseFromDict(i))
    file.close()
    return rest_list

#with open('data.json') as data_file:
 #   data = json.load(data_file)

#pprint(data)
def parseRequest(request):
    dictionary = {}
    if request.find('=') == -1:
        return None
    for s in request.split('&'):
        arglist = s.split('=', 1)
        print (arglist);
        dictionary.update({arglist[0] : arglist[1]})
    print (dictionary)
    return dictionary

def getJson(request):
        file = open("Restaurants.json", "r")
        restaurants = json.load(file)
        return json.dumps(restaurants,sort_keys=True, indent=0)