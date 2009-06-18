##  this creates the documentation, needs: GAPDoc package, latex, pdflatex,
##  mkindex, dvips
##  
##  Call this with GAP.
##

LoadPackage( "MapleForHomalg" );

HOMALG_IO.show_banners := false;

LoadPackage( "GAPDoc" );

list := [
         "../gap/MapleForHomalg.gd",
         "../gap/MapleForHomalg.gi",
         ];

TestManualExamples( "doc", "MapleForHomalg.xml", list );

GAPDocManualLab( "MapleForHomalg" );

quit;
