import math

import matplotlib.pyplot as plt

n = 200
tbprd = 7500
m = 1

sin_table_epwm1 = [0] * n
print("sin_table_epwm1[N] = {", end="")
for i in range(0, n):
    sin_table_epwm1[i] = int(tbprd * ((1 + m * math.sin((2 * math.pi * i) / n)) / 2))
    print(f"{sin_table_epwm1[i]}", end="")

    if (i == n - 1):
        print("}", end="")
    else:
        print(", ", end="")

print("\n")

sin_table_epwm2 = [0] * n
print("sin_table_epwm2[N] = {", end="")
for i in range(0, n):
    sin_table_epwm2[i] = int(tbprd * ((1 + m * math.sin(((2 * math.pi * i) / n) - (2 * math.pi / 3))) / 2))
    print(f"{sin_table_epwm2[i]}", end="")

    if (i == n - 1):
        print("}", end="")
    else:
        print(", ", end="")

print("\n")

sin_table_epwm3 = [0] * n
print("sin_table_epwm3[N] = {", end="")
for i in range(0, n):
    sin_table_epwm3[i] = int(tbprd * ((1 + m * math.sin(((2 * math.pi * i) / n) - (3 * math.pi / 2))) / 2))
    print(f"{sin_table_epwm3[i]}", end="")

    if (i == n - 1):
        print("}", end="")
    else:
        print(", ", end="")
    

x_value = range(0, n)
plt.plot(x_value, sin_table_epwm1)
plt.plot(x_value, sin_table_epwm2)
plt.plot(x_value, sin_table_epwm3)
plt.show() 