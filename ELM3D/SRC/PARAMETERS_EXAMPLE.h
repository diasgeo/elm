//---------------------------------------------------------------------------------
// MODEL VALUE
#define Nx             (20)               // X DIR (mpi)
#define Ny             (100)              // Y DIR
#define Nz             (100)              // Z DIR
#define dx             (10)               // Grid Spacing
#define dt             (1.0e-3)             // Time step
#define Max_Time       1001                // Max run iterations
//---------------------------------------------------------------------------------
// PHYSICAL VALUE
#define density       (2400.0)         // Density in kg/m^3
#define velp          (3300.0)         // P-wave in m/s  
#define vels          (2500.0)      // S-wave in m/s  
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
#define sdir 		2              // source direction 0=x  1=y 2=z  
#define sscale 		(1e+8)         // scale source amplitude by this factor
#define input3 		"ricker2hz"     // source file
#define input1 		"location"     // source location file
//----------------------------------------------------------------------------------
// RECEIVERS  &&  SNAPSHOTS
#define NumGeo		18             // Number of entries in geophone_locations file
#define input0 		"rec"          // trace coordinates in x y format
#define LR              1              // rescale the 3d snapshots
#define NumSnap 	1              // No of snapshots
#define isnap 		1000            // snapshot record interval
#define snap_start 	1000            // start snapshot
//----------------------------------------------------------------------------------
#define output0		"dps_geo"
#define output1		"bgk_geo"
#define output2		"disp"
#define output3		"pressure"
#define output4		"Bseis2hz"
#define output5		"vel"
//---------------------------------------------------------------------------------
