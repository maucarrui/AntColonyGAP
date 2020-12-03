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

task_test = executable('Task test', 
	               ['test/src/Task_Test.cpp',
			'src/Task.cpp'],
		       dependencies : dependencies)

dao_test = executable('DAO test',
	              ['test/src/DAO_Test.cpp',
		       'src/DAO.cpp',
		       'src/Worker.cpp',
		       'src/Task.cpp'],
		      dependencies : dependencies)

graph_test = executable('Graph test',
	                ['test/src/Graph_Test.cpp',
			 'src/Graph.cpp',
			 'src/Worker.cpp',
			 'src/Task.cpp',
			 'src/DAO.cpp'],
			dependencies : dependencies)

test('Worker tests', worker_test)

test('Task tests', task_test)

test('DAO tests', dao_test)

test('Graph tests', graph_test)