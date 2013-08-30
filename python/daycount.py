from sys import argv

script, year, month, day = argv

yno = int(year)
mno = int(month)
dno = int(day)

def leap(yno):
	if yno%4 == 0:
		if yno%100 == 0:
			return 0
		else:
			return 1
	else:
		return 0

ydays = [0,31,28,31,30,31,30,31,31,30,31,30]

if leap(yno) == 1:
	ydays[2] = 29

def daycount(ydays,mno,dno):

	def monrun(ydays,mno):
		k = 0
		for i in range(mno):
			k = k + ydays[i]
		return k

	return monrun(ydays,mno) + dno

print  daycount(ydays,mno,dno)