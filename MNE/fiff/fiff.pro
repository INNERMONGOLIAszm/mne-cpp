#--------------------------------------------------------------------------------------------------------------
#
# @file     fiff.pro
# @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
#           Matti Hämäläinen <msh@nmr.mgh.harvard.edu>
# @version  1.0
# @date     July, 2012
#
# @section  LICENSE
#
# Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification, are permitted provided that
# the following conditions are met:
#     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
#       following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
#       the following disclaimer in the documentation and/or other materials provided with the distribution.
#     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
#       to endorse or promote products derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
# PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
# INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
#
# @brief    This project file builds the fiff library.
#
#--------------------------------------------------------------------------------------------------------------

include(../../mne-cpp.pri)

TEMPLATE = lib

QT       -= gui

DEFINES += FIFF_LIBRARY

TARGET = fiff

CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}

#ToDo Fix this: remove mne-cpp from path
win32:QMAKE_POST_LINK += $${QMAKE_COPY} "..\\..\\..\\mne-cpp\\lib\\$${TARGET}.dll" "..\\..\\..\\mne-cpp\\bin\\"
DESTDIR = $${PWD}/../../lib

SOURCES += fiff.cpp \
#    fiff_parser.cpp \
    fiff_tag.cpp \
    fiff_dir_tree.cpp \
    fiff_coord_trans.cpp \
    fiff_ch_info.cpp \
    fiff_proj.cpp \
    fiff_named_matrix.cpp \
    fiff_file.cpp \
    fiff_raw_data.cpp \
    fiff_ctf_comp.cpp \
    fiff_id.cpp \
    fiff_info.cpp \
    fiff_raw_dir.cpp \
    fiff_dig_point.cpp \
    fiff_ch_pos.cpp \
    fiff_evoked_data_set.cpp \
    fiff_evoked_data.cpp \
    fiff_cov.cpp

HEADERS += fiff.h \
    fiff_global.h \
    fiff_types.h \
    fiff_id.h \
    fiff_constants.h \
    fiff_tag.h \
    fiff_dir_tree.h \
    fiff_coord_trans.h \
    fiff_ch_info.h \
    fiff_proj.h \
    fiff_named_matrix.h \
    fiff_ctf_comp.h \
    fiff_info.h \
    fiff_raw_data.h \
    fiff_dir_entry.h \
    fiff_raw_dir.h \
    fiff_file.h \
    fiff_dig_point.h \
    fiff_ch_pos.h \
    fiff_evoked_data.h \
    fiff_evoked_data.h \
    fiff_evoked_data_set.h \
    fiff_evoked_data.h \
    fiff_cov.h

#Install headers to include directory
header_files.files = ./*.h
header_files.path = ../../include/fiff

INSTALLS += header_files
