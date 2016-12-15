from django.conf.urls import url
from django.contrib.staticfiles.urls import staticfiles_urlpatterns
from django.conf.urls.static import static
from django.conf import settings

from . import views


urlpatterns = [
    url(r'^cold_dishes/$', views.Cold_dishes, name = 'main'),
    url(r'^add/$', views.rest, name = 'main'),
    url(r'^hot_appetizers/$', views.Hot_appetizers, name = 'main'),
    url(r'^salad/$', views.Salad_view, name = 'main'),
    url(r'^first_courses/$', views.First_courses, name = 'main'),
    url(r'^search/$',views.search, name = 'main'),
    url(r'^cold_dish/(\d+)/$', views.ColdDishes_id, name = 'main'),
    url(r'^cold_dish/del/(\d+)/$', views.DelCold_Dishes, name='main'),
    url(r'^order/$', views.Orders, name='main'),
    url(r'^orders/$', views.Orders_get, name='main'),
    url(r'^contacts/$', views.Contact, name='main'),
   # url(r'^hot_appetizers/$', views.hot_view, name = 'main'),

    url(r'^$', views.Menu),


]

if settings.DEBUG:
    urlpatterns += staticfiles_urlpatterns() + static(
    settings.MEDIA_URL, document_root=settings.MEDIA_ROOT
)