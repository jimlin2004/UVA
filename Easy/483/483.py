def main():
    while(1):
        try:
            s = input()
            texts = s.split(" ")
            first = True
            for text in texts:
                if (first):
                    first = False
                else:
                    print(" ", end = "")
                print(text[::-1], end="")
            print()
        except EOFError:
            break
main()