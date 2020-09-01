from django.db import models


class Button(models.Model):
    value = models.BooleanField(default = True)
    mapped_io = models.CharField(max_length=25, default = 'a')
    def __str__(self):
        return "Digital: " + str(self.mapped_io)

class Slider(models.Model):
    value = models.IntegerField(default = 0)
    mapped_io = models.CharField(max_length=25, default = 'a')
    def __str__(self):
        return "Analogue: " + str(self.mapped_io)

# Create your models here.
