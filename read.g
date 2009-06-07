#############################################################################
##
##  read.g                MapleForHomalg package              Thomas Bächler
##
##  Copyright 2009, Thomas Bächler, RWTH Aachen
##
##  Reading the implementation part of the MapleForHomalg package.
##
#############################################################################

# load kernel function if it is installed:
if (not IsBound(START_MAPLE_KERNEL)) and
   (Filename(DirectoriesPackagePrograms("mapleforhomalg"), "mapleforhomalg.so") <> fail) then
  LoadDynamicModule(Filename(DirectoriesPackagePrograms("mapleforhomalg"), "mapleforhomalg.so"));
fi;

if (not IsBound(START_MAPLE_KERNEL)) then
    Error( "Could not load MapleForHomalg plugin.\n" );
fi;

##
ReadPackage( "MapleForHomalg", "gap/MapleForHomalg.gi" );
