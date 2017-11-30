env = Environment()
env['QT5DIR'] = 'H:\\Programy\\QT\\5.9.1\\msvc2015_64'
env.Tool('qt5')
env.EnableQt5Modules([
                      'QtGui',
                      'QtCore',
                      'QtNetwork',
					  'QtWidgets'
                     ])
build_path = './../build/'
src_path = './'
env.VariantDir(build_path, src_path, duplicate=0)
env.Program(target = build_path+'GeneticCars', source = [build_path+'main.cpp'])