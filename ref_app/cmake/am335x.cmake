﻿##############################################################################
#  Copyright Christopher Kormanyos 2021 - 2022.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)

#
# MIT License
#
# Copyright (c) 2019 Joel Winarske
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

set(APP ref_app)

set(CMAKE_EXECUTABLE_SUFFIX .elf)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

set(TARGET_INCLUDES
    ${PATH_APP}/util/STL
)

set(_TARGET_CFLAGS
    -finline-functions
    -finline-limit=32
    -march=armv7-a
    -mtune=cortex-a8
    -marm
    -mfloat-abi=hard
    -mfpu=neon
    -ffast-math
)

set(TARGET_AFLAGS "")

set(_TARGET_LDFLAGS
    -nostdlib
    -nostartfiles
    -T ${LINKER_DEFINITION_FILE}
)

string(REPLACE ";" " " TARGET_CFLAGS "${_TARGET_CFLAGS}")
string(REPLACE ";" " " TARGET_LDFLAGS "${_TARGET_LDFLAGS}")


set(FILES_TARGET
    ${PATH_APP}/mcal/mcal_gcc_cxx_completion
    ${PATH_APP}/mcal/${TARGET}/mcal_cpu_detail
    ${PATH_APP}/mcal/${TARGET}/mcal_cpu_detail_secure
    ${PATH_APP}/util/STL/impl/cmath_impl_gamma
    ${PATH_APP}/util/STL/impl/cmath_impl_hyperbolic
    ${PATH_TGT}/startup/crt0
    ${PATH_TGT}/startup/crt0_init_ram
    ${PATH_TGT}/startup/crt1
    ${PATH_TGT}/startup/int_vect
)
