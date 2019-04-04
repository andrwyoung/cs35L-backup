import argparse, random, sys

class shuf:
	#creates the file depending if -i is on/off
	def __init__(self, filename, eye):
		if not eye:
			f = open(filename, 'r')
			self.lines = f.readlines()
			for c in self.lines:
				print c
			f.close()
			#print self.lines
		else:
			#inputrange option implementation
			for index, c in enumerate(filename):
				if c == '-':
					low = filename[:index]
					high = filename[index + 1:]
			try:
				self.lines = range(int(low), int(high) + 1)
			except:
				parser.error("Invalid range of number")

		random.shuffle(self.lines)

	def length(self):
		return len(self.lines)

	#outputs specific line with random/norandom option
	def outline(self, line, rand):
		if rand:
			return random.choice(self.lines)
		else:
			return self.lines[line]

def main():

	parser = argparse.ArgumentParser()
	parser.add_argument("file")
	parser.add_argument("-n", "--head-count", type=int, action="store", default=sys.maxsize,
		help="Output this many lines")
	parser.add_argument("-r", "--repeat", action="store_true", 
		help="Repeat output values. Infinite if no -n")
	parser.add_argument("-i", "--input-range", action="store_true", 
		help="Treat filename as range of numbers (format: #-#)")
	args = parser.parse_args()

	#creating the shuffler
	try:
		generator = shuf(args.file, args.input_range)
	except:
		parser.error("Invalid filename")

	numlines = generator.length()

	#headcount option implementation
	offset = args.head_count
	if offset < 0:
		parser.error("Invalid number of lines")
	if offset < numlines or args.repeat:
		numlines = offset

	#regular mode + repeat option implemenation
	while numlines > 0:
		if args.input_range:
			sys.stdout.write(str(generator.outline(numlines - 1, args.repeat)) + "\n")
		else:
			sys.stdout.write(generator.outline(numlines - 1, args.repeat))
		numlines -= (not args.repeat or offset >= 0)

if __name__ == "__main__":
	main()