for i in range (-10,10):
	for j in range (-10,10):
		if i ** 2 + j ** 2 < 81:
			print "o",
		else:
			print " ",
	print "\n"
