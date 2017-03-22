project('petanqulator', 'cpp')

add_global_arguments('-std=c++14', language : 'cpp')
add_global_arguments('-O2', language : 'cpp')

inc_dir = include_directories('src/')

bullet_dep = dependency('bullet')
eigen_dep = dependency('eigen3')

pet_src = [ 'src/petanqulator/Chrono.cpp',
                     'src/petanqulator/Game.cpp',
                     'src/petanqulator/GameObject.cpp',
                     'src/petanqulator/Physics.cpp',
                     'src/petanqulator/Player.cpp',
                     'src/petanqulator/Prng.cpp',
                     'src/petanqulator/Utils.cpp' ]

petanqulator_lib = static_library('petanqulator', 
        pet_src, 
        include_directories : inc_dir,
        dependencies : [bullet_dep, eigen_dep])

executable('petanqulator_cli', 
        'src/petanqulator_cli/petanqulator_cli.cpp',
        include_directories : inc_dir,
        dependencies : [bullet_dep, eigen_dep],
        link_with : petanqulator_lib)

executable('petanqulator_test', 
        'src/petanqulator_test/petanqulator_test.cpp',
        include_directories : inc_dir,
        dependencies : [bullet_dep, eigen_dep],
        link_with : petanqulator_lib)

gtkmm_dep = dependency('gtkmm-2.4')
gtkglextmm_dep = dependency('gtkglextmm-1.2')
glu_dep = dependency('glu')

pet_gui_src = [ 'src/petanqulator_gui/Controller.cpp',
            'src/petanqulator_gui/petanqulator_gui.cpp',
            'src/petanqulator_gui/View.cpp',
            'src/petanqulator_gui/ViewGL.cpp',
            'src/petanqulator_gui/ViewPanel.cpp' ]

executable('petanqulator_gui', 
        pet_gui_src,
        include_directories : inc_dir,
        dependencies : [gtkmm_dep, bullet_dep, eigen_dep, gtkglextmm_dep, glu_dep],
        link_with : petanqulator_lib)

