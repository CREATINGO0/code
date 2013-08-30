from sys import argv

script, i, j, l = argv

a = int(i)
b = int(j)
c = int(l)

def compare(a, b, c):
	if a > b:
		if a > c:
			print("a largest")
		if a < c:
			print("c largest")
	if a < b:
		if b > c:
			print("b largest")
		else:
			print("c largest")
