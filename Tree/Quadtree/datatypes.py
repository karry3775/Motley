#!/usr/bin/env python

from matplotlib.patches import Rectangle


class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y


class Node:
    def __init__(self, pos=Point()):
        self.pos = pos


class Quad:
    def __init__(self, top_left=Point(), bot_right=Point()):
        self.top_left = top_left
        self.bot_right = bot_right

    def in_boundary(self, pos):
        return (
            pos.x > self.top_left.x and pos.x < self.bot_right.x and
            pos.y > self.bot_right.y and pos.y < self.top_left.y
        )

    def is_dividable(self):
        # Has to be more than unit area
        return (
            abs(self.top_left.x - self.bot_right.x) >= 1 and
            abs(self.top_left.y - self.bot_right.y) >= 1
        )

    def is_within_top_left(self, pos):
        return (
            pos.x > self.top_left.x and pos.x < (self.top_left.x + self.bot_right.x) / 2.0 and
            pos.y > self.top_left.y and pos.y < (self.top_left.y + self.bot_right.y) / 2.0
        )

    def is_within_top_right(self, pos):
        return (
            pos.x > (self.top_left.x + self.bot_right.x) / 2.0 and pos.x < self.bot_right.x and
            pos.y > self.top_left.y and pos.y < (self.top_left.y + self.bot_right.y) / 2.0
        )

    def is_within_bot_left(self, pos):
        return (
            pos.x > self.top_left.x and pos.x < (self.top_left.x + self.bot_right.x) / 2.0 and
            pos.y > (self.top_left.y + self.bot_right.y) / 2.0 and pos.y < self.bot_right.y
        )

    def is_within_bot_right(self, pos):
        return (
            pos.x > (self.top_left.x + self.bot_right.x) / 2.0 and pos.x < self.bot_right.x and
            pos.y > (self.top_left.y + self.bot_right.y) / 2.0 and pos.y < self.bot_right.y
        )

    def get_top_left(self):
        return Quad(
            top_left=self.top_left,
            bot_right=Point(
                (self.top_left.x + self.bot_right.x) / 2.0,
                (self.top_left.y + self.bot_right.y) / 2.0
            )
        )

    def get_top_right(self):
        return Quad(
            top_left=Point(
                (self.top_left.x + self.bot_right.x) / 2.0,
                self.top_left.y
            ),
            bot_right=Point(
                self.bot_right.x,
                (self.top_left.y + self.bot_right.y) / 2.0
            )
        )

    def get_bot_left(self):
        return Quad(
            top_left=Point(
                self.top_left.x,
                (self.top_left.y + self.bot_right.y) / 2.0
            ),
            bot_right=Point(
                (self.top_left.x + self.bot_right.x) / 2.0,
                self.bot_right.y
            )
        )

    def get_bot_right(self):
        return Quad(
            top_left=Point(
                (self.top_left.x + self.bot_right.x) / 2.0,
                (self.top_left.y + self.bot_right.y) / 2.0
            ),
            bot_right=self.bot_right
        )

    def get_viz_rect(self):
        return Rectangle((self.top_left.x, self.top_left.y),
                         abs(self.top_left.x - self.bot_right.x),
                         abs(self.top_left.y - self.bot_right.y),
                         lw=2,
                         edgecolor='red',
                         facecolor='none'
                         )
