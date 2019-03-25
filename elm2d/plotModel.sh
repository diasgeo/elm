#!/bin/bash

rm gmt.conf
rm gmt.history

gmt gmtset MAP_FRAME_AXES WeSn
gmt gmtset MAP_FRAME_TYPE plain
gmt gmtset MAP_FRAME_PEN thick
gmt gmtset MAP_TICK_PEN thick
gmt gmtset MAP_TICK_LENGTH_PRIMARY -3p
#gmt gmtset MAP_DEGREE_SYMBOL none
#gmt gmtset MAP_GRID_CROSS_SIZE_PRIMARY 0.0i
#gmt gmtset MAP_GRID_CROSS_SIZE_SECONDARY 0.0i
#gmt gmtset MAP_GRID_PEN_PRIMARY thin,black
#gmt gmtset MAP_GRID_PEN_SECONDARY thin,black
gmt gmtset MAP_ORIGIN_X 100p
gmt gmtset MAP_ORIGIN_Y 100p
#gmt gmtset FORMAT_GEO_OUT +D
gmt gmtset COLOR_NAN 255/255/255
gmt gmtset COLOR_FOREGROUND 255/255/255
gmt gmtset COLOR_BACKGROUND 0/0/0
gmt gmtset FONT 12p,Helvetica,black
#gmt gmtset PS_MEDIA custom_2.8ix2.8i
gmt gmtset PS_MEDIA letter
gmt gmtset PS_PAGE_ORIENTATION portrait
#gmt gmtset GMT_VERBOSE d

exampleFolder=example/
figfolder=$exampleFolder\figures/
mkdir -p $figfolder

parameterFile=$exampleFolder\input/PARAMETERS.h
dx=`grep \ dx $parameterFile | cut -d "(" -f2 | cut -d ")" -f1`
Ny=`grep \ Ny $parameterFile | cut -d "(" -f2 | cut -d ")" -f1`
#Nx=`grep \ Nx $parameterFile | cut -d "(" -f2 | cut -d ")" -f1`
Nx=$Ny

topo_polygon=$exampleFolder/topo_polygon
topo=$exampleFolder\input/topo
cat $topo > $topo_polygon
echo $(($Nx-1)) $(($Ny-1)) >> $topo_polygon
echo 0 $(($Ny-1)) >> $topo_polygon
echo 0 0 >> $topo_polygon

source=$exampleFolder\input/source
stations=$exampleFolder\input/stations
coordinate=$exampleFolder/coordinate

#rm -f $coordinate
#for ix in $( seq 0 $((Nx-1)) )
#do
#for iy in $( seq 0 $((Ny-1)) )
#do
#echo $ix $iy >> $coordinate
#done
#done
#-----------------------------------------------------
name=vp
domain=1.1i/-0.6i/1.4i/0.16ih
projection=X2.2i

scale=`echo "1000/$dx" | bc -l`
plotPointNumber=300
inc=`echo "($Nx-1)/$scale/$plotPointNumber" | bc -l`

originalxyz=$exampleFolder\input/$name
processedxyz=$exampleFolder$name.processed
cpt=$exampleFolder$name.cpt
grd=$exampleFolder$name.nc
grad=$exampleFolder$name.int.nc
ps=$figfolder$name.ps
eps=$figfolder$name.eps
pdf=$figfolder$name.pdf

xmin=`gmt gmtinfo $originalxyz -C | awk -v scale="$scale" '{print $1/scale}'`
xmax=`gmt gmtinfo $originalxyz -C | awk -v scale="$scale" '{print $2/scale}'`
ymin=`gmt gmtinfo $originalxyz -C | awk -v scale="$scale" '{print $3/scale}'`
ymax=`gmt gmtinfo $originalxyz -C | awk -v scale="$scale" '{print $4/scale}'`
zmin=`gmt gmtinfo $originalxyz -C | awk '{print $5/1000}'`
zmax=`gmt gmtinfo $originalxyz -C | awk '{print $6/1000}'`
zmin=3.5 
zmax=5.5
zinc=`echo "($zmax-$zmin)/100" | bc -l`

region=0/`echo "($Nx-1)/$scale" | bc -l`/0/`echo "($Ny-1)/$scale" | bc -l`


gmt makecpt -CGMT_rainbow.cpt -T$zmin/$zmax/$zinc -Z > $cpt


cat $originalxyz | awk -v scale="$scale" '{ print $1/scale, $2/scale, $3/1000 }' | gmt blockmean -R$region -I$inc > $processedxyz
cat $processedxyz | gmt blockmode -R$region -I$inc | gmt surface -R$region -I$inc -G$grd
gmt grdgradient $grd -A15 -Ne0.75 -G$grad

gmt grdimage -R$region -J$projection $grd -C$cpt -Bxa2f1+l"X (km)" -Bya2f1+l"Z (km)" -K > $ps #  Bya2fg2
awk -v scale="$scale" '{ print $1/scale, $2/scale }' $stations | gmt psxy -R -J -St0.1i -Gblue -N -Wthinner,black -O -K >> $ps
awk -v scale="$scale" '{ print $1/scale, $2/scale }' $source   | gmt psxy -R -J -Sa0.05i -Gred  -N -Wthinner,black -O -K >> $ps
awk -v scale="$scale" '{ print $1/scale, $2/scale }' $topo_polygon | gmt psxy -R -J -Ggray -W1p -O -K >> $ps #-L+yt -Ggray 

gmt psscale -D$domain -C$cpt  -Bxa1f0.5+l"P-wave velocity (km/s)" -O >> $ps

gmt psconvert -A -Te $ps -D$figfolder
epstopdf --outfile=$pdf $eps

rm -f $grd $grad $cpt $processedxyz
rm -f $eps $ps
rm -f $figfolder\ps2raster_*bb
