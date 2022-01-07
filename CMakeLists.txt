########################################################################################################################
### SYNTHATOR AUDIO PLUGIN AND APP
########################################################################################################################

cmake_minimum_required(VERSION 3.15)

########################################################################################################################
### PROJECT DESCRIPTION AND META INFO
########################################################################################################################

set(SYNTHATOR_PROJECT_NAME        "Synthator")
set(SYNTHATOR_PROJECT_DESCRIPTION "A scriptable Synthesizer made from JUCE and ChaiScript")
set(SYNTHATOR_AUTHOR_DOMAIN       "https://github.com/mostsignificant/synthator")
set(SYNTHATOR_AUTHOR_MAINTAINER   "mostsig@gmail.com")
set(SYNTHATOR_VERSION_MAJOR       "0")
set(SYNTHATOR_VERSION_MINOR       "0")
set(SYNTHATOR_VERSION_PATCH       "1")
set(SYNTHATOR_VERSION             "${SYNTHATOR_VERSION_MAJOR}.${SYNTHATOR_VERSION_MINOR}.${SYNTHATOR_VERSION_PATCH}")
set(SYNTHATOR_NAME_VERSION        "${SYNTHATOR_PROJECT_NAME} v${SYNTHATOR_VERSION} (${SYNTHATOR_VERSION_REVISION})")

configure_file(Version.hpp.in ${CMAKE_BINARY_DIR}/Version.hpp)

########################################################################################################################
### PROJECT DECLARATION AND DEPENDENCIES
########################################################################################################################

project(${SYNTHATOR_PROJECT_NAME} VERSION ${SYNTHATOR_VERSION})

add_subdirectory(External/ChaiScript)
add_subdirectory(External/JUCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/Source)

