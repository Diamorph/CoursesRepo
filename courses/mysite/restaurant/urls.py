from django.conf.urls import url

from . import views


urlpatterns = [
    url(r'^cold_dishes/$', views.Cold_dishes, name = 'main'),
    url(r'^hot_appetizers/$', views.Hot_appetizers, name = 'main'),
    url(r'^salad/$', views.Salad_view, name = 'main'),
    url(r'^first_courses/$', views.First_courses, name = 'main'),
    url(r'^$', views.hot_view),

]