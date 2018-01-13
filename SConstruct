import glob
import re
import os

def search_for_files(pattern):
	test_pattern = re.compile(pattern)
	test_files = []
	
	for root, dirs, files in os.walk("./"):
		temp = filter(test_pattern.match, files)
		if root != "./":
			temp = [root + '//' + x for x in temp]
			for idx, x in enumerate(temp):
				temp[idx] = x[2:]
		test_files += temp
	return test_files

def add_build_path(files, build_path):
	for i in xrange(0, len(files)):
		files[i] = build_path + files[i]
	
QT5DIR = ''
CXXFLAGS = []
LINKFLAGS = []
LIBS = []
CPPPATH = ['./']

build_path = './../build/'
src_path = './'

env = Environment()
if env['CXX'] == 'g++':
	CXXFLAGS.extend(['-fPIC','-std=c++14','-pthread'])
	LINKFLAGS.extend(['-lpthread'])
	LIBS.extend(['boost_unit_test_framework', 'pthread'])
elif env['CXX'] == 'cl' or env['CC'] == 'cl':
	CXXFLAGS.extend(['/std:c++14', '-pthread'])
	LINKFLAGS.extend(['/LIBPATH:..\\boost_1_65_1\\lib64-msvc-14.0', '-lpthread'])
	CPPPATH.extend(['..\\boost_1_65_1'])

env.Append(CXXFLAGS=CXXFLAGS)
env.Append(LINKFLAGS=LINKFLAGS)
env.Append(LIBS=LIBS)
env.Append(CPPPATH=CPPPATH)

#Prepare QT5 tool
env.Tool('qt5') #Tool for qt5 building <- Both
env.EnableQt5Modules([
                      'QtGui',
                      'QtCore',
                      'QtNetwork',
						'QtWidgets',
						'QtCharts'
                    ]) #QT5 modules used

#Prepare Box2D
box2D_sources = glob.glob('Box2D/*.cpp')+glob.glob('Box2D/*/*.cpp')+glob.glob('Box2D/*/*/*.cpp')
add_build_path(box2D_sources, build_path)

env.VariantDir(build_path, src_path, duplicate=0)

#Sources containing tests
source_tests = search_for_files("test_.*\.(cc|cpp)")
add_build_path(source_tests, build_path)

#All sources
source = search_for_files(".*\.(cc|cpp)")
add_build_path(source, build_path)

#Main.cpp file
source_main = search_for_files("main.cc")
add_build_path(source_main, build_path)

source_without_tests = filter(lambda x: x not in source_tests, source)
env.Program(target = build_path+'GeneticCars', source = source_without_tests)

source_without_main = filter(lambda x: x not in source_main, source)
env.Program(target = build_path+'tests_GeneticCars', source = source_without_main)
