#!/usr/bin/env python3
# O(n^2m)


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
        tempCurr = trie[curr]

        if x in tempCurr:
            curr = tempCurr[x]
        else:
            ind = len(trie)
            trie.append({})
            done.append(0)
            char.append(x)
            cnt.append(0)
            tempCurr[x] = ind
            curr = ind
    done[curr] = 1


for i in range(len(trie)):
    if done[i]:
        trie[i] = {}

# Build fail-edges in the trie

alfa = [chr(x) for x in range(ord("a"),ord("z")+1)]

for word in words:
    choices = []
    main = 0
    for ch in word:

        nxt = []

        main = trie[main][ch]
        if done[main]:
            break

        for cand in choices:
            if ch in trie[cand]:
                nxt.append(trie[cand][ch])
        nxt,choices = choices,nxt
        
        choices.append(0)

        tempTrie = trie[main]
        for alf in alfa:

            conn = -1
            bad = 0
            if alf in tempTrie:
                conn = tempTrie[alf]
            for cand in choices:
                tempCand = trie[cand]
                if alf in tempCand:
                    if conn == -1:
                        conn = tempCand[alf]
                    if done[tempCand[alf]]:
                        bad = 1
                        
            if conn != -1:
                tempTrie[alf] = conn
                if bad:
                    done[tempTrie[alf]] = 1

for _ in range(n):
    nxt = [0]*len(trie)
    for i in range(len(trie)):

        currcnt = cnt[i]
        currTrie = trie[i]
        
        if currcnt:
            for ch in currTrie:
                currCh = currTrie[ch]
                if done[currCh]:
                    continue
                nxt[currCh] += 1*currcnt
                nxt[currCh] %= MOD
            nxt[0] += (26 - len(currTrie))*currcnt
            nxt[0] %= MOD

    nxt,cnt = cnt,nxt

print(sum(cnt)%MOD)


