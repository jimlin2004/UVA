fib = [0] * 5005
fib[0] = 0
fib[1] = 1

for i in range(2, 5005):
    fib[i] = fib[i - 1] + fib[i - 2]

while (1):
    try:
        n = int(input())
        print(f"The Fibonacci number for {n} is {fib[n]}")
    except EOFError:
        break