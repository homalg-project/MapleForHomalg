##  this creates the documentation, needs: GAPDoc package, latex, pdflatex,
##  mkindex, dvips
##  
##  Call this with GAP.
##

LoadPackage( "GAPDoc" );

SetGapDocLaTeXOptions( "utf8" );

bib := ParseBibFiles( "doc/MapleForHomalg.bib" );
WriteBibXMLextFile( "doc/MapleForHomalgBib.xml", bib );

list := [
         "../gap/MapleForHomalg.gd",
         "../gap/MapleForHomalg.gi",
         ];

MakeGAPDocDoc( "doc", "MapleForHomalg", list, "MapleForHomalg" );

GAPDocManualLab("MapleForHomalg");

quit;

