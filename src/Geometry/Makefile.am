###################################################################################
#
# FFV-C : Frontflow / violet Cartesian
#
# Copyright (c) 2007-2011 VCAD System Research Program, RIKEN. 
# All rights reserved.
#
# Copyright (c) 2011-2015 Institute of Industrial Science, The University of Tokyo. 
# All rights reserved.
#
# Copyright (c) 2012-2015 Advanced Institute for Computational Science, RIKEN.
# All rights reserved. 
#
###################################################################################

noinst_lib_LIBRARIES = libGEOM.a

noinst_libdir = ../lib

#fj>
# add -DMPI_PL
libGEOM_a_CXXFLAGS = \
  -DMPI_PL \
  -I$(top_srcdir)/src/Geometry \
  -I$(top_srcdir)/src/FB \
  @CPM_CFLAGS@ \
  @PL_CFLAGS@ \
  @TP_CFLAGS@ \
  @MPICH_CFLAGS@ \
  @REALOPT@
#fj<

libGEOM_a_SOURCES = \
  Geometry.C \
  Geometry.h \
  CompoFraction.C \
  CompoFraction.h \
  fill_bid_naive.h \
  Glyph.C \
  Glyph.h

EXTRA_DIST = Makefile_hand depend.inc

