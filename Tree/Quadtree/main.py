#!/usr/bin/env python

from quad_tree import QuadTree
from datatypes import Point, Node

import matplotlib.pyplot as plt
import random

from collections import deque


def main():
    # Create a quad
    qt = QuadTree(top_left=Point(0, 0), bot_right=Point(10, 10))

    fig, ax = plt.subplots()

    # Generate random points between 1-9
    num_pts = 100
    pts = []
    for i in range(num_pts):
        xr = random.uniform(1, 9)
        yr = random.uniform(1, 9)
        pts.append((xr, yr))
        ax.plot(pts[-1][0], pts[-1][1], 'bo')

        # Add points to to the quad tree
        qt.insert(
            Node(Point(
                xr, yr
            ))
        )

    ax.set_xlim([-1, 11])
    ax.set_ylim([-1, 11])

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
