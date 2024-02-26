project('eksersajz', 'cpp',
        default_options: ['cpp_std=c++20'])


srcs = ['src/main.cpp',
        'src/utils.cpp',
        'src/tester_class.cpp',
        'src/fill_bounds.cpp',
        'src/weird_date.cpp',
        'src/buy_sell_stock.cpp',
        'src/longest_common_prefix.cpp',
        'src/insert_delete_getrandom.cpp',
        'src/list_node.cpp',
        'src/add_two_numbers.cpp',
        'src/container_with_most_water.cpp',
        'src/insert_search_position.cpp',
        'src/first_missing_positive.cpp',
        'src/reverse_integer.cpp',
        'src/climbing_stairs.cpp',
        'src/house_robber.cpp',
        'src/coin_change.cpp',
        'src/kth_largest_element_array.cpp'
        ]
incdirs = ['include']

executable('prog',
           sources: srcs,
           include_directories: incdirs)


gtest_proj = subproject('gtest')

gtest_dep = gtest_proj.get_variable('gtest_main_dep') 
gmock_dep = gtest_proj.get_variable('gmock_dep') 
gtest_dep = dependency('gtest', main : true, required : false) 
gmock_dep = dependency('gmock', main : true, required : false) 

gtest_lib = static_library('gtest', install : true)
gmock_lib = static_library('gmock', install: true) 

test_srcs = ['test/test_all.cpp',
             'src/utils.cpp',
             'src/longest_common_prefix.cpp',
             'src/insert_delete_getrandom.cpp',
             'src/product_of_array_except_self.cpp',
             'src/list_node.cpp',
             'src/add_two_numbers.cpp',
             'src/merge_two_sorted_lists.cpp',
             'src/container_with_most_water.cpp',
             'src/insert_search_position.cpp',
             'src/first_missing_positive.cpp',
             'src/reverse_integer.cpp',
             'src/climbing_stairs.cpp',
             'src/house_robber.cpp',
             'src/coin_change.cpp',
             'src/kth_largest_element_array.cpp'
             ]

test_exe = executable('test_all',
                      sources: test_srcs,
                      include_directories: incdirs,
                      dependencies: [gtest_dep, gmock_dep],
                      link_with: [gtest_lib, gmock_lib])

test('all_tests', test_exe)
