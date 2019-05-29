def fib(n):
    if n<=2:
        return n
    return fib(n-1) + fib(n-2)

def fibi(n):
    a, b = 0,1
    for i in range(n):
        a, b = b, a+b
    return a

def printfib(func, inputs):
    for i in inputs:
        print("fib(%d)==%d"%(i,func(i)))

printfib(fib, range(0, 101))
