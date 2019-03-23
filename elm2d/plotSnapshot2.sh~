#!/bin/bash
rm gmt.conf
rm gmt.history

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
#gmt gmtset FONT 9p,Times-Roman,black
gmt gmtset PS_MEDIA A4
#gmt gmtset PS_MEDIA letter   
gmt gmtset PS_PAGE_ORIENTATION portrait
#gmt gmtset GMT_VERBOSE d

exampleFolder=example/
figfolder=$exampleFolder\figures/
mkdir -p $figfolder

projection=X1.4i/1.4i
offset=1.4i

parameterFile=$exampleFolder\input/PARAMETERS.h
dx=`grep \ dx $parameterFile | cut -d "(" -f2 | cut -d ")" -f1`
Ny=`grep \ Ny $parameterFile | cut -d "(" -f2 | cut -d ")" -f1`
#Nx=`grep \ Nx $parameterFile | cut -d "(" -f2 | cut -d ")" -f1`
Nx=$Ny


source=$exampleFolder\input/source
coordinate=$exampleFolder/coordinate

minOldString1='(-1) sh mx'
minNewString1='(-max) sh mx'
maxOldString1='(1) sh mx'
maxNewString1='(max) sh mx'

minOldString2='(-1) bc Z'
minNewString2='(-max) bc Z'
maxOldString2='(1) bc Z'
maxNewString2='(max) bc Z'

scale=1

zmin=-1
zmax=1
zinc=`echo "($zmax-($zmin))/50" | bc -l`

cpt=$exampleFolder\snapshot.cpt
gmt makecpt -CGMT_seis.cpt -T$zmin/$zmax/$zinc -Z > $cpt
domain=1.1i/-0.4i/1.2i/0.16ih

#rm -f $coordinate
#for ix in $( seq 0 $((Nx-1)) )
#do
#for iy in $( seq 0 $((Ny-1)) )
#do
#echo $ix $iy >> $coordinate
#done
#done
#------------------------------------
number=2000
ps=$figfolder\disp$number.ps
eps=$figfolder\disp$number.eps
pdf=$figfolder\disp$number.pdf

sourceType=XForce
snapshotFile=$exampleFolder\disp$number\_$sourceType

xmin=`gmt gmtinfo $snapshotFile -C | awk '{print $1}'`
xmax=`gmt gmtinfo $snapshotFile -C | awk '{print $2}'`
ymin=`gmt gmtinfo $snapshotFile -C | awk '{print $3}'`
ymax=`gmt gmtinfo $snapshotFile -C | awk '{print $4}'`

x_normalization=`echo $xmin $xmax | awk ' { if(sqrt($1^2)>(sqrt($2^2))) {print sqrt($1^2)} else {print sqrt($2^2)}}'`
y_normalization=`echo $ymin $ymax | awk ' { if(sqrt($1^2)>(sqrt($2^2))) {print sqrt($1^2)} else {print sqrt($2^2)}}'`
normalization=`echo $x_normalization $y_normalization | awk ' { if($1>$2) {print $1} else {print $2}}'`

upperLimit=1
lowerLimit=-1
grd=$snapshotFile.nc


region=0/`echo "($Nx-1)*$dx/1000" | bc -l`/0/`echo "($Ny-1)*$dx/1000" | bc -l`
plotPointNumber=300
inc=`echo "($Nx-1)*$dx/1000/$plotPointNumber" | bc -l`

gmt gmtset MAP_FRAME_AXES wesn
paste -d ' ' $coordinate $snapshotFile | awk -v normalization="$normalization" -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000, $3/normalization }' > $snapshotFile.processed
cat $snapshotFile.processed | gmt blockmean -R$region -I$inc | gmt surface -Ll$lowerLimit -Lu$upperLimit -R$region -I$inc -G$grd
gmt grdimage -R$region -J$projection  -Bxa2f1+l"X (km) " -Bya2f1+l"Z (km)" $grd -C$cpt -K > $ps
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $source   | gmt psxy -R -J -Sa0.05i -Gred  -N -Wthinner,black -O -K  >> $ps
echo "4 4 X" | gmt pstext -R -J -F+jLB -N -O -K >> $ps
echo "0.5 0.5 $sourceType" | gmt pstext -R -J -F+jLB -N -O -K >> $ps

