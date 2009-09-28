#############################################################################
##
##  MapleForHomalg.gi           MapleForHomalg package        Thomas Bächler
##
##  Copyright 2009, Thomas Bächler, RWTH Aachen
##
##  Implementation stuff for MapleForHomalg.
##
#############################################################################

####################################
#
# global variables:
#
####################################

InstallValue( MapleForHomalg,
        rec(
            
            )
);

####################################
#
# initialization
#
####################################

HOMALG_IO_Maple.LaunchCAS := LaunchCASMapleForHomalg;

####################################
#
# methods for operations:
#
####################################

InstallGlobalFunction( LaunchCASMapleForHomalg,
  function( arg )
    local s, success, pid;
    
    success := START_MAPLE_KERNEL();
    if (success) then
      pid := EvalString(EXECUTE_MAPLE_COMMAND( "kernelopts(pid);" )[1]);
      
      s := rec(
                lines := "",
                errors := "",
                SendBlockingToCAS := SendBlockingToCASMapleForHomalg,
                TerminateCAS := TerminateCASMapleForHomalg,
                pid := pid,
                trim_display := ""
              );
      return s;
    else
      return fail;
    fi;
end );

InstallGlobalFunction( SendBlockingToCASMapleForHomalg,
  function( arg )
    local r;
    
    if ( Length( arg ) = 2 and IsRecord( arg[1] ) and IsString( arg[2] ) ) then
      r := EXECUTE_MAPLE_COMMAND( arg[2] );
      arg[1].lines := r[1];
      arg[1].errors := r[2];
    else
      Error("Wrong number or type of arguments.");
    fi;
end );

InstallGlobalFunction( TerminateCASMapleForHomalg,
  function( arg )
    # Make this a no-op, as we can never re-start the Maple kernel
    # The kernel will exit when gap exits
    # STOP_MAPLE_KERNEL();
end );

#############################################
#
# Override Display method for MapleForHomalg
#
#############################################

MapleMacros.MatrixPrint := "\n\
  HomalgMatrixPrint := proc(Mat)\n\
    local M, c, r:\n\
    M := convert(Mat, listlist):\n\
    r := \"\":\n\
    for c in M do\n\
      r := cat(r, convert(c, string), \"\\n\"):\n\
    od:\n\
    return StringTools[Trim](r):\n\
  end:\n\
\n";

##
InstallMethod( Display,
        "for homalg matrices in Maple",
        [ IsHomalgExternalMatrixRep ], 1,
  function( o )
    if IsHomalgExternalRingInMapleRep( HomalgRing( o ) ) then
        Print( homalgSendBlocking( [ "HomalgMatrixPrint(", HomalgRing( o ), "[-1][matrix](", o, "))" ], "need_display", HOMALG_IO.Pictograms.Display ) );
    else
        TryNextMethod( );
    fi;
end );
