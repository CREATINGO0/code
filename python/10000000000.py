from sys import argv

script, x = argv

a = int(x)

if a > 100:
    if a >1000:
        print("greater than 1k")
        if a >100000:
            print("so big")
    print("greater than 100")
elif a <100 and a >50:
    print("between 50 and 100")
else:
    print("less than 50")
