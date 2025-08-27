#!/usr/bin/python3
def encode(S: str) -> str:
    E = S + "1" + S + "1" + S
    return "".join(E)

def decode(E: str) -> str:
    n = len(E)//3
    if E[n] == E[2*n+1] == "1":
        out = [E[:n],E[n+1:2*n+1],E[2*n+2:]]
        out.sort()
        return out[1]
    elif E[n] == E[2*n+1] == "0":
        return E[n+1:2*n+1].replace("1","2").replace("0","1").replace("2","0") #swap all 1s with 0s
    elif E[n] == "0":
        return E[2*n+2:]
    elif E[2*n+1] == "0":
        return E[:n]
    
    assert 0, "please please please don't get here"
