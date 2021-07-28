#!/usr/bin/env python

# Based on:
# https://www.geeksforgeeks.org/quad-tree/

from datatypes import Point, Node, Quad


class QuadTree:
    def __init__(self, top_left=Point(), bot_right=()):
        self.quad = Quad(top_left, bot_right)

        # Node
        self.node = None

        # Children of this node
        self.top_left_tree = None
        self.top_right_tree = None
        self.bot_left_tree = None
        self.bot_right_tree = None

    def insert(self, node):
        if node:
            # Assign node to the quadtree if we
            # can't subdivide further
            if not self.is_dividable():
                if not self.node:
                    self.node = node
                return

            # Assign to one of its children
            if self.quad.is_within_top_left(node.pos):
                self.top_left_tree = QuadTree(
                    quad=self.quad.get_top_left()
                )
                self.top_left_tree.insert(node)

            elif self.quad.is_within_top_right(node.pos):
                self.top_right_tree = QuadTree(
                    quad=self.quad.get_top_right()
                )
                self.top_right_tree.insert(node)

            elif self.quad.is_within_bot_left(node.pos):
                self.bot_left_tree = QuadTree(
                    quad=self.quad.get_bot_left()
                )
                self.bot_left_tree.insert(node)

            elif self.quad.is_within_bot_right(node.pos):
                self.bot_right_tree = QuadTree(
                    quad=self.quad.get_bot_right()
                )
                self.bot_right_tree.insert(node)

        return

    def search(self, pos):
        # TODO
        return self.node
