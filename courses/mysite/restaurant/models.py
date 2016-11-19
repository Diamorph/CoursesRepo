from django.db import models

# Create your models here.


class Cold_Dishes(models.Model):
    name = models.CharField(max_length = 30)
    weight = models.IntegerField(default = 0)
    price = models.FloatField(default = 0)
    consist = models.CharField(max_length = 100)
    image = models.ImageField(upload_to='image/' , null = True)


class Salad(models.Model):
    name = models.CharField(max_length=30)
    weight = models.IntegerField(default=0)
    price = models.FloatField(default=0)
    consist = models.CharField(max_length=100)
    image = models.ImageField(upload_to='image/', null=True)

class Hot_Appetizers(models.Model):
    name = models.CharField(max_length=30)
    weight = models.IntegerField(default=0)
    price = models.FloatField(default=0)
    consist = models.CharField(max_length=100)
    image = models.ImageField(upload_to='image/', null=True)

class First_Courses(models.Model):
    name = models.CharField(max_length=30)
    weight = models.IntegerField(default=0)
    price = models.FloatField(default=0)
    consist = models.CharField(max_length=100)
    image = models.ImageField(upload_to='image/', null=True)