#!/bin/python3

import math

def main():
    nx = 800
    ny = 600
    print("P3\n" + str(nx) + " " + str(ny) + "\n255\n")
    for j in range(ny, 0, -1):
        for i in range(0, nx):
            r = i / nx
            g = j / ny
            b = 0.2;
            intr = math.floor(255.99 * r)
            intg = math.floor(255.99 * g)
            intb = math.floor(255.99 * b)
            print(str(intr) + " " + str(intg) + " " + str(intb) + "\n")

if __name__ == "__main__":
    main()
