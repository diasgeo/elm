//---------------------------------------------------------------------------------
// MODEL VALUE
#define Nx             (20)               // X DIR (mpi)
#define Ny             (100)              // Y DIR
#define Nz             (100)              // Z DIR
#define dx             (16)               // Grid Spacing
#define dt             (1.5e-3)             // Time step
#define Max_Time       501                // Max run iterations
//---------------------------------------------------------------------------------
// PHYSICAL VALUE
#define density       (2000.0)         // Density in kg/m^3
#define velp          (3500.0)         // P-wave in m/s  
#define vels          (2020.0)         // S-wave in m/s  
//----------------------------------------------------------------------------------
// BOUNDARY CONDITIONS
#define absorb_model      0           // 0->no boundary: 1->absorb: 2->absorb + surface
#define lambda            (1e-4)             // 1.5 2.0 4.0 decay constant for boundary
#define width             20                 // no of absorbing columns
#define topography  	  0           // 2-> two layers 1-> top file 0 -> none
#define flat              0                 // 1->flat surface 0 -> none //surf at Nz-4
#define input5            "glacier1sm"
//----------------------------------------------------------------------------------
// SOURCE
#define input_source 	1              // 0-internal ;  3-no source
#define NumSource 	1              // Number of entries in source_locations file
#define sdir 		2              // source direction 0=x  1=y 2=z  
#define sscale 		(1e+6)         // scale source amplitude by this factor
#define input1 		"SOURCE"     // source location file
#define input3 		"SIGNAL"     // source file
//----------------------------------------------------------------------------------
// RECEIVERS  &&  SNAPSHOTS
#define NumGeo		18             // Number of entries in geophone_locations file
#define input0 		"STATIONS"          // trace coordinates in x y format
#define LR              1              // rescale the 3d snapshots
#define NumSnap 	5              // No of snapshots
#define isnap 		100            // snapshot record interval
#define snap_start 	100            // start snapshot
//----------------------------------------------------------------------------------
#define output0 "dps_geo"
#define output1 "bgk_geo"
#define output2 "disp"
#define output3 "pressure"
#define output4 "seismo"
#define output5 "vel"
//---------------------------------------------------------------------------------
