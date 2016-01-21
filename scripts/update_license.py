#!/usr/bin/python
"""
Update SSIGLib lincence
"""

import re
import os

if __name__ == "__main__":

    with open('data/ssiglib_template_license.txt', 'r') as f_template_license:
        TEMPLATE = f_template_license.read()

    ROOT_DIR = '../modules'
    for subdir, _, files in os.walk(ROOT_DIR, topdown=False):
        for filename in files:
            if filename.endswith('.h') or \
					filename.endswith('.hpp') or \
			   		filename.endswith('.cpp') or \
			   		filename.endswith('.cu') or filename.endswith('.cuh'):
                fullpath = os.path.join(subdir, filename)
                print fullpath
                content = ''
                with open(fullpath, 'r') as file_reader:
                    content = file_reader.read()
                with open(fullpath, 'w') as file_writer:
                    match_pattern = re.search(
                        r'/\*L(.+?)L\*/', content, re.DOTALL)
                    if match_pattern:
                        content = content.replace(
                            match_pattern.group(0), TEMPLATE)
                        file_writer.write(content)
                    else:
                        content = TEMPLATE.rstrip(
                            '\r\n') + '\n\n' + content
                        file_writer.write(content)
