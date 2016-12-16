from django.conf.urls import url, include
from django.contrib import admin

from restaurant import api_views

urlpatterns = [
    url(r'^add/$', api_views.add),
    url(r'^$', api_views.get),
    url(r'^(\d+)/$',api_views.Cold_Dishes_id),
    url(r'^del/(\d+)/$', api_views.delete),

]