# Testing library
set (${self} test_${PROJECT_NAME})
# ph_fetch (catch2)
find_package(Catch2 REQUIRED)

file(GLOB_RECURSE HEADER_LIST "include/*.hpp")
file(GLOB SOURCE_LIST *.cpp)

# set (deps )
macro (ph_add_test name)
	add_executable (test_${name} testlib.cpp test_${name}.cpp ${HEADER_LIST})
	target_link_libraries (test_${name} PRIVATE ${PROJECT_NAME} Catch2::Catch2 ph::color)
	target_include_directories (test_${name} PRIVATE include ph::color)
	ph_precompile (TARGET test_${name} PRIVATE PCH ${std_pch})

	if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
		set_target_properties(test_${name}          PROPERTIES FOLDER "${PROJECT_NAME}")
	endif()		
endmacro ()


# add_executable (test_${PROJECT_NAME}_sequence testlib.cpp test_sequence.cpp ${HEADER_LIST})
# add_executable (test_${PROJECT_NAME}_algorithms testlib.cpp test_algorithms.cpp ${HEADER_LIST})

ph_add_test (algorithms)
ph_add_test (sequence)
ph_add_test (allocator)
ph_add_test (vector)
ph_add_test (arena)
ph_add_test (array)
ph_add_test (pointee)

# target_link_libraries (test_${PROJECT_NAME}_algorithms PRIVATE ${PROJECT_NAME} Catch2::Catch2 ph::color)
# target_include_directories (test_${PROJECT_NAME}_algorithms PRIVATE include ph::color)
# ph_precompile (TARGET test_${PROJECT_NAME}_algorithms PRIVATE PCH ${std_pch})

# target_link_libraries (test_${PROJECT_NAME}_sequence PRIVATE ${PROJECT_NAME} Catch2::Catch2 ph::color)
# target_include_directories (test_${PROJECT_NAME}_sequence PRIVATE include ph::color)
# ph_precompile (TARGET test_${PROJECT_NAME}_sequence PRIVATE PCH ${std_pch})

add_test (NAME testtest_${PROJECT_NAME} COMMAND ${self}) 


# if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
#     set_target_properties(test_${PROJECT_NAME}_sequence          PROPERTIES FOLDER "${PROJECT_NAME}")
#     set_target_properties(test_${PROJECT_NAME}_algorithms          PROPERTIES FOLDER "${PROJECT_NAME}")

# else()
#     set_target_properties(test_${PROJECT_NAME}_sequence           PROPERTIES FOLDER "dependencies/${PROJECT_NAME}")
#     set_target_properties(test_${PROJECT_NAME}_algorithms          PROPERTIES FOLDER "${PROJECT_NAME}")

# endif()



