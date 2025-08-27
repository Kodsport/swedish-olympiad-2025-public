#!/usr/bin/env python3
import os
import sys

from karleksbrev import encode, decode



def main():
    _NUM_TESTCASES = 50
    _USER_FAIL = 120
    _SECRET_KEY = "SUCCESSiujwefguiwehuioew"
    _SECRET_FAIL = "FAILiujwefguiwehuioew"

    global rng_state
    rng_state = -1
    def next_rand():
        global rng_state
        rng_state ^= (rng_state << 21) & 0xFFFFFFFFFFFFFFFF  # Apply modulo 2^64 with bitmask
        rng_state ^= (rng_state >> 35) & 0xFFFFFFFFFFFFFFFF
        rng_state ^= (rng_state << 4) & 0xFFFFFFFFFFFFFFFF
        rng_state = (rng_state * 2685821657736338717) % (1 << 64)
        return rng_state

    def rand_interval(l, r):
        range_size = r - l + 1
        return l + (next_rand() % range_size)


    def permute_vector(vec) -> None:
        for i in range(len(vec) - 1, 0, -1):
            j = rand_interval(0, i)
            vec[i], vec[j] = vec[j], vec[i]

    
    n, k = [int(i) for i in input().split()]
    test_type, seed = [int(i) for i in input().split()]
    rng_state = seed

    def get_lr(elen):
        if test_type == 0:
            l = rand_interval(0, elen-1)
            r = rand_interval(l, elen-1)
            return l,r
        if test_type == 1:
            l = rand_interval(0, elen-1)
            return l,l
        if test_type == 2:
            while True:
                l = rand_interval(0, elen-3)
                if l % 2 == 0:
                    break
            while True:
                r = rand_interval(l, elen-1)
                if r % 2 == 0:
                    break
            return l,r
        if test_type == 3:
            while True:
                l = rand_interval(0, elen-1)
                if l % 2 == 0:
                    break
            r = rand_interval(l, elen-1)
            return l,r



    r, w = os.pipe()
    pid = os.fork()

    if pid == 0:
        os.close(r)
        w = os.fdopen(w, 'w')
        testcases = []
        
        for t in range(_NUM_TESTCASES):
            s = ""
            for i in range(n):
                s += "1" if rand_interval(0, 1) else "0"

            encoded = encode(s)

            if len(encoded) == 0:
                print(f"{_SECRET_FAIL}Encoder gave an empty E")
                sys.exit(_USER_FAIL)

            if len(encoded) > k:
                print(f"{_SECRET_FAIL}Encoder gave too long E")
                sys.exit(_USER_FAIL)

            for c in encoded:
                if not c in ['0', '1']:
                    print(f"{_SECRET_FAIL}Encoder gave E containing character which is not 0 or 1")
                    sys.exit(_USER_FAIL)
            
            l, r = get_lr(len(encoded))
            encoded = [c for c in encoded]
            for i in range(l,r+1):
                if encoded[i]=='0':
                    encoded[i]='1'
                else:
                    encoded[i]='0'
            encoded = "".join(encoded)

            testcases.append((s, encoded))

        for t in testcases:
            w.write(t[0]+"$")
            w.write(t[1]+"@")


        w.close()
    else:
        os.close(w)
        r = os.fdopen(r)
        pid, status = os.waitpid(pid, 0)
        if os.WIFSIGNALED(status): os.kill(pid, os.WTERMSIG(status))
        ex = os.WEXITSTATUS(status)
        if ex == _USER_FAIL: sys.exit(0)
        if ex != 0: sys.exit(ex)
        buf = r.read()
        buf = [tc.split("$") for tc in buf.split("@")[:-1]]
        permute_vector(buf)

        h = 0
        MOD = 1 << 64

        for tc in buf:
            S, E = tc
            for c in S:
                h = (h+ord(c)-ord('0'))*31 % MOD
            for c in E:
                h = (h+ord(c)-ord('0'))*31 % MOD

            decoded = decode(E)
            if decoded != S:
                print(f"{_SECRET_FAIL}Decoder did not find S")
                sys.exit(0)
        sys.stderr.write(f"Hash of run: {h}\n")
        print(_SECRET_KEY + str(seed))

if __name__ == "__main__":
    main()
