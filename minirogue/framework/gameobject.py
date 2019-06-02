#!/usr/bin/env python3
# coding: utf-8
import random, json, curses, math
from pprint import pprint

class Level():
    def __init__(self):
        self.d = []
        lvl = 1
        coeff = 1.0
        while lvl < 51:
            if lvl % 10 == 0:
                coeff += 1
            log = 100 * math.pow(1.05, lvl)
            hp, xp = (int(log), int(log * coeff))
            self.d.append((hp, xp))
            lvl += 1

    def getlvl(self, lvl):
        return self.d[lvl - 1]

###########################################################

class GameObject():
	def __init__(self, x = 0, y = 0):
		self.x = x
		self.y = y
		self.hidden = False
		self.sym = None

	def setSym(self, sym):
		self.sym = sym

	def setHidden(self, hidden):
		self.hidden = hidden

	def setPosition(self, x, y):
		self.x = x
		self.y = y

	def getPosition(self):
		return (self.x, self.y)

	def isHidden(self):
		return self.hidden

	def destroy(self):
		del(self)

############################################################

class LivingObject(GameObject):
	def __init__(self, x = 0, y = 0):
		super().__init__(x, y)
		self.level = 1

	def collide(self, gameObject):
		return self.x == gameObject.x and self.y == gameObject.y

	def move(self, x, y):
		self.setPosition(x, y)

	def attack(self, livingObject):
		livingObject.modifyHp(-self.damage)
		return self.damage

	def modifyHp(self, hp):
		self.hp += hp
		if self.hp <= 0:
			self.hp = 0
			self.destroy()
		if self.hp > self.maxHp:
			self.hp = self.maxHp

	def setHp(self, hp):
		self.hp = hp
		self.setMaxHp(hp)

	def setMaxHp(self, maxHp):
		self.maxHp = maxHp

	def setDamage(self, damage):
		self.damage = damage

############################################################


class Monster(LivingObject):
	def __init__(self, x = 0, y = 0):
		super().__init__(x, y)

	def setAtk(self, minAtk, maxAtk):
		self.minAtk = minAtk
		self.maxAtk = maxAtk

	def setCritChance(self, critChance):
		self.critChance = critChance

	def setCritCoeff(self, critCoeff):
		self.critCoeff = critCoeff

	def updateDamage(self):
		dmg = random.randint(self.minAtk, self.maxAtk)
		rand = random.randint(0, 100)
		if self.critChance >= rand:
			dmg *= self.critCoeff
		super().setDamage(int(round(dmg)))

	def setName(self, name):
		self.name = name

	def setXpGiven(self, xp):
		self.xp = xp

	def move(self, x, y):
		self.updateDamage()
		self.setPosition(x, y)

	def draw(self, win):
		win.addstr(self.y, self.x, self.sym, curses.color_pair(2))


############################################################

