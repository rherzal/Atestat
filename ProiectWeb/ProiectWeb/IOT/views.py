from django.http import HttpResponse, HttpResponseRedirect
from django.template import loader
from .models import Button, Slider
import requests

def index(request):
    template = loader.get_template("IOT/index.html")
    Buttons = Button.objects.all()
    Sliders = Slider.objects.all()
    context = {
        'Buttons': Buttons,
        'Sliders': Sliders
    }
    return HttpResponse(template.render(context, request))


def save(request):
    if "Analog_Submit" in request.GET:
        for slider in Slider.objects.all():
            slider.value = request.GET.get("A" + str(slider.pk))
            slider.save()
            return HttpResponseRedirect('/iot')
    else:
        for button in Button.objects.all():
            if ("D" + str(button.pk)) in request.GET:
                button.value = not button.value
                button.save()
                print (str(button.pk) + str(button.value))
                if button.mapped_io == "led" :
                    r = requests.get('http://192.168.1.7:80', params = {'led' : str(button.value)})
                    print(r)
                return HttpResponseRedirect('/iot')
