from django.contrib import admin
from .models import Cold_Dishes,Hot_Appetizers,Salad , First_Courses
# Register your models here.


class Cold_Dishes_Admin(admin.ModelAdmin):
    fields = ['name' , 'weight' , 'price' , 'consist' , 'image']

class First_Courses_Admin(admin.ModelAdmin):
    fields = ['name' , 'weight' , 'price' , 'consist' , 'image']

class Hot_Appetizers_Admin(admin.ModelAdmin):
    fields = ['name' , 'weight' , 'price' , 'consist' , 'image']

class Salad_Admin(admin.ModelAdmin):
    fields = ['name' , 'weight' , 'price' , 'consist' , 'image']

admin.site.register(Cold_Dishes , Cold_Dishes_Admin)
admin.site.register(First_Courses,First_Courses_Admin )
admin.site.register(Hot_Appetizers, Hot_Appetizers_Admin)
admin.site.register(Salad, Salad_Admin)