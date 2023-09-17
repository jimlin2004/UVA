import bisect

nums = []

while (1):
    try:
        x = int(input())
        insertionPos = bisect.bisect_left(nums, x, 0, len(nums))
        nums.insert(insertionPos, x)
        midIndex = (len(nums)) // 2
        midIndex = max(0, midIndex)
        if (len(nums) % 2 == 0):
            print((nums[midIndex - 1] + nums[midIndex]) // 2)
        else:
            print(nums[midIndex])
    except EOFError as e:
        break