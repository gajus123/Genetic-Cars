import glob

QT5DIR = ''
CXXFLAGS = []
LINKFLAGS = []
LIBS = []
CPPPATH = ['./']

build_path = './../build/'
src_path = './'

env = Environment()
if env['CXX'] == 'g++':
	CXXFLAGS.extend(['-fPIC','-std=c++14'])
	LIBS.extend(['boost_unit_test_framework'])
elif env['CXX'] == 'cl':
	CXXFLAGS.extend(['/std:c++14'])
	LINKFLAGS.extend(['/LIBPATH:H:\\Kodzenie\\boost_1_65_1\\lib64-msvc-14.0'])
	CPPPATH.extend(['H:\\Kodzenie\\boost_1_65_1'])

env.Append(CXXFLAGS=CXXFLAGS)
env.Append(LINKFLAGS=LINKFLAGS)
env.Append(LIBS=LIBS)
env.Append(CPPPATH=CPPPATH)

#Prepare QT5 tool
env['QT5DIR'] = 'H:\\Programy\\QT\\5.9.1\\msvc2015_64' #QT5 directory for Windows <- Windows only
env.Tool('qt5') #Tool for qt5 building <- Both
env.EnableQt5Modules([
                      'QtGui',
                      'QtCore',
                      'QtNetwork',
		      'QtWidgets'
                     ]) #QT5 modules used

#Prepare Box2D
box2D_sources = glob.glob('Box2D/*.cpp')+glob.glob('Box2D/*/*.cpp')+glob.glob('Box2D/*/*/*.cpp')
for i in xrange(0, len(box2D_sources)):
	box2D_sources[i] = build_path + box2D_sources[i]

env.VariantDir(build_path, src_path, duplicate=0)
source = [build_path+'main.cpp'] + box2D_sources
env.Program(target = build_path+'GeneticCars', source = source)
