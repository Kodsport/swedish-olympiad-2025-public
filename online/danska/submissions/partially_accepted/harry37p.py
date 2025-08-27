#!/usr/bin/env python3
#@EXPECTED_GRADES@ AC WA AC WA WA

# O(n^2m)
# with some bug. 

MOD = 10**9+7

n,m = map(int,input().split())

words = [input() for _ in range(m)]

trie = [{}]
done = [0]
char = [""]
cnt = [1]

for word in words:
    curr = 0
    for x in word:
        if x in trie[curr]:
            curr = trie[curr][x]
        else:
            ind = len(trie)
            trie.append({})
            done.append(0)
            char.append(x)
            cnt.append(0)
            trie[curr][x] = ind
            curr = ind
    done[curr] = 1


# Build fail-edges

alfa = [chr(x) for x in range(ord("a"),ord("z")+1)]

for word in words:
    choices = []
    main = 0
    for ch in word:
        nxt = []

        main = trie[main][ch]
        for cand in choices:
            if ch in trie[cand]:
                nxt.append(trie[cand][ch])
        nxt,choices = choices,nxt
        
        choices.append(0)

        for alf in alfa:
            conn = -1
            if alf in trie[main]:
                continue
            for cand in choices:
                if alf in trie[cand]:
                    conn = trie[cand][alf]
                    break
            if conn != -1:
                trie[main][alf] = conn
    

for _ in range(n):
    nxt = [0]*len(trie)
    for i in range(len(trie)):
        if cnt[i]:
            for ch in trie[i]:
                if done[trie[i][ch]]:
                    continue
                nxt[trie[i][ch]] += 1*cnt[i]
                nxt[trie[i][ch]] %= MOD
            nxt[0] += (26 - len(trie[i]))*cnt[i]
            nxt[0] %= MOD
    nxt,cnt = cnt,nxt

print(sum(cnt)%MOD)

