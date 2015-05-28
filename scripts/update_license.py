#!/usr/bin/python

import sys, getopt
import re
import os

def main(argv):
		
	with open('data/ssf_template_license.txt', 'r') as fTemplateLicense :
		strTemplateLicense = fTemplateLicense.read()
	
	rootdir ='../components'
	for subdir, dirs, files in os.walk(rootdir, topdown=False):
		for filename in files:
			if (filename.endswith('.h') or filename.endswith('.hpp') or filename.endswith('.cpp')):
				fullpath = os.path.join(subdir, filename)
				print(fullpath)
				content = ''
				with open(fullpath, 'r') as fr:
					content = fr.read()
				with open(fullpath, 'w') as fw:					
					matchPattern = re.search('/\*L(.+?)L\*/', content, re.DOTALL)
					if matchPattern:
						content = content.replace(matchPattern.group(0), strTemplateLicense)
						fw.write(content)
					else:
						content = strTemplateLicense.rstrip('\r\n') + '\n\n' + content
						fw.write(content)
	
if __name__ == "__main__":
	main(sys.argv[1:])