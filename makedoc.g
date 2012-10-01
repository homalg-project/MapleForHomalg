##  this creates the documentation, needs: GAPDoc package, latex, pdflatex,
##  mkindex, dvips
##  
##  Call this with GAP.
##

LoadPackage( "GAPDoc" );

SetGapDocLaTeXOptions( "utf8" );

bib := ParseBibFiles( "doc/MapleForHomalg.bib" );
WriteBibXMLextFile( "doc/MapleForHomalgBib.xml", bib );

Read( "ListOfDocFiles.g" );

PrintTo( "VERSION", PackageInfo( "MapleForHomalg" )[1].Version );

MakeGAPDocDoc( "doc", "MapleForHomalg", list, "MapleForHomalg" );

GAPDocManualLab( "MapleForHomalg" );

QUIT;
