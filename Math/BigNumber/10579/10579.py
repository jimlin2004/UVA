fib = [0] * 100000

fib[1] = 1
fib[2] = 2
for i in range(3, 100000):
    fib[i] = fib[i - 1] + fib[i - 2]

while (1):
    try:
        x = int(input())
        print(fib[x - 1])
    except EOFError:
        break