//---------------------------------------------------------------------------------
// MODEL VALUE
#define Nx             (16)    // run on 64 nodes
#define Ny             (128)              // Y DIR
#define Nz             (60)              // Z DIR
#define dx             (40.0)         // Grid Spacing
#define dt             (1.0e-3)        // Time step
#define Max_Time       (10001)            // Max run iterations
//---------------------------------------------------------------------------------
// PHYSICAL VALUE
#define velocity_model (0)             // 0 - homo model: 1-hetero model
#define input0        "none"           //
#define density       (2500.00)         // Density in kg/m^3
#define velp          (3000.00)         // P-wave in m/s  
#define vels          (1850.00)         // S-wave in m/s  
//----------------------------------------------------------------------------------
// BOUNDARY CONDITIONS
#define absorb_model    0           // 0->no boundary: 1->absorb: 2->absorb + surface
#define lambda         (0)      // 1.5 2.0 4.0 decay constant for boundary
#define width           0           // no of absorbing columns
#define topography       0            // 2-> two layers 1-> top file 0 -> none
#define input5        "none"     //topography 
//----------------------------------------------------------------------------------
// SOURCE
#define input_source 	1              // 0 source off : 1 source on
#define NumSource       1              // Number of entries in source_locations file
#define sdir 		3              // source direction 0=x  1=y 2=z expl=3
#define sscale 		(1e+10)         // scale source amplitude by this factor
#define input3 		"input/signal"      // source file
#define input2 		"input/source"     // source location file
//----------------------------------------------------------------------------------
// RECEIVERS  &&  SNAPSHOTS
#define NumGeo		13           // Number of entries in geophone_locations file
#define input1 	      "input/stations"     // trace coordinates in x y format
#define LR              1             // rescale the 3d snapshots
#define NumSnap 	2            // No of snapshots
#define isnap 		5000            // snapshot record interval
#define snap_start 	5000            // start snapshot
#define NumSnapS 	10             // No of surface snapshots
#define isnapS 		1000           // surface snapshot record interval
//----------------------------------------------------------------------------------
// OUTPUT FILE NAMES
#define output2		"disp"
#define output4		"bulk_rec"
#define output6         "surface"     // outputs surface traces
//---------------------------------------------------------------------------------
#define mxx (1.0)
#define myy (1.0)
#define mzz (1.0)
#define mxy (0.0)
#define mxz (0.0)
#define myz (0.0)
//---------------------------------------------------------------------------------
