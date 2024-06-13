from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import (
    NumericProperty, ReferenceListProperty, ObjectProperty,ListProperty
)
from kivy.vector import Vector
from kivy.core.audio import SoundLoader
from kivy.clock import Clock
from kivy.config import Config

import random
import json
import os

vivo=False
enemyPos=50
estadoPista=0

arcoiris=[   [1,0,0,1],[0,1,0,1],[0,0,1,1]   ]

calle=[      [.5,.5,.5,.5],
                [.75,.75,.75,.75],
                [.5,.5,.5,.5]   ]


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
    color = ListProperty([1, 1, 1, 1])

class Enemy(Widget):
    velocity_x = NumericProperty(0)
    velocity_y = NumericProperty(0)
    velocity = ReferenceListProperty(velocity_x, velocity_y)
    color = ListProperty([1, 1, 1, 1])

    def move(self):
        self.pos = Vector(*self.velocity) + self.pos

class Game(Widget):

    aumentarNivel=5
    flag=0

    car = ObjectProperty(None)
    player = ObjectProperty(None)

    start_button = ObjectProperty(None)
    quit_button = ObjectProperty(None)
    color_button = ObjectProperty(None)
    mejor_puntaje = ObjectProperty(None)
    pista_button = ObjectProperty(None)

    color1 = ListProperty([.5,.5,.5,.5])
    color2 = ListProperty([.75,.75,.75,.75])
    color3 = ListProperty([.5,.5,.5,.5])

    sound=SoundLoader.load('sounds/iniciar_juego.mp3')
    crashSound=SoundLoader.load('sounds/crash.mp3')
    gameLoopSound=SoundLoader.load('sounds/main_loop2.mp3')

    def cambiarPista(self):
        global estadoPista
        if self.color1==calle[0] and estadoPista==0:
            self.color1=arcoiris[0]
            self.color2=arcoiris[1]
            self.color3=arcoiris[2]
            self.pista_button.text = "Carretera"
            estadoPista=1
            return
        if self.color1==arcoiris[0] and estadoPista==1:
            self.color1=calle[0]
            self.color2=calle[1]
            self.color3=calle[2]
            estadoPista=0
            self.pista_button.text = "Pista de colores"
            return

    def reubicarEnemigo(self):
        self.car.y = self.height-self.car.height #reubicar el enemigo en el eje y

        posiciones=(self.width/6-self.car.width/2,
                self.center_x-self.car.width/2,
                self.width/6*5-self.car.width/2)
        eleccion=random.choice(posiciones)
        self.car.x=eleccion #obtener una de las tres posiciones posible para el eje en x
        
        #obtener una lista con 3 numeros aleatorios (de 0 a 1) para el color rgb de auto enemigo
        self.car.color = [random.uniform(0,1)] +[random.uniform(0,1)] +[random.uniform(0,1)] + [1]

    def actualizarScore(self):
        self.player.score += 1 #aumentar el score actual
        #actualizar en best score (en caso de ser necesario)
        if self.player.score>self.player.mejor_score:
            self.player.mejor_score=self.player.score
            guardarMejorPuntaje(self.player.mejor_score)

        #Esto determina la curva de dificultad. Al momento del comentario:
        #Cada 5 puntos conseguidos, el auto enemigo aumenta su velocidad en 2.
        #(esta en negativo porque el enemigo se mueve en direccion contraria)     
        if self.player.score == self.aumentarNivel:
            self.car.velocity_y -= 2
            self.aumentarNivel+=5

    def serve_car(self, vel=(0, -4)):
        self.car.center = self.center
        self.car.velocity = vel
        self.car.velocity_y = -4
        self.reubicarEnemigo()
        global vivo
        vivo=True

    def cambiarColor(self):
        self.player.color = [random.uniform(0,1)] +[random.uniform(0,1)] +[random.uniform(0,1)] + [1]

    def iniciar_juego(self):
        self.serve_car()
        self.gameLoopSound.play()
        self.player.score = 0
        self.start_button.pos = (-500, -500)
        self.quit_button.pos = (-500, -500)
        self.color_button.pos = (-500, -500)
        self.pista_button.pos = (-500, -500)
        self.mejor_puntaje.pos = (-500, -500)

    def mostrar_menu(self):
        self.start_button.pos = (self.width / 2 - self.start_button.width/2, self.height/2+self.start_button.height)
        self.color_button.pos = (self.width / 2 - self.start_button.width/2, self.height/2)
        self.pista_button.pos = (self.width / 2 - self.start_button.width/2, self.height/2-self.start_button.height)
        self.quit_button.pos = (self.width / 2 - self.start_button.width/2, self.height/2-self.start_button.height*2)
        
        self.mejor_puntaje.pos = (self.width/2-self.start_button.width/3, self.height/2-self.mejor_puntaje.height*2)

    def update(self, dt):

        self.car.move()

        if self.car.y < self.y+self.car.height:
            self.reubicarEnemigo()
            self.actualizarScore()
        
        if (self.car.x == self.player.x):        
            if ( 55 < self.car.y <= 235):
                self.gameLoopSound.stop()
                self.crashSound.play()
                self.crashSound.loop=False
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
        game.color_button = game.ids.color_button
        game.pista_button = game.ids.pistaColor_button

        game.mejor_puntaje = game.ids.puntaje_label
        
        #game.serve_car()
        Clock.schedule_interval(game.update, 1.0 / 60.0)
        return game
    
if __name__ == '__main__':
    GameApp().run()
