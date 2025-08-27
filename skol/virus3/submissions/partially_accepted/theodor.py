#!/usr/bin/python3
def interpret(code):
    array = [0]*100
    ans = ""
    pointerLocation = 0
    i = 0
    c = 0
    current = ""
    while i < len(code):
        if code[i] == '<':
            if pointerLocation > 0:
                pointerLocation -= 1
        elif code[i] == '>':
            pointerLocation += 1
            if len(array) <= pointerLocation:
                array.append(0)
        elif code[i] == '+':
            if array[pointerLocation] == 255:
                array[pointerLocation] = 0
            else:
                array[pointerLocation] += 1
        elif code[i] == '-':
            if array[pointerLocation] == 0:
                array[pointerLocation] = 255
            else:
                array[pointerLocation] -= 1
        elif code[i] == '.':
            # print(str(array[pointerLocation]))
            print(chr(array[pointerLocation]), end="")
        elif code[i] == ',':
            if c == len(current):
                current = input()+' '
                c = 0
            try:
                y = ord(current[c])
                c+=1
            except ValueError:
                y = int(current)
                c = len(current)
            array[pointerLocation] = y
        elif code[i] == '[':
            if array[pointerLocation] == 0:
                open_braces = 1
                while open_braces > 0:
                    i += 1
                    if code[i] == '[':
                        open_braces += 1
                    elif code[i] == ']':
                        open_braces -= 1
        elif code[i] == ']':
            open_braces = 1
            while open_braces > 0:
                i -= 1
                if code[i] == '[':
                    open_braces -= 1
                elif code[i] == ']':
                    open_braces += 1
            i -= 1
        i += 1
    
    print(ans)


interpret(
    """
>>+[>++++[<++++++++>-],>++++[<-------->-]<]

>>+[>++++[<++++++++>-],>++++[<-------->-]<]
<[<]
>[-]<
<<[<]
>[-]

>[>]>>>[>]
<[>>>+<<<
[<]<<[-]<[->+>+<<]
>>>>[>]<[->+<]>
[-<<[<]<->>[>]>]
<<[<]<<[-<+>]+>

[[-]<->]
<[-<[-]<[[->+<]<]>>[>]]

+<[>-]
>[<<<++++++++++[-<+++++++++++>]<----.---------.<<<<<<]
>>[>]<

]

>>>>[[-]++++++++++[-<+++++++++++>]<.---------.+++++.[-]]
""")