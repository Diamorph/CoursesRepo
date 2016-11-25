from django.conf.urls import url, include
from django.contrib import admin

from restaurant import api_views

urlpatterns = [
    url(r'^cold_dishes/$', api_views.Cold_dishes, name ='main'),
    url(r'^cold_dish/(\d+)/$', api_views.Cold_dish_id, name = 'main'),
    url(r'^hot_appetizers/$', api_views.Hot_appetizers, name ='main'),
    url(r'^salad/$', api_views.Salad_view, name ='main'),
    url(r'^first_courses/$', api_views.First_courses, name ='main'),
    url(r'^$', api_views.hot_view),
    url(r'^auth/', include('login.urls')),
    url(r'^admin/', admin.site.urls),
    url(r'^restaurant/', include('restaurant.urls')),
    url(r'^auth/'  ,include('login.urls')),
    url(r'^', include('restaurant.urls')),

]