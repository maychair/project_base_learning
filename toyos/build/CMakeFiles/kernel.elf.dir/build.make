# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/saturn/workspace/sourcecode/project_base_learning/toyos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/saturn/workspace/sourcecode/project_base_learning/toyos/build

# Include any dependencies generated for this target.
include CMakeFiles/kernel.elf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/kernel.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/kernel.elf.dir/flags.make

CMakeFiles/kernel.elf.dir/Kernel/Arch/riscv/boot.S.o: CMakeFiles/kernel.elf.dir/flags.make
CMakeFiles/kernel.elf.dir/Kernel/Arch/riscv/boot.S.o: ../Kernel/Arch/riscv/boot.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saturn/workspace/sourcecode/project_base_learning/toyos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building ASM object CMakeFiles/kernel.elf.dir/Kernel/Arch/riscv/boot.S.o"
	/home/saturn/workspace/Applications/llvm-project/build/bin/clang $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/kernel.elf.dir/Kernel/Arch/riscv/boot.S.o -c /home/saturn/workspace/sourcecode/project_base_learning/toyos/Kernel/Arch/riscv/boot.S

# Object files for target kernel.elf
kernel_elf_OBJECTS = \
"CMakeFiles/kernel.elf.dir/Kernel/Arch/riscv/boot.S.o"

# External object files for target kernel.elf
kernel_elf_EXTERNAL_OBJECTS =

kernel.elf: CMakeFiles/kernel.elf.dir/Kernel/Arch/riscv/boot.S.o
kernel.elf: CMakeFiles/kernel.elf.dir/build.make
kernel.elf: Kernel/Arch/riscv/libriscv.a
kernel.elf: Library/libc/liblibc.a
kernel.elf: CMakeFiles/kernel.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saturn/workspace/sourcecode/project_base_learning/toyos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable kernel.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kernel.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/kernel.elf.dir/build: kernel.elf

.PHONY : CMakeFiles/kernel.elf.dir/build

CMakeFiles/kernel.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/kernel.elf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/kernel.elf.dir/clean

CMakeFiles/kernel.elf.dir/depend:
	cd /home/saturn/workspace/sourcecode/project_base_learning/toyos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saturn/workspace/sourcecode/project_base_learning/toyos /home/saturn/workspace/sourcecode/project_base_learning/toyos /home/saturn/workspace/sourcecode/project_base_learning/toyos/build /home/saturn/workspace/sourcecode/project_base_learning/toyos/build /home/saturn/workspace/sourcecode/project_base_learning/toyos/build/CMakeFiles/kernel.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/kernel.elf.dir/depend

