#!/usr/bin/env python3

from math import pi, asin

"""
    Считаем реальную площадь объединения аналитически: 0.25·π+ 1.25·arcsin(0.8)−1
"""
def calculate_square():
    return 0.25 * pi + 1.25 * asin(0.8) - 1

print(calculate_square())