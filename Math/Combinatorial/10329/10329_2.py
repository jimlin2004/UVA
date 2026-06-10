# 運用技巧反而過不去time limit

import math

not_prime = [False] * 5005
not_prime[0] = True
not_prime[1] = True
primes = []


def process_prime(x, list_of_primes, add_num = 1):
    for p in primes:
        if (x == 1):
            break
        while (x % p == 0):
            x //= p
            list_of_primes[p] += add_num


def process_fact_prime(x, list_of_primes, add_num = 1):
    for i in range(2, x + 1):
        process_prime(i, list_of_primes, add_num)


if (__name__ == "__main__"):

    for i in range(2, 5005):
        if (not not_prime[i]):
            primes.append(i)
            for j in range(i * i, 5005, i):
                not_prime[j] = True
    
    while (1):
        try:
            n, m = list(map(int, input().split()))

            num_count = [0] * 5005
            
            for i in range(n):
                n, r = list(map(int, input().split()))

                process_fact_prime(n, num_count, 1)
                process_fact_prime(r, num_count, -1)
                process_fact_prime(n - r, num_count, -1)
            
            for i in range(m):
                n, r = list(map(int, input().split()))

                process_fact_prime(n, num_count, -1)
                process_fact_prime(r, num_count, 1)
                process_fact_prime(n - r, num_count, 1)

            ok = True
            res = 1

            for p in range(2, 5005):
                if (num_count[p] < 0):
                    ok = False
                    break
                elif (num_count[p] > 0):
                    res *= pow(p, num_count[p])

            if (ok):
                if (math.log10(res) >= 100):
                    print(-1)
                else:
                    print(res)
            else:
                print(0)
            

        except EOFError:
            break
