# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.18.20081302-MSVC_2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(dungeonator-populate NONE)

include(ExternalProject)
ExternalProject_Add(dungeonator-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/BenjaminHinchliff/dungeonator.git" "GIT_TAG" "1.0.0"
                    SOURCE_DIR          "C:/Users/benja/source/repos/dungeonator-demo/out/build/x64-Debug (default)/_deps/dungeonator-src"
                    BINARY_DIR          "C:/Users/benja/source/repos/dungeonator-demo/out/build/x64-Debug (default)/_deps/dungeonator-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


