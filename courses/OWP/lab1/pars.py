import json
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
    print (restaurants)
    rest_list = []
    for i in restaurants:
         rest_list.append(Restaurant().parseFromDict(i))
    file.close()
    return rest_list


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
    if request == "all":
        file = open("Restaurants.json", "r")
        restaurants = json.load(file)
        return json.dumps(restaurants,sort_keys=True, indent=0)
    if request == "help":
        return "all\nexit"
    argdict = parseRequest(request)
    if argdict == None:
        return '[{"exception" : "wrong args"}]'
    restaurants = ParseFile("Restaurants.json")
    newRestlist = restaurants.copy()
    for rs in restaurants:
        for key, value in argdict.items():
            if key == "name":
                if rs.name != value:
                    print("name")
                    newRestlist.remove(rs)
                    break
            elif key == "city":
                if rs.city != value:
                    print("city")
                    newRestlist.remove(rs)
                    break
            elif key[-2:] == 'lt':
                if key.find("rate") == 0:
                    if rs.rate > int(value):
                        print(value)
                        print("ratelt")
                        newRestlist.remove(rs)
                        break
                elif key.find("check") == 0:
                    if rs.check > int(value):
                        print("checklt")
                        newRestlist.remove(rs)
                        break
            elif key[-2:] == 'gt':
                if key.find("rate") == 0:
                    if rs.rate < int(value):
                        print("rategt" + rs.name)
                        newRestlist.remove(rs)
                        break
                elif key.find("check") == 0:
                    if rs.check < int(value):
                        print("checkgt")
                        newRestlist.remove(rs)
                        break

            elif key == "rate":
                if rs.rate == int(value):
                    print("rate")
                    newRestlist.remove(rs)
                    break
            elif key == "check":
                if rs.check == int(value):
                    print("check")
                    newRestlist.remove(rs)
                    break
            else:
                return '[{"exception" : "wrong args"}]'
    returnList = []
    for rs in newRestlist:
        print(rs.toString())
        returnList.append(rs.toDict())
    return json.dumps(returnList, sort_keys=True, indent=4)