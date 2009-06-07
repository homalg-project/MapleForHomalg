#############################################################################
##
##  MapleForHomalg.gd           MapleForHomalg package        Thomas Bächler
##
##  Copyright 2009, Thomas Bächler, RWTH Aachen
##
##  Declaration stuff for MapleForHomalg.
##
#############################################################################

# our info class:
DeclareInfoClass( "InfoMapleForHomalg" );
SetInfoLevel( InfoMapleForHomalg, 1 );

# a central place for configurations:
DeclareGlobalVariable( "MapleForHomalg" );

####################################
#
# global functions and operations:
#
####################################

DeclareGlobalFunction( "LaunchCASMapleForHomalg" );

DeclareGlobalFunction( "SendBlockingToCASMapleForHomalg" );

DeclareGlobalFunction( "TerminateCASMapleForHomalg" );

# basic operations:

