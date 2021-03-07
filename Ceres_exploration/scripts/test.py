#!/usr/bin/env python

import matplotlib.pyplot as plt

if __name__ == "__main__":

    circle_data_filename = "/home/kartik/Documents/Motley/Ceres_exploration/data/circle_data.txt"

    x_data = []
    y_data = []

    with open(circle_data_filename, "r") as f:
        for line in f:
            data = line.split(",")

            x_data.append(float(data[0]))
            y_data.append(float(data[1]))

    circle = plt.Circle((0.533913, 0.518611), 2.99839, color='r', fill=False)

    fig, ax = plt.subplots()
    ax.set_aspect("equal")
    ax.add_patch(circle)

    ax.plot(x_data, y_data)
    plt.show()
