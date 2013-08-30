from sys import argv

script, year = argv

yrnb = int(year)

if yrnb%4 == 0:
	if yrnb%100 == 0:
		print 'not leap year'
	else:
		print 'leap year'
else:
	print 'not leap year'
