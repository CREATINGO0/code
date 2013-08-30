class Human(object):
	laugh = 'haha'
	def show_laugh(self):
		print self.laugh
	def laugh_10th(self):
		for i in range(10):
			self.show_laugh()