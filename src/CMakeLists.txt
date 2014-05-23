# Copyright (C) LAAS-CNRS
# Author : Elie MOUSSY
#
# This file is part of controlPTZ.
# controlPTZ is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

SET(SOURCES
	controlPTZ/ControlPTZ.cpp 
	controlPTZ/StreamRTSP.cpp)

ADD_LIBRARY(controlPTZ SHARED ${SOURCES})
INSTALL(TARGETS controlPTZ DESTINATION ${CMAKE_INSTALL_LIBDIR})