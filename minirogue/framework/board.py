#!/usr/bin/env python3

from framework.gameobject import *
from queue import Queue
from pprint import pprint

import copy
import random


import sys

MAP_HEIGHT = 75
MAP_WIDTH = 75
# TODO Center Window
WIN_X = 0
WIN_Y = 0

def neighbors(current, obstacles):
    neighbors = []
    if current[0] - 1 >= 0 and (current[0] - 1, current[1]):
        neighbors += [(current[0] - 1, current[1])]
    if current[0] + 1 <= MAP_WIDTH - 1 and (current[0] + 1, current[1]):
        neighbors += [(current[0] + 1, current[1])]
    if current[1] - 1 >= 0 and (current[0], current[1] - 1):
        neighbors += [(current[0], current[1] - 1)]
    if current[1] + 1 <= MAP_HEIGHT - 1 and (current[0], current[1] + 1):
        neighbors += [(current[0], current[1] + 1)]

    for obstacle in obstacles:
        if obstacle in neighbors:
            neighbors.remove(obstacle)

    return neighbors

def get_points_of_rooms(rooms):
    points = []
    for room in rooms:
        for tile in room.tiles:
            points += [tile]
        for wall in room.walls:
            points += [wall]
    return points

def path_find(start, end, obstacles):
    frontier = Queue()
    frontier.put(start)

    came_from = {}
    came_from[start] = None

    while not frontier.empty():
        current = frontier.get()
        if current == end:
            break
        for next in neighbors(current, obstacles):
            if next not in came_from:
                frontier.put(next)
                came_from[next] = current

    if not came_from or end not in came_from:
        return []

    current = end
    path = []
    while current != start:
        path = [current] + path
        current = came_from[current]

    return path[:-1]

class Board():
    def __init__(self):
        self.all = {}
        self.hallways = []
        self.obstacles = []
        self.rooms = []

    def addRoom(self):
        MIN = 10
        MAX = 30

        while True:
            random_width = random.randint(MIN, MAX)
            random_height = random.randint(MIN, MAX)

            random_x = random.randint(2, MAP_WIDTH - random_width - 3)
            random_y = random.randint(2, MAP_HEIGHT - random_height - 3)

            room = Room(random_x, random_y, random_width, random_height)
            if self.roomCollides(room):
                continue
            else:
                self.rooms += [room]
                self.updateAll()
                self.updateObstacles()
                break

    def connectRoom(self, roomA, roomB):
        wallsA = list(roomA.walls.keys())
        random.shuffle(wallsA)
        wallsB = list(roomB.walls.keys())
        random.shuffle(wallsB)
        for wallA in wallsA:
            if not roomA.isCorner(wallA[0], wallA[1]):
                for wallB in wallsB:
                    if not roomB.isCorner(wallB[0], wallB[1]):
                        obstacles = copy.deepcopy(self.obstacles)
                        obstacles.remove(wallA)
                        obstacles.remove(wallB)
                        if len(path_find(wallA, wallB, obstacles)) > 0:
                            roomA.addDoor(wallA[0], wallA[1])
                            roomB.addDoor(wallB[0], wallB[1])
                            hallway = Hallway(wallA, wallB, obstacles)
                            self.hallways += [hallway]
                            self.updateAll()
                            self.updateObstacles()
                            return True

        return False

    def connectRooms(self):
        for i in range(len(self.rooms) - 1):
            if not self.connectRoom(self.rooms[i], self.rooms[i + 1]):
                print("unlucky gangbang!", file=sys.stderr)
                pass

    def roomCollides(self, room):
        for point in get_points_of_rooms([room]):
            if point in self.obstacles:
                return True

    def updateAll(self):
        self.all = {}
        for room in self.rooms:
            self.all.update(room.doors)
            self.all.update(room.tiles)
            self.all.update(room.walls)
        for hallway in self.hallways:
            self.all.update(hallway.tiles)

    def updateObstacles(self):
        self.obstacles = get_points_of_rooms(self.rooms)


class Hallway():
    def __init__(self, start, end, obstacles):
        self.tiles = {}
        for point in path_find(start, end, obstacles):
            tile = Tile(point[0], point[1])
            tile.setSym("░")
            self.tiles[(point[0], point[1])] = tile

class Room():
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.doors = {}
        self.tiles = {}
        self.walls = {}

        for x in range(self.x, self.x + width):
            wall = Wall(x, self.y)
            self.walls[(x, self.y)] = wall

            wall = Wall(x, self.y + height - 1)
            self.walls[(x, self.y + height - 1)] = wall

        for y in range(self.y, self.y + height):
            wall = Wall(self.x, y)
            self.walls[(self.x, y)] = wall

            wall = Wall(self.x + width - 1, y)
            self.walls[(self.x + width - 1, y)] = wall

        for x in range(self.x + 1, self.x + width - 1):
            for y in range(self.y + 1, self.y + height - 1):
                tile = Tile(x, y)
                self.tiles[(x, y)] = tile

    def addDoor(self, x, y):
        self.walls.pop((x, y))
        self.doors[(x, y)] = Door(x, y)

    def isCorner(self, x, y):
        return (x == self.x and y == self.y) or \
            (x == self.x + self.width - 1 and y == self.y) or \
            (x == self.x + self.width - 1 and y == self.y + self.height - 1) or \
            (x == self.x and y == self.y + self.height - 1)
