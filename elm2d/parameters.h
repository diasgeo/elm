//---------------------------------------------------------------------------------
// MODEL VALUE
#define Nx             (32)            // run on 64 nodes
#define Ny             (200)          // Y DIR
#define dx             (40.0)         // Grid Spacing
#define dt             (1.0e-3)       // Time step
#define Max_Time       (10001)         // Max run iterations
//---------------------------------------------------------------------------------
// PHYSICAL VALUE
#define velocity_model (0)             // 0 - homo model: 1-hetero model
#define input8        "none"           //
#define density       (2000.00)         // Density in kg/m^3
#define velp          (2000.00)         // P-wave in m/s  
#define vels          (1154.70)         // S-wave in m/s  
//----------------------------------------------------------------------------------
// BOUNDARY CONDITIONS
#define absorb_model    0           // 0->no boundary: 1->absorb: 2->absorb + surface
#define lambda         (1)      // 1.5 2.0 4.0 decay constant for boundary
#define width           1           // no of absorbing columns
#define topography      0            // 2-> two layers 1-> top file 0 -> none
#define layer           0            // input layer tracking topography
#define input5        "none"     //topography 
//----------------------------------------------------------------------------------
// SOURCE
#define input_source 	1              // 0 source off : 1 source on
#define NumSource       1              // Number of entries in source_locations file
#define sdir 		1              // source direction 0=x  1=y expl=2
#define sscale 		(1e+6)         // 0.00625 scale source amplitude by this factor
#define input2 		"source.dat"       // source file
#define input1 		"location"     // source location file
//----------------------------------------------------------------------------------
// RECEIVERS  &&  SNAPSHOTS
#define NumGeo		31           // Number of entries in geophone_locations file
#define input6 	      "recorder"     // trace coordinates in x y format
#define LR              1             // rescale the 3d snapshots
#define NumSnap 	10             // No of snapshots
#define isnap 		1000            // snapshot record interval
#define snap_start 	1000            // start snapshot
#define NumSnapS 	0             // No of surface snapshots
#define isnapS 		0           // surface snapshot record interval
//----------------------------------------------------------------------------------
// OUTPUT FILE NAMES
#define output2		"ELMdisp"
#define output4		"ELMstation"
#define output5         "ELMvel"     // outputs surface traces
//---------------------------------------------------------------------------------