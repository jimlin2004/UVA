arr = [0 for i in range(0, 1005)]
arr[2] = arr[3] = 1
for i in range(4, 1005):
    if (i % 2 == 0):
        arr[i] = arr[i - 1] * 2 + 1
    else:
        arr[i] = arr[i - 1] * 2 - 1

while (1):
    try:
        n = int(input())
        print(arr[n])
    except EOFError:
        break