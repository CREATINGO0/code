from sys import argv

script, filename = argv

target = open(filename, 'w')
target.truncate()
target.write("fuck")
target.write("\n")
target.close()
