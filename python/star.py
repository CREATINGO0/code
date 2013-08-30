from sys import argv

script, m = argv

k = int(m)

for i in range(1,k):
	print(" "*(k -1 - i), "*"*(2 * i -1))
for i in range(1,k-1):
	print(" "*i, "*"*(2 * (k - i -1) - 1))
