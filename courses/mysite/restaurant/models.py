from django.db import models

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

class Labs(models.Model):
    name = models.CharField(max_length=10)
    decrib = models.CharField(max_length=1000);
    res = models.IntegerField(default=0)
    def dict(self):
        return{
            'name': self.name,
            'decrib': self.decrib,
            'res': self.res,
        }