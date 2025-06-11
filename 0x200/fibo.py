# Fibonacci sequence generator using a list
seq = []
fib = [0, 1]

count = 10
for i in range(count):
    fib.append(fib[0] + fib[1])  # 0 + 1 = 1
    seq.append(fib.pop(0))  # [0]

print(seq)
print(fib)
