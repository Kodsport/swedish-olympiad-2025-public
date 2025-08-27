#!/usr/bin/python3
# Complexity: let b=block_size
# Update: ~O(6b)
# Query: ~O(2b+N/b*log(b)) (in expectation, the query endpoints will be in the middle of the block)


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


n, q = [int(i) for i in input().split()]
h = [int(i) for i in input().split()]

queries = []
num_updates = 0
for _ in range(q):
    t, a, b = [int(i) for i in input().split()]
    queries.append((t,a,b))
    if t==2:
        num_updates+=1

update_percent = num_updates/q
if update_percent > 0.5:
    block_size = 500
else:
    block_size = 900

while n % block_size != 0:
    n += 1
    h.append(0)

tree = SegmentTree([(h[i], i) for i in range(n)])

num_blocks = (n+block_size-1)//block_size

prefmax = [[0 for i in range(block_size)] for j in range(num_blocks)]
prefmaxcum = [[0 for i in range(block_size)] for j in range(num_blocks)]
prefsum = [[0 for i in range(block_size)] for j in range(num_blocks)]
sufmax = [[0 for i in range(block_size)] for j in range(num_blocks)]
sufmaxcum = [[0 for i in range(block_size)] for j in range(num_blocks)]
sufsum = [[0 for i in range(block_size)] for j in range(num_blocks)]


def update_block(block_ind):
    p = 0
    base = block_ind * block_size
    for i in range(block_size):
        p = max(p, h[i+base])
        prefmax[block_ind][i] = p
        prefsum[block_ind][i] = h[i+base]
        prefmaxcum[block_ind][i] = p-h[i+base]
        if i != 0:
            prefsum[block_ind][i] += prefsum[block_ind][i-1]
            prefmaxcum[block_ind][i] += prefmaxcum[block_ind][i-1]
    p = 0
    for i in range(block_size-1, -1, -1):
        p = max(p, h[i+base])
        sufmax[block_ind][i] = p
        sufsum[block_ind][i] = h[i+base]
        sufmaxcum[block_ind][i] = p-h[i+base]
        if i != block_size-1:
            sufsum[block_ind][i] += sufsum[block_ind][i+1]
            sufmaxcum[block_ind][i] += sufmaxcum[block_ind][i+1]

for block_ind in range(num_blocks):
    update_block(block_ind)


for _ in queries:
    t,a,b=_
    if t==1:
        l, r = a-1, b-1
        ans = 0
        idx = tree.query(l, r+1)[1]
        ans = 0

        # Left to middle
        l_block = l // block_size

        level = 0
        for i in range(l, min(idx, (l_block+1) * block_size)):
            level = max(level, h[i])
            ans += level - h[i]

        mid_block = idx // block_size
        for block_ind in range(l_block+1, mid_block):
            if level >= prefmax[block_ind][-1]:
                ans += level * block_size - prefsum[block_ind][-1]
            else:
                lo = -1
                hi = block_size
                while lo+1<hi:
                    mid = (lo+hi)//2
                    if prefmax[block_ind][mid] >= level:
                        hi = mid
                    else:
                        lo = mid
                ans += level*(lo+1)+prefmaxcum[block_ind][-1]
                if lo>=0:
                    ans -= prefsum[block_ind][lo]
                if hi>0:
                    ans -= prefmaxcum[block_ind][hi-1]

                level = prefmax[block_ind][-1]

        if l_block != mid_block:
            for i in range(mid_block*block_size, idx):
                level = max(level, h[i])
                ans += level - h[i]

        # Right to middle
        r_block = r // block_size
        level = 0
        for i in range(r, max(idx, r_block*block_size-1), -1):
            level = max(level, h[i])
            ans += level - h[i]
        
        for block_ind in range(r_block-1, mid_block, -1):
            if level >= sufmax[block_ind][0]:
                ans += level * block_size - sufsum[block_ind][0]
            else:
                lo = -1
                hi = block_size
                while lo+1<hi:
                    mid = (lo+hi)//2
                    if sufmax[block_ind][mid] >= level:
                        lo = mid
                    else:
                        hi = mid
                ans += level*(block_size-hi)+sufmaxcum[block_ind][0]
                if hi<block_size:
                    ans -= sufsum[block_ind][hi]
                    ans -= sufmaxcum[block_ind][hi]

                level = sufmax[block_ind][0]

        if r_block != mid_block:
            for i in range(min(n-1, (mid_block+1)*block_size-1), idx, -1):
                level = max(level, h[i])
                ans += level - h[i]


        print(ans)
    else:
        ind = a-1
        h[ind] += b
        tree[ind] = (h[ind], ind)
        update_block(ind//block_size)
