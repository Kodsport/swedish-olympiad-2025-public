#!/usr/bin/python3

# Pyrival segment tree
class SegmentTree:
    def __init__(self, data, default=(-1, -1), func=max):
        """initialize the segment tree with data"""
        self._default = default
        self._func = func
        self._len = len(data)
        self._size = _size = 1 << (self._len - 1).bit_length()

        self.data = [default] * (2 * _size)
        self.data[_size:_size + self._len] = data
        for i in reversed(range(_size)):
            self.data[i] = func(self.data[i + i], self.data[i + i + 1])

    def __delitem__(self, idx):
        self[idx] = self._default

    def __getitem__(self, idx):
        return self.data[idx + self._size]

    def __setitem__(self, idx, value):
        idx += self._size
        self.data[idx] = value
        idx >>= 1
        while idx:
            self.data[idx] = self._func(self.data[2 * idx], self.data[2 * idx + 1])
            idx >>= 1

    def __len__(self):
        return self._len

    def query(self, start, stop):
        """func of data[start, stop)"""
        start += self._size
        stop += self._size

        res_left = res_right = self._default
        while start < stop:
            if start & 1:
                res_left = self._func(res_left, self.data[start])
                start += 1
            if stop & 1:
                stop -= 1
                res_right = self._func(self.data[stop], res_right)
            start >>= 1
            stop >>= 1

        return self._func(res_left, res_right)

    def __repr__(self):
        return "SegmentTree({0})".format(self.data)

block_size = 1000

n, q = [int(i) for i in input().split()]
h = [int(i) for i in input().split()]

tree = SegmentTree([(h[i], i) for i in range(n)])

for _ in range(q):
    t, a, b = [int(i) for i in input().split()]
    if t==1:
        l, r = a-1, b-1
        ans = 0
        idx = tree.query(l, r+1)[1]
        ans = 0
        prefmax = -1
        for i in range(l, idx):
            prefmax = max(prefmax, h[i])
            ans += prefmax - h[i]
        prefmax = 0
        for i in range(r, idx - 1, -1):
            prefmax = max(prefmax, h[i])
            ans += prefmax - h[i]
        print(ans)
    else:
        ind = a-1
        h[ind] += b
        tree[ind] = (h[ind], ind)
