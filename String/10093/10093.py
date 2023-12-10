while (1):
    try:
        inputStr = input()
        nums = []
        for i in range(0, len(inputStr)):
            if (not inputStr[i].isalnum()):
                continue
            
            if (inputStr[i].isalpha()):
                if (inputStr[i].isupper()):
                    nums.append(ord(inputStr[i]) - ord('A') + 10)
                else:
                    nums.append(ord(inputStr[i]) - ord('a') + 26 + 10)
            else:
                nums.append(ord(inputStr[i]) - ord('0'))
                    
        ok = True
        for base in range(2, 63):
            ok = True
            total = 0
            baseNow = 1
            for num in nums:
                if (base <= num):
                    ok = False
                    break
                total += num * baseNow
                baseNow *= base
            if (not ok):
                continue
            if (total % (base - 1) != 0):
                ok = False
                continue
            print(base)
            break
        
        if (not ok):
            print("such number is impossible!")
    
    except EOFError:
        break