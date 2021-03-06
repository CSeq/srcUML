##
# CMakeLists.txt
#
# Copyright (C) 2015-2016 srcML, LLC. (www.srcML.org)
#
# This file is part of srcUML.
#
# srcUML is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# srcUML is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with srcUML.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.8)
project(srcUML)

enable_testing()

# find needed libraries
find_package(LibXml2 REQUIRED)

# include needed includes
include_directories(${LIBXML2_INCLUDE_DIR})
add_definitions("-std=c++1y")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(src/generator
                    ${CMAKE_SOURCE_DIR}/srcSAX/src/srcsax
                    ${CMAKE_SOURCE_DIR}/srcSAX/src/cpp
                    ${CMAKE_SOURCE_DIR}/srcSAX/src/windows
                    ${CMAKE_SOURCE_DIR}/srcSAXEventDispatch/src/dispatcher
                    ${CMAKE_SOURCE_DIR}/srcSAXEventDispatch/src/policy_classes
                    test/driver)

add_subdirectory(srcSAX/src)
add_subdirectory(srcSAXEventDispatch/src)
add_subdirectory(src)

add_subdirectory(test)
