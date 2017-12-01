import glob

env = Environment()
env['QT5DIR'] = 'H:\\Programy\\QT\\5.9.1\\msvc2015_64' #QT5 directory for Windows
env.Tool('qt5') #Tool for qt5 building
#env.Append(CCFLAGS=['-fPIC','-std=c++11']) #Flags for G++
env.Append(CXXFLAGS=['-fPIC', '-std=c++14', '/std:c++14']) #Flags for G++ and MVCS
env.Append(LINKFLAGS=['/LIBPATH:H:\\Kodzenie\\boost_1_65_1\\lib64-msvc-14.0']) #Boost libraries path for MVCS
#env.Append(LIBS=['boost_unit_test_framework']) #Flag for G++
env.Append(CPPPATH=['./', 'H:\\Kodzenie\\boost_1_65_1\\']) #Boost headers path
env.EnableQt5Modules([
                      'QtGui',
                      'QtCore',
                      'QtNetwork',
		      'QtWidgets'
                     ]) #QT5 modules used
build_path = './../build/'
src_path = './'
env.VariantDir(build_path, src_path, duplicate=0)
source = [build_path+'main.cpp'] + glob.glob('Box2D/*.cpp')+glob.glob('Box2D/*/*.cpp')+glob.glob('Box2D/*/*/*.cpp')
env.Program(target = build_path+'GeneticCars', source = source)