class Player(LivingObject, Level):
	def __init__(self, x = 0, y = 0):
		LivingObject.__init__(self, x, y)
		Level.__init__(self)
		self.setSym('\u263A')
		self.gold = 0
		self.foods = []
		self.weapons = []
		self.setHp(500 + self.getlvl(1)[0])
		self.setMaxHp(self.hp)
		self.setDamage(30)
		self.level = 1
		self.equippedWeapon = None
		self.xp = 0
		self.xpMax = self.getlvl(1)[1]

	def eat(self, food):
		self.modifyHp(food.hpGiven)
		self.delItem(food)

	def addItem(self, item):
		if isinstance(item, Food):
			self.foods.append(item)
		if isinstance(item, Weapon):
			for i in self.weapons:
				if i.name == item.name:
					return
			self.weapons.append(item)
		if isinstance(item, Gold):
			self.gold += item.amount

	def delItem(self, item):
		if isinstance(item, Food):
			self.foods.remove(item)
		if isinstance(item, Weapon):
			self.weapons.remove(item)

	def equip(self, item):
		self.weapons.remove(item)
		if self.equippedWeapon != None:
			self.weapons.append(self.equippedWeapon)
		self.equippedWeapon = item

	def attack(self, livingObject):
		dmg = self.damage
		if self.equippedWeapon:
			dmg += random.randint(self.equippedWeapon.minAtk, self.equippedWeapon.maxAtk)
			rand = random.randint(0, 100)
			if self.equippedWeapon.critChance >= rand:
				dmg *= self.equippedWeapon.critCoeff
		dmg = int(round(dmg))
		livingObject.modifyHp(-dmg)
		if livingObject.hp <= 0:
			self.levelUp(livingObject.xp)
		return dmg

	def levelUp(self, xp):
		self.xp += xp
		if self.xp >= self.xpMax:
			self.level += 1
			newlevel = self.getlvl(self.level)
			self.xp = 0
			self.xpMax = newlevel[1]
			self.setHp(self.maxHp + newlevel[0])
			self.damage *= 1.15

	def regen(self, clock):
		if clock % 20 == 0:
			self.modifyHp(1)

	def draw(self, win):
		win.addstr(self.y, self.x, self.sym, curses.color_pair(1))

	def __str_inventory__(self):
		str0 = 'Your Inventory:\n'
		if self.foods != []:
			str0 += '\n'.join(['\tFood:']+["\t\t{} : {}".format(x.name, x.description) for x in self.foods])
			str0 += '\n'
		if self.weapons != []:
			str0 += '\n'.join(['\tWeapons:']+["\t\t{} : {}".format(x.name, x.description) for x in self.weapons])
			str0 += '\n'
		if self.weapons == [] and self.foods == []:
			str0 += '\tYour Inventory is Empty!\n'
		str0 += ' Your Gold: {}\n'.format(self.gold)
		str0 += ' Your Health: {}\n'.format(self.hp)
		return str0
############################################################

class Door(GameObject):
	def __init__(self, x, y, sym = "+"):
		super().__init__(x, y)
		self.sym = sym
	def draw(self, win):
		win.addstr(self.y, self.x, self.sym, curses.color_pair(6))
############################################################

class Tile(GameObject):
	def __init__(self, x, y, sym = "·"):
		super().__init__(x, y)
		self.sym = sym

	def draw(self, win):
		win.addstr(self.y, self.x, self.sym, curses.color_pair(6))

############################################################

class Wall(GameObject):
	def __init__(self, x, y, sym = "█"):
		super().__init__(x, y)
		self.sym = sym
	def draw(self, win):
		win.addstr(self.y, self.x, self.sym, curses.color_pair(7))

############################################################

class Item(GameObject):
	def __init__(self, x, y):
		super().__init__(x, y)
		self.setDescription("unknown description")
		self.setName("unknown name")

	def setName(self, name):
		self.name = name

	def setDescription(self, description):
		self.description = description

############################################################

class Food(Item):
	def __init__(self, x, y):
		super().__init__(x, y)

	def setHpGiven(self, hp):
		self.hpGiven = hp

	def draw(self, win):
		win.addstr(self.y, self.x, self.sym, curses.color_pair(5))

############################################################

class Weapon(Item):
	def __init__(self, x, y):
		super().__init__(x, y)
		self.critChance = 0
		self.critCoeff = 1.5

	def setAtk(self, minAtk, maxAtk):
		self.minAtk = minAtk
		self.maxAtk = maxAtk

	def setCritChance(self, crit):
		self.critChance = crit

	def setCritCoeff(self, critCoeff):
		self.critCoeff = critCoeff

	def draw(self, win):
		win.addstr(self.y, self.x, self.sym, curses.color_pair(4))

############################################################

class Gold(Item):
	def __init__(self, x, y):
		super().__init__(x, y)

	def setAmount(self, amount, maxAmount = 0):
		if maxAmount <= 0:
			self.amount = amount
		else:
			self.amount = random.randint(amount, maxAmount)

	def draw(self, win):
		win.addstr(self.y, self.x, self.sym, curses.color_pair(3))

############################################################
