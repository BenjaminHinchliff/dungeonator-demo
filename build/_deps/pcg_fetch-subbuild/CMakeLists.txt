# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.19.1)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(pcg_fetch-populate NONE)

include(ExternalProject)
ExternalProject_Add(pcg_fetch-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/imneme/pcg-c-basic.git"
                    SOURCE_DIR          "C:/Users/benja/source/repos/dungeonator-demo/build/_deps/pcg_fetch-src"
                    BINARY_DIR          "C:/Users/benja/source/repos/dungeonator-demo/build/_deps/pcg_fetch-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


