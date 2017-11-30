import glob

env = Environment()
env['QT5DIR'] = 'H:\\Programy\\QT\\5.9.1\\msvc2015_64'
#env.Append(QT5DIR=['H:\\Programy\\QT\\5.9.1\\msvc2015_64'])
env.Tool('qt5')
env.Append(CCFLAGS=['-fPIC','-std=c++11'])
env.Append(LIBS=['boost_unit_test_framework'])
env.Append(CPPPATH=['./../libs/'])
env.EnableQt5Modules([
                      'QtGui',
                      'QtCore',
                      'QtNetwork',
		      'QtWidgets'
                     ])
build_path = './../build/'
src_path = './'
env.VariantDir(build_path, src_path, duplicate=0)
source = [build_path+'main.cpp'] + glob.glob('Box2D/*.cpp')+glob.glob('Box2D/*/*.cpp')+glob.glob('Box2D/*/*/*.cpp')
env.Program(target = build_path+'GeneticCars', source = source)
