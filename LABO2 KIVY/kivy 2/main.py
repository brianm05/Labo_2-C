from kivy.app import App
from kivy.uix.widget import Widget
from kivy.properties import (
    NumericProperty, ReferenceListProperty, ObjectProperty
)
from kivy.vector import Vector
from kivy.clock import Clock
from kivy.config import Config

import random

pos=75

enemyPos=50

class Player(Widget):
    score = NumericProperty(0)

    def bounce_ball(self, ball):
        if self.collide_widget(ball):
            vx, vy = ball.velocity
            offset = (ball.center_y - self.center_y) / (self.height / 2)
            bounced = Vector(-1 * vx, vy)
            vel = bounced * 1.1
            ball.velocity = vel.x, vel.y + offset

class Enemy(Widget):
    velocity_x = NumericProperty(0)
    velocity_y = NumericProperty(0)
    velocity = ReferenceListProperty(velocity_x, velocity_y)

    def move(self):
        self.pos = Vector(*self.velocity) + self.pos

class Game(Widget):
    ball = ObjectProperty(None)
    player1 = ObjectProperty(None)

    def serve_ball(self, vel=(0, -4)):
        self.ball.center = self.center
        self.ball.velocity = vel

    def update(self, dt):

        self.ball.move()

        aumentarNivel=5

        # bounce off paddles
        self.player1.bounce_ball(self.ball)

        """
        # bounce ball off bottom or top
        if (self.ball.y < self.y) or (self.ball.top > self.top):
            self.ball.velocity_y *= -1
        """
        
        if self.ball.y < self.y-50:
            self.ball.y = self.height
            test=(self.width-2*enemyPos,
                  self.center_x-25,
                  self.x+enemyPos)
            eleccion=random.choice(test)
            self.ball.x=eleccion
            self.player1.score += 1

        if self.player1.score == aumentarNivel:
            self.ball.velocity_y = -8

        """
        # went off to a side to score point?
        if self.ball.right > self.width:
            self.player1.score += 1
            self.serve_ball(vel=(-4, 0))
        """

    def on_touch_move(self, touch):
        if touch.x < self.width / 3:
            self.player1.center_x = self.x+pos
        if touch.x > self.width / 3 and touch.x < self.width - self.width / 3:
            self.player1.center_x = self.center_x
        if touch.x > self.width - self.width / 3:
            self.player1.center_x = self.width-pos

class GameApp(App):
    def build(self):
        Config.set('graphics', 'width', '450')
        Config.set('graphics', 'height', '800')
        game = Game()
        game.serve_ball()
        Clock.schedule_interval(game.update, 1.0 / 60.0)
        return game


if __name__ == '__main__':
    GameApp().run()