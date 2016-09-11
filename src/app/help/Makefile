# ///////////////////////////////////////////////////////////////////
# filename: Makefile
# author name: Aaron Licata
# creation date: 04/03/01
# last modified: 04/03/01
#
# purpose: makefile for recovery3d project
#
# //////////////////////////////////////////////////////////////////

recov3d: apperr.o appio.o ccenter.o clock.o crust.o delaunay.o filept2.o geom.o geomutil.o geostat.o mainvoro.o math.o rabdata.o rendergl.o skeleton.o visualize.o visdebug.o wininfo.o 
	g++ -lGL -lGLU -lglut apperr.o appio.o ccenter.o clock.o crust.o delaunay.o filept2.o geom.o geomutil.o geostat.o mainvoro.o math.o rabdata.o rendergl.o skeleton.o visualize.o visdebug.o wininfo.o

apperr.o: apperr.cpp apperr.h config.h
	g++ -c apperr.cpp 

appio.o: appio.cpp appio.h clock.cpp clock.h config.h 
	g++ -c appio.cpp

ccenter.o: ccenter.cpp ccenter.h clock.cpp clock.h config.h
	g++ -c ccenter.cpp 

clock.o: clock.cpp clock.h appio.cpp appio.h config.h
	g++ -c clock.cpp

crust.o: crust.cpp crust.h config.h math.cpp math.h delaunay.h delaunay.cpp geom.h geom.cpp
	g++ -c crust.cpp

filept2.o: filept2.cpp filept2.h geom.h geom.cpp rabdata.h rabdata.cpp config.h
	g++ -c filept2.cpp

geom.o: geom.cpp geom.h config.h appio.cpp appio.h apperr.h apperr.cpp math.cpp math.h ccenter.cpp ccenter.h 
	g++ -c geom.cpp

geomutil.o: geomutil.cpp geomutil.h config.h geom.h geom.cpp ccenter.cpp ccenter.h
	g++ -c geomutil.cpp

geomstat.o: geomstat.cpp geomstat.h geom.cpp geom.h appio.h appio.cpp config.h 
	g++ -c geostat.cpp

mainvoro.o: mainvoro.cpp math.h math.cpp geom.cpp geom.h geomutil.cpp geomutil.h geostat.cpp geostat.h ccenter.h ccenter.cpp delaunay.cpp delaunay.h rabdata.h rabdata.cpp rendergl.cpp rendergl.h visualize.h visualize.cpp visdebug.h visdebug.cpp appio.h appio.cpp clock.cpp clock.h wininfo.cpp wininfo.h filept2.cpp filept2.h 
	g++ -c mainvoro.cpp

math.o: math.cpp math.h config.h
	g++ -c math.cpp

rabdata.o: rabdata.cpp rabdata.h 
	g++ -c rabdata.cpp

rendergl.o: rendergl.cpp rendergl.h math.h math.cpp geom.h geom.cpp geomutil.cpp geomutil.h delaunay.cpp delaunay.h visualize.h visualize.cpp visdebug.cpp visdebug.h STL.h config.h
	g++ -c rendergl.cpp

skeleton.o: skeleton.cpp geom.h geom.cpp config.h
	g++ -c skeleton.cpp

visdebug.o: visdebug.cpp visdebug.h math.cpp math.h geom.cpp geom.h geomutil.cpp geomutil.h geostat.cpp geostat.h appio.h appio.cpp STL.h config.h
	g++ -c visdebug.cpp

visualize.o: visualize.cpp visualize.h geom.h geom.cpp math.cpp math.h geomutil.cpp geomutil.h geostat.cpp geostat.h appio.cpp appio.h STL.h crust.cpp crust.h config.h
	g++ -c visualize.cpp

wininfo.o: wininfo.cpp wininfo.h appio.h appio.cpp config.h
	g++ -c wininfo.cpp






 