gmt gmtset MAP_FRAME_AXES wesn
paste -d ' ' $coordinate $snapshotFile | awk -v normalization="$normalization" -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000, $4/normalization }'> $snapshotFile.processed
cat $snapshotFile.processed | gmt blockmean -R$region -I$inc | gmt surface -Ll$lowerLimit -Lu$upperLimit -R$region -I$inc -G$grd
gmt grdimage -R$region -J$projection  -Bxa2f1+l"X (km) " -Bya2f1+l"Z (km)" $grd -C$cpt -X$offset -O -K >> $ps
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $source   | gmt psxy -R -J -Sa0.05i -Gred  -N -Wthinner,black -O -K >> $ps
echo "4 4 Z" | gmt pstext -R -J -F+jLB -N -O -K >> $ps
#------------------------------------
number=2000
ps=$figfolder\disp$number.ps
eps=$figfolder\disp$number.eps
pdf=$figfolder\disp$number.pdf

sourceType=MomentTensor
snapshotFile=$exampleFolder\disp$number\_$sourceType

xmin=`gmt gmtinfo $snapshotFile -C | awk '{print $1}'`
xmax=`gmt gmtinfo $snapshotFile -C | awk '{print $2}'`
ymin=`gmt gmtinfo $snapshotFile -C | awk '{print $3}'`
ymax=`gmt gmtinfo $snapshotFile -C | awk '{print $4}'`

x_normalization=`echo $xmin $xmax | awk ' { if(sqrt($1^2)>(sqrt($2^2))) {print sqrt($1^2)} else {print sqrt($2^2)}}'`
y_normalization=`echo $ymin $ymax | awk ' { if(sqrt($1^2)>(sqrt($2^2))) {print sqrt($1^2)} else {print sqrt($2^2)}}'`
normalization=`echo $x_normalization $y_normalization | awk ' { if($1>$2) {print $1} else {print $2}}'`

upperLimit=1
lowerLimit=-1
grd=$snapshotFile.nc

region=0/`echo "($Nx-1)*$dx/1000" | bc -l`/0/`echo "($Ny-1)*$dx/1000" | bc -l`
plotPointNumber=300
inc=`echo "($Nx-1)*$dx/1000/$plotPointNumber" | bc -l`

gmt gmtset MAP_FRAME_AXES wesn
paste -d ' ' $coordinate $snapshotFile | awk -v normalization="$normalization" -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000, $3/normalization }' > $snapshotFile.processed
cat $snapshotFile.processed | gmt blockmean -R$region -I$inc | gmt surface -Ll$lowerLimit -Lu$upperLimit -R$region -I$inc -G$grd
gmt grdimage -R$region -J$projection  -Bxa2f1+l"X (km) " -Bya2f1+l"Z (km)" $grd -C$cpt -X-$offset -Y-$offset -O -K >> $ps
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $source   | gmt psxy -R -J -Sa0.05i -Gred  -N -Wthinner,black -O -K  >> $ps
echo "4 4 X" | gmt pstext -R -J -F+jLB -N -O -K >> $ps
echo "0.5 0.5 $sourceType" | gmt pstext -R -J -F+jLB -N -O -K >> $ps

gmt gmtset MAP_FRAME_AXES wesn
paste -d ' ' $coordinate $snapshotFile | awk -v normalization="$normalization" -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000, $4/normalization }'> $snapshotFile.processed
cat $snapshotFile.processed | gmt blockmean -R$region -I$inc | gmt surface -Ll$lowerLimit -Lu$upperLimit -R$region -I$inc -G$grd
gmt grdimage -R$region -J$projection  -Bxa2f1+l"X (km) " -Bya2f1+l"Z (km)" $grd -C$cpt -X$offset -O -K >> $ps
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $source   | gmt psxy -R -J -Sa0.05i -Gred  -N -Wthinner,black -O -K >> $ps
echo "4 4 Z" | gmt pstext -R -J -F+jLB -N -O >> $ps
#------------------------------------

rm -f $grd
gmt psconvert -A -Te $ps -D$figfolder
epstopdf --outfile=$pdf $eps
#rm -f $ps $eps
rm -f $figfolder/ps2raster_*bb
