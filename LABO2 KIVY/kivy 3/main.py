from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import (
    NumericProperty, ReferenceListProperty, ObjectProperty
)
from kivy.vector import Vector
from kivy.clock import Clock
from kivy.config import Config
from kivy.graphics import Color

import random

pos=75
vivo=True
enemyPos=50

class Player(Widget):
    score = NumericProperty(0)


class Enemy(Widget):
    velocity_x = NumericProperty(0)
    velocity_y = NumericProperty(0)
    velocity = ReferenceListProperty(velocity_x, velocity_y)

    def move(self):
        self.pos = Vector(*self.velocity) + self.pos

class Game(Widget):
    car = ObjectProperty(None)
    player = ObjectProperty(None)

    def serve_car(self, vel=(0, -4)):
        self.car.center = self.center
        self.car.velocity = vel

    def update(self, dt):

        self.car.move()

        aumentarNivel=5

        """
        # bounce car off bottom or top
        if (self.car.y < self.y) or (self.car.top > self.top):
            self.car.velocity_y *= -1
        """
        
        if self.car.y < self.y-50:
            self.car.y = self.height
            posiciones=(self.width-2*enemyPos,
                  self.center_x-25,
                  self.x+enemyPos)
            eleccion=random.choice(posiciones)
            self.car.x=eleccion
            self.player.score += 1

        if self.player.score == aumentarNivel:
            self.car.velocity_y = -8

        #print(self.player.x)
        #print(self.car.x)

        if (self.car.x == self.player.x):        
            if (self.car.y<=115):
                global vivo
                vivo = False
        if (not vivo):
            print("F")
            quit()

        """
        # went off to a side to score point?
        if self.car.right > self.width:
            self.player.score += 1
            self.serve_car(vel=(-4, 0))
        """

    def on_touch_move(self, touch):
        if touch.x < self.width / 3:
            self.player.center_x = self.x+pos
        if touch.x > self.width / 3 and touch.x < self.width - self.width / 3:
            self.player.center_x = self.center_x
        if touch.x > self.width - self.width / 3:
            self.player.center_x = self.width-pos

class GameApp(App):
    def build(self):
        Config.set('graphics', 'width', '450')
        Config.set('graphics', 'height', '800')
        game = Game()
        game.serve_car()
        Clock.schedule_interval(game.update, 1.0 / 60.0)
        return game


if __name__ == '__main__':
    GameApp().run()