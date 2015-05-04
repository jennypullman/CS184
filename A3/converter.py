def converter(fileIn, fileOut):
	fIn = open(fileIn, 'r')
	print fIn
	fOut = open(fileOut, 'w')
	print fOut
	count = 0
	fOut.write(fIn.readline()) # add patch count
	fIn.readline() # skip first 3 3
	lineCount = 0
	currLine = ''
	for line in fIn:
		if (lineCount == 4):
			lineCount = 0
			fOut.write('\n')
			continue
		count = count +1
		currLine = currLine + '\t' + line.strip()
		if (count == 4):
			fOut.write(currLine + '\n')
			currLine = ''
			lineCount = lineCount+1
			count = 0
	fIn.close()
	fOut.close()

def converter2(fileIn, fileOut):
	fIn = open(fileIn, 'r')
	fOut = open(fileOut, 'w')
	count = 0
	lineCount = 0
	currLine = ''
	for line in fIn:
		if (lineCount == 4):
			lineCount = 0
			fOut.write('\n')
		count = count +1
		currLine = currLine + line.strip() + '\t'
		if (count == 4):
			fOut.write(currLine + '\n')
			currLine = ''
			lineCount = lineCount+1
			count = 0
	fIn.close()
	fOut.close()

def flip(fileIn, fileOut):
	fIn = open(fileIn, 'r')
	fOut = open(fileOut, 'w')
	fOut.write(fIn.readline())
	for line in fIn:
		print line
		line.strip();
		points = line.split('\t')
		if (len(points) < 3):
			fOut.write('\n')
			continue
		for point in points:
			coords = point.split(' ')
			fOut.write(coords[0] + ' ')
			if (coords[2][0] == '-'):
				fOut.write(coords[2][1:] + ' ')
			else:
				fOut.write('-'+coords[2] + ' ')
			fOut.write(coords[1] + '\t')
		fOut.write('\n')
	fIn.close()
	fOut.close()