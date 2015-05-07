#!/usr/bin/python

# python script -c core -n nameClass -f nameFile

import sys, getopt


def main(argv):

	component = 'core'
	className = 'Class'
	fileName = 'class'
	only_interface = False	

	try:
		opts, args = getopt.getopt(argv,"hic:n:f:",["component=","name=","file=", "only_interface"])
	except getopt.GetoptError:
		help()
		sys.exit(2)

	for opt, arg in opts:
		if opt == '-h':
			help()
			sys.exit()
		elif opt in ("-c", "--component"):
			component = arg
		elif opt in ("-n", "--name"):
			className = arg
		elif opt in ("-f", "--file"):
			fileName = arg
		elif opt in ("-i", "--only_interface"):
			only_interface = True


	alias = {}	
	alias['component'] = component
	alias['className'] = className	
	alias['fileName'] = fileName
	alias['componentUpper'] = component.upper()
	alias['fileNameUpper'] = fileName.upper()


	with open('data/ssf_template_header.hpp', 'r') as fTemplateHeader :
		strTemplateHeader = fTemplateHeader.read()

	with open('data/ssf_template_source.cpp', 'r') as fTemplateSource :
		strTemplateSource = fTemplateSource.read()

	headerPath = "../components/%s/include/%s/%s.hpp" % (component, component, fileName)
	sourcePath = "../components/%s/src/%s.cpp" % (component, fileName)

	with open(headerPath, 'w') as fHeader:
		fHeader.write(strTemplateHeader.format(**alias))

	if(not only_interface):
		with open(sourcePath, 'w') as fSource:
			fSource.write(strTemplateSource.format(**alias))

	print ('Class files generate with success!')

def help():
	print('This scripts generates a empty c++ file class (.h and .cpp) according with SSF coding style guide.')
	print('Options:')
	print('-h: shows this help.')
	print('-c --component: specifies which component the new class will be part.')
	print('-n --name: the name class.')
	print('-f --file: the file name of the new class. (i.e. if file=test the files class will be named test.cpp and test.h)')


if __name__ == "__main__":
	main(sys.argv[1:])