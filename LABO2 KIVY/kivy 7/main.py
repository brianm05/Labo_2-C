from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import (
    NumericProperty, ReferenceListProperty, ObjectProperty
)
from kivy.vector import Vector
from kivy.clock import Clock
from kivy.config import Config

import random
import json
import os

pos=75
vivo=True
enemyPos=50

tamanio_enemigo_x=50
tamanio_enemigo_y=100

tamanio_boton_x=150
tamanio_boton_y=50

flag = 0


def cargarMejorPuntaje(filename="score.json"):
    if os.path.exists(filename):
        with open(filename, 'r') as file:
            return json.load(file).get("best_score", 0)
    return 0

def guardarMejorPuntaje(score, filename="score.json"):
    with open(filename, 'w') as file:
        json.dump({"best_score": score}, file)



class Player(Widget):
    score = NumericProperty(0)
    mejor_score = NumericProperty(cargarMejorPuntaje())

class Enemy(Widget):
    velocity_x = NumericProperty(0)
    velocity_y = NumericProperty(0)
    velocity = ReferenceListProperty(velocity_x, velocity_y)

    def move(self):
        self.pos = Vector(*self.velocity) + self.pos

class Game(Widget):
    car = ObjectProperty(None)
    player = ObjectProperty(None)
    start_button = ObjectProperty(None)
    quit_button = ObjectProperty(None)
    mejor_puntaje = ObjectProperty(None)

    def reubicarEnemigo(self):
        self.car.y = self.height #reubicar el enemigo en el eje y
        posiciones=(self.width/6-tamanio_enemigo_x/2,
                self.center_x-tamanio_enemigo_x/2,
                self.width/6*5-tamanio_enemigo_x/2)
        eleccion=random.choice(posiciones)
        self.car.x=eleccion #obtener una de las tres posiciones posible para el eje en x

    def actualizarScore(self):
        self.player.score += 1 #aumentar el score actual
        #actualizar en best score (en caso de ser necesario)
        if self.player.score>self.player.mejor_score:
            self.player.mejor_score=self.player.score
            guardarMejorPuntaje(self.player.mejor_score)


    def serve_car(self, vel=(0, -4)):
        self.car.center = self.center
        self.car.velocity = vel
        self.car.velocity_y = -4
        self.reubicarEnemigo()
        global vivo
        vivo=True

    def iniciar_juego(self):
        self.serve_car()
        self.player.score = 0
        self.start_button.pos = (-500, -500)
        self.quit_button.pos = (-500, -500)
        self.mejor_puntaje.pos = (-500, -500)

    def mostrar_menu(self):
        self.start_button.pos = (self.width / 2 - tamanio_boton_x/2, self.height/2)
        self.quit_button.pos = (self.width / 2 - tamanio_boton_x/2, self.height/2-tamanio_boton_y)
        self.mejor_puntaje.pos = (self.width/2-tamanio_boton_x/3, self.height/2-self.mejor_puntaje.height*2)

    def update(self, dt):

        self.car.move()

        aumentarNivel=5
        
        if self.car.y < self.y-50:
            self.reubicarEnemigo()
            self.actualizarScore()

        if self.player.score == aumentarNivel:
            self.car.velocity_y = -8
        
        if (self.car.x == self.player.x):        
            if ( 45 < self.car.y <= 235):
                global vivo
                vivo = False
        if (not vivo):
            self.car.velocity_y = 0
            self.mostrar_menu()
            
    def on_touch_move(self, touch):
        global vivo
        if vivo:
            if touch.x < self.width / 3:
                self.player.center_x = self.width/6
            if touch.x > self.width / 3 and touch.x < self.width - self.width / 3:
                self.player.center_x = self.center_x
            if touch.x > self.width - self.width / 3:
                self.player.center_x = self.width/6*5

class GameApp(App):
    def build(self):

        Config.set('graphics', 'width', '450')
        Config.set('graphics', 'height', '800')
        game = Game()
        game.start_button = game.ids.start_button
        game.quit_button = game.ids.quit_button
        game.mejor_puntaje = game.ids.puntaje_label
        
        #game.serve_car()
        Clock.schedule_interval(game.update, 1.0 / 60.0)
        return game
    
if __name__ == '__main__':
    GameApp().run()
