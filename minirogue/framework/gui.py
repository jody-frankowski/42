from framework.gameobject import *
import curses

class Text():
    def __init__(self, text, x, y):
        self.value = str(text)
        self.x = x
        self.y = y

class Gui():
    def __init__(self, win):
        self.win = win
        self.texts = []

    def draw(self):
        self.win.erase()
        self.win.box()
        for text in self.texts:
            self.win.addstr(text.y, text.x, text.value)
        self.texts.clear()

    def setText(self, text):
        self.texts.append(text)
