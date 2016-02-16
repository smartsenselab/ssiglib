#!/usr/bin/python

"""
Generate SSIGLib Classes
Usage: python script -m core -n nameClass -f nameFile -t testFile
"""

import sys
import getopt


def print_help():
    "Help Method"

    print'This scripts generates a empty c++ file class" \
            "(.h and .cpp) according with ssiglib coding style guide.'
    print 'Options:'
    print '-h: shows this help.'
    print '-m --module: specifies which module the new class \
            will be part.'
    print '-n --name: the name class.'
    print '-t --test_name: the name of the test file.[optional]'
    print '-f --file: the file name of the new class. \
            (i.e. if file=test the files class will be named test.cpp and test.h)'


def read_values(argv):
    "Read variable values"

    values = {}
    values['module'] = 'core'
    values['class_name'] = 'Class'
    values['file_name'] = 'class'
    values['only_interface'] = False
    values['test_name'] = 't'

    try:
        opts, _ = getopt.getopt(argv, "him:n:f:t:", \
                                   ["module=", "name=", "file=", \
                                    "only_interface", "test_name="])
    except getopt.GetoptError as err:
        print str(err)
        print_help()
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-h':
            print_help()
            sys.exit()
        elif opt in ("-m", "--module"):
            values['module'] = arg
        elif opt in ("-n", "--name"):
            values['class_name'] = arg
        elif opt in ("-f", "--file"):
            values['file_name'] = arg
        elif opt in ("-t", "--test_name"):
            values["test_name"] = arg
        elif opt in ("-i", "--only_interface"):
            values['only_interface'] = True

    values['module_upper'] = values['module'].upper()
    values['file_name_upper'] = values['file_name'].upper()

    return values



def generate(argv):
    "Generate Method"

    values = read_values(argv)

    with open('data/ssiglib_template_header.thpp', 'r') as f_template_header:
        str_template_header = f_template_header.read()

    with open('data/ssiglib_template_source.tcpp', 'r') as f_template_source:
        str_template_source = f_template_source.read()

    header_path = "../modules/%s/include/%s/%s.hpp" % (
        values['module'], values['module'], values["file_name"])
    
    t_source_path = ""
    if values["test_name"] != 't':
        with open('data/ssiglib_template_test.tcpp', 'r') as f_template_test:
            str_template_test = f_template_test.read()
        
        t_source_path = "../modules/%s/test/test_%s.cpp" % (
            values['module'], values["test_name"])
    
    source_path = "../modules/%s/src/%s.cpp" % (
        values['module'], values["file_name"])

    with open('data/ssiglib_template_license.txt', 'r') as f_template_license:
        str_template_license = f_template_license.read()

    with open(header_path, 'w') as f_header:
        f_header.write(str_template_license.rstrip('\r\n') + '\n\n' + \
                      str_template_header.format(**values))
                      
    if values["test_name"] != 't':
        with open(t_source_path, 'w') as t_source:
            t_source.write(str_template_license.rstrip('\r\n') + '\n\n' + \
                          str_template_test.format(**values))
    
    if not values['only_interface']:
        with open(source_path, 'w') as f_source:
            f_source.write(str_template_license.rstrip('\r\n') + '\n\n' + \
                          str_template_source.format(**values))

    print 'Class files generate with success!'


if __name__ == "__main__":
    if len(sys.argv) == 1:
        print_help()
    else:
        generate(sys.argv[1:])
