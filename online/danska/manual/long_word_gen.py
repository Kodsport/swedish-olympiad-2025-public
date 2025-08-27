#!/usr/bin/python3
import random
import string

m = 150
n = 100

test_case = []
for _ in range(m):
    random_string = ''.join(random.choices(string.ascii_lowercase, k=n))
    test_case.append(random_string)

print(n,m)
print("\n".join(test_case))
