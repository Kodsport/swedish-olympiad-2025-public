#!/usr/bin/python3
def get_min(dsum, length, start):
    if length == 1:
        return dsum
    for d in range(start, 10):
        if dsum-d <= 9*(length-1):
            return d*10**(length-1) + get_min(dsum-d, length-1, 0)
    return -1

def get_max(dsum, length):
    if length == 1:
        return dsum
    d = min(9, dsum)
    return d*10**(length-1) + get_max(dsum-d, length-1)

n = input()
dsum = sum([int(d) for d in n])
length = len(n)
print(get_min(dsum, length, 1), get_max(dsum, length))
