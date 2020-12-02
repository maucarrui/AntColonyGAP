project('Ant Colony GAP', 'cpp')

add_global_arguments('-DSOME_TOKEN=value', language: 'cpp')

dependencies= [dependency('sqlite3'),
	       dependency('gtest')]

src = ['src/Task.cpp',
       'src/Worker.cpp',
       'src/DAO.cpp',
       'src/Graph.cpp',
       'src/main.cpp']

incdir = include_directories('src')

executable('gap', 
           src, 
	   dependencies : dependencies,
	   include_directories : incdir)

worker_test = executable('Worker test', 
	                 ['test/src/Worker_Test.cpp',
			  'src/Worker.cpp'],
			 dependencies : dependencies)
test('Worker tests', worker_test)

task_test = executable('Task test', 
	               ['test/src/Task_Test.cpp',
			'src/Task.cpp'],
		       dependencies : dependencies)
test('Task tests', task_test)

dao_test = executable('DAO test',
	              ['test/src/DAO_Test.cpp',
		       'src/DAO.cpp',
		       'src/Worker.cpp',
		       'src/Task.cpp'],
		      dependencies : dependencies)

test('DAO tests', dao_test)