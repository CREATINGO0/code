animals = ['tiger', 'python', 'peacock', 'kangaroo', 'whale', 'platypus']

def shunxu(m):
	if m == 1:
		return("1st")
	elif m == 2:
		return("2nd")
	else:
		return(m + "th")

for i in range(0,6):
	print("the animal at", shunxu(i+1), "is", animals[i])
