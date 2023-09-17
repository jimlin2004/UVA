import math

while (1):
    try:
        x = int(input())
        print(f"{x}!")
        print(math.factorial(x))
    except EOFError:
        break