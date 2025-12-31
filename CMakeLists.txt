cmake_minimum_required(VERSION 3.10)
project(IndividualBinaries)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Function to add individual executable for each source file
function(add_individual_executable source_file)
    # Get the relative path from src/
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR}/src ${source_file})
    
    # Remove the .c extension to get the executable name
    get_filename_component(exec_name ${rel_path} NAME_WE)
    get_filename_component(exec_dir ${rel_path} DIRECTORY)
    
    # Set the output directory for this specific executable
    if(exec_dir)
        set_target_properties(${exec_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${exec_dir})
    endif()
    
    # Create the executable
    add_executable(${exec_name} ${source_file})
endfunction()

# Find all .c files in src/ and its subdirectories
file(GLOB_RECURSE source_files 
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

# Add an executable for each source file
foreach(source_file ${source_files})
    add_individual_executable(${source_file})
endforeach()