from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.uix.screenmanager import ScreenManager, Screen
import subprocess

class MenuScreen(BoxLayout):
    def __init__(self, **kwargs):
        super(MenuScreen, self).__init__(**kwargs)
        #self.orientation = 'vertical'
        
        self.add_widget(Label(text='Bienvenido al Juego.'))
        play_button = Button(text='Play')
        play_button.bind(on_press=self.start_game)
        self.add_widget(play_button)
        
    def start_game(self, instance):
        subprocess.Popen(["python", "main.py"])

class MenuApp(App):
    def build(self):
        return MenuScreen()

if __name__ == '__main__':
    MenuApp().run()
