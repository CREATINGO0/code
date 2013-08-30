class Human(object):
	laugh = 'haha'
	def show_laugh(self):
		print self.laugh
	def laugh_10th(self):
		for i in range(10):
			self.show_laugh()
	def __init__(self,input_gender):
		self.gender = input_gender
	def printGender(self):
		print self.gender

Lei = Human('male')
#print Lei.gender
Lei.printGender()