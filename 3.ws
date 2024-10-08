push 0 push 24 store  # initialize testcase counter
label L1  # testcase loop (stack is empty here)
    push 0 load dup  # retrieve 2 copies of testcase counter
    jzero END
    push 1 sub push 0 swap store  # decrement testcase counter on heap
    # read A
    push 1 readc push 2 readc push 3 readc push 4 readc push 5 readc
    push 6 readc push 7 readc push 8 readc push 9 readc push 10 readc
    push 18 readc  # discard space
    # read B
    push 11 readc push 12 readc push 13 readc push 14 readc push 15 readc
    push 18 readc  # discard terminating newline
    push 16 push 6 store  # set i to 6
    label L2  # i loop
        push 16 load  # load i
        push 1 sub dup push 16 swap store  # decrement i on the heap
        jneg FAIL
        # stack is empty
        push 17 push 5 store  # set j to 5
        label L3  # j loop
            push 17 load  # load j
            push 1 sub dup  # replace top with 2 copies of j-1
            push 17 swap store  # write decremented j to the heap
            jneg FOUND
            # stack is empty here; compare A[i+j] with B[j]
            push 16 load push 17 load add push 1 add load  # load A[i+j]
            push 17 load push 11 add load  # load B[j]
            sub
            jzero L3  # chars are same; continue loop
            jump L2  # chars differ; try next i
        label FOUND
        push 1 writen push 10 writec
        jump L1
    label FAIL  # end of this iteration of of testcase loop; no match
    push 0 writen push 10 writec
    jump L1
label END
exit