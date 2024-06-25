while (1):
    try:
        x = int(input())
        y = int(input())
        print(x * y)
    except EOFError:
        break