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

size := SizeScreen( );
SizeScreen([80]);

TestManualExamples( DirectoriesPackageLibrary( "MapleForHomalg", "doc" )[1]![1], "MapleForHomalg.xml", list );

GAPDocManualLab( "MapleForHomalg" );

SizeScreen( size );

quit;
