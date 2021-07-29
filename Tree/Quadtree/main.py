#!/usr/bin/env python

from quad_tree import QuadTree
from datatypes import Point, Node

import matplotlib.pyplot as plt
import random

from collections import deque
import numpy as np


def get_random_pts(num_pts):
    pts = []
    for i in range(num_pts):
        xr = random.uniform(1, 9)
        yr = random.uniform(1, 9)
        pts.append((xr, yr))

    return pts


def get_circle_pts(step=np.pi / 10, rad=3):
    center = (5, 5)

    pts = []
    angle = 0
    while(angle < 2 * np.pi):
        xr = rad * np.cos(angle) + center[0]
        yr = rad * np.sin(angle) + center[1]
        pts.append((xr, yr))

        angle += step

    return pts


def main():
    # Create a quad
    qt = QuadTree(top_left=Point(0, 0), bot_right=Point(10, 10))

    fig, ax = plt.subplots()

    # Generate random points between 1-9
    # num_pts = 10
    # rand_pts = get_random_pts(num_pts)
    circle_pts = get_circle_pts()

    for (xr, yr) in circle_pts:
        ax.plot(xr, yr, 'bo')
        qt.insert(
            Node(
                Point(xr, yr)
            )
        )

    ax.set_xlim([-1, 11])
    ax.set_ylim([-1, 11])
    ax.set_aspect('equal')

    # Need to do a DFS
    q = deque()
    q.append(qt)
    while(q):
        front = q.popleft()
        rect = front.quad.get_viz_rect()
        ax.add_patch(rect)

        # Iterate through neighbours
        if front.top_left_tree:
            q.append(front.top_left_tree)
        if front.top_right_tree:
            q.append(front.top_right_tree)
        if front.bot_left_tree:
            q.append(front.bot_left_tree)
        if front.bot_right_tree:
            q.append(front.bot_right_tree)

    plt.show()


if __name__ == '__main__':
    main()
