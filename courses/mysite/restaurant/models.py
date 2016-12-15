from django.db import models
from django.forms import MultiValueField, CharField, ChoiceField, MultiWidget, TextInput, Select

# Create your models here.


class Cold_Dishes(models.Model):
    name = models.CharField(max_length = 30)
    weight = models.IntegerField(default = 0)
    price = models.FloatField(default = 0)
    consist = models.CharField(max_length = 100)
    image = models.ImageField(null = True, blank = True, upload_to='images/')
    def dict(self):
        return {
            'name': self.name,
            'weight': self.weight,
            'price' : self.price,
            'consist': self.consist,
            'id': self.id,
            'image': self.image.url,
        }


class Salad(models.Model):
    name = models.CharField(max_length=30)
    weight = models.IntegerField(default=0)
    price = models.FloatField(default=0)
    consist = models.CharField(max_length=100)
    image = models.ImageField(null = True, blank = True, upload_to='images/')

class Hot_Appetizers(models.Model):
    name = models.CharField(max_length=30)
    weight = models.IntegerField(default=0)
    price = models.FloatField(default=0)
    consist = models.CharField(max_length=100)
    image = models.ImageField(null = True, blank = True, upload_to='images/')

class First_Courses(models.Model):
    name = models.CharField(max_length=30)
    weight = models.IntegerField(default=0)
    price = models.FloatField(default=0)
    consist = models.CharField(max_length=100)
    image = models.ImageField(null = True, blank = True, upload_to='images/')
    def dict(self):
        return {
            'name': self.name,
            'weight': self.weight,
            'price' : self.price,
            'consist': self.consist,
            'id': self.id,
        }


# class PhoneWidget(MultiWidget):
#     def __init__(self, code_length=3, num_length=7, attrs=None):
#         widgets = [TextInput(attrs={'size': code_length, 'maxlength': code_length}),
#                    TextInput(attrs={'size': num_length, 'maxlength': num_length})]
#         super(PhoneWidget, self).__init__(widgets, attrs)
#
#     def decompress(self, value):
#         if value:
#             return [value.code, value.number]
#         else:
#             return ['', '']
#
#     def format_output(self, rendered_widgets):
#         return '+0' + '(' + rendered_widgets[0] + ') - ' + rendered_widgets[1]
#
#
#
# class PhoneField(MultiValueField):
#     def __init__(self, code_length, num_length, *args, **kwargs):
#         list_fields = [CharField(),
#                        CharField()]
#         super(PhoneField, self).__init__(list_fields, widget=PhoneWidget(code_length, num_length), *args, **kwargs)
#
#     def compress(self, values):
#         return '+0' + values[0] + values[1]  #Собственно, стандартизация строки номера эстетики ради

class Order(models.Model):
    name = models.CharField(max_length = 30)
    surname = models.CharField(max_length = 30)
    phone = models.CharField(max_length=11)
    email = models.EmailField(max_length = 50)
    number = models.IntegerField(default=0)
    date = models.DateField()
    def dict(self):
        return {
        'name': self.name,
        'surname': self.surname,
        'phone': self.phone,
        'email': self.email,
        'number' : self.number,
        'date' : self.date,
        'id' : self.id,
        }















