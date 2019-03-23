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

rm -f $coordinate
for ix in $( seq 0 $((Nx-1)) )
do
for iy in $( seq 0 $((Ny-1)) )
do
echo $ix $iy >> $coordinate
done
done

snapshotNormalizationFile=$exampleFolder\disp2000

xmin=`gmt gmtinfo $snapshotNormalizationFile -C | awk '{print $1}'`
xmax=`gmt gmtinfo $snapshotNormalizationFile -C | awk '{print $2}'`
ymin=`gmt gmtinfo $snapshotNormalizationFile -C | awk '{print $3}'`
ymax=`gmt gmtinfo $snapshotNormalizationFile -C | awk '{print $4}'`
x_normalization=`echo $xmin $xmax | awk ' { if(sqrt($1^2)>(sqrt($2^2))) {print sqrt($1^2)} else {print sqrt($2^2)}}'`
y_normalization=`echo $ymin $ymax | awk ' { if(sqrt($1^2)>(sqrt($2^2))) {print sqrt($1^2)} else {print sqrt($2^2)}}'`
normalization=`echo $x_normalization $y_normalization | awk ' { if($1>$2) {print $1} else {print $2}}'`

upperLimit=1
lowerLimit=-1
snapshotFile=$exampleFolder\snapshot
grd=$snapshotFile.nc

projection=X2.2i/2.2i
offset=2.2i

region=0/`echo "($Nx-1)*$dx/1000" | bc -l`/0/`echo "($Ny-1)*$dx/1000" | bc -l`
plotPointNumber=300
inc=`echo "($Nx-1)*$dx/1000/$plotPointNumber" | bc -l`

allSnapshots=`ls example/disp* | cut -d "/" -f 2`

for iSnapshot in $allSnapshots;
do

ps=$figfolder`echo $iSnapshot | cut -d '.' -f 1`.ps
eps=$figfolder`echo $iSnapshot | cut -d '.' -f 1`.eps
pdf=$figfolder`echo $iSnapshot | cut -d '.' -f 1`.pdf

gmt gmtset MAP_FRAME_AXES WeSn
paste -d ' ' $coordinate $exampleFolder$iSnapshot | awk -v normalization="$normalization" -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000, $3/normalization }'> $snapshotFile
cat $snapshotFile | gmt blockmean -R$region -I$inc | gmt surface -Ll$lowerLimit -Lu$upperLimit -R$region -I$inc -G$grd
gmt grdimage -R$region -J$projection  -Bxa2f1+l"X (km) " -Bya2f1+l"Z (km)" $grd -C$cpt -K > $ps
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $topo_polygon | gmt psxy -R -J -Ggray -W1p -O -K >> $ps #-L+yt -Ggray 
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $stations | gmt psxy -R -J -St0.05i -Gblue -N -Wthinner,black -O -K >> $ps
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $source   | gmt psxy -R -J -Sa0.05i -Gred  -N -Wthinner,black -O -K  >> $ps
echo "4 4 X" | gmt pstext -R -J -F+jLB -N -O -K >> $ps

gmt gmtset MAP_FRAME_AXES wesn
paste -d ' ' $coordinate $exampleFolder$iSnapshot | awk -v normalization="$normalization" -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000, $4/normalization }'> $snapshotFile
cat $snapshotFile | gmt blockmean -R$region -I$inc | gmt surface -Ll$lowerLimit -Lu$upperLimit -R$region -I$inc -G$grd
gmt grdimage -R$region -J$projection  -Bxa2f1+l"X (km) " -Bya2f1+l"Z (km)" $grd -C$cpt -X$offset -O -K >> $ps
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $topo_polygon | gmt psxy -R -J -Ggray -W1p -O -K >> $ps #-L+yt -Ggray 
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $stations | gmt psxy -R -J -St0.05i -Gblue -N -Wthinner,black -O -K >> $ps
awk -v dx="$dx" '{ print $1*dx/1000, $2*dx/1000 }' $source   | gmt psxy -R -J -Sa0.05i -Gred  -N -Wthinner,black -O -K >> $ps
echo "4 4 Z" | gmt pstext -R -J -F+jLB -N -O >> $ps

#gmt psscale -D$domain -C$cpt -E -Bx1f0.5 -O | sed "s/$minOldString1/$minNewString1/g" | sed "s/$minOldString2/$minNewString2/g" | sed "s/$maxOldString1/$maxNewString1/g" | sed "s/$maxOldString2/$maxNewString2/g">> $ps

rm -f $grd
gmt psconvert -A -Te $ps -D$figfolder
epstopdf --outfile=$pdf $eps
rm -f $ps $eps
rm -f $figfolder/ps2raster_*bb

done

for isnap in $(seq 200 200 8000)
do
PDFName=$figfolder\disp$isnap.pdf
totalPDFName+=" $PDFName"
done
gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=$figfolder\merged.pdf $totalPDFName
