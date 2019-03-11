//---------------------------------------------------------------------------
// Parameters.h
//---------------------------------------------------------------------------
#define Max_Time 1001
#define Nx ( 60 )
#define Ny ( 300 )
//---------------------------------------------------------------------------
// BOUNDARY CONDITIONS
#define bound 0                // 0 -> no boundary: 1-> absorb boundary: 2 -> absorb + surface
#define lambda (1e-5)    // 0.0025 // decay constant for boundary (1/3n^2)
#define width 20             // no of absorbing columns
#define flat_surface 1
//---------------------------------------------------------------------------
// PHYSICAL VALUES
#define dt (1.5e-3)            // dt < sqrt(3)*diameter/(2*Vp)
#define dx (16.0)
#define density ( 2000.0 )          // in kg/m^3
#define velp (3500.0)              // in m/s
#define vels (2500.0) //        // in m/s
//---------------------------------------------------------------------------
// SOURCE
#define input_source 1          // 0-internal source; 1-external input source; 3-no source
#define input1 "SOURCE"
#define NumSource 1             // Number of entries in source_locations file
#define sdir 1                         // source direction 0=x  1=z 
#define sscale (1e+5)           // scale source amplitude by this factor
#define input2 "SIGNAL"         // source
//---------------------------------------------------------------------------
// RECEIVERS  &&  SNAPSHOTS
#define NumGeo 10             // Number of entries in geophone_locations file
#define input0 "STATIONS"     // trace coordinates in x y format
#define NumSnap 10          // No of snapshots
#define isnap 100              // snapshot record interval
#define snap_start 100         // start snapshot
//---------------------------------------------------------------------------
// I/O FILES
#define output0 "dps_geo"
#define output1 "bgk_geo"
#define output2 "vel"
#define output6 "disp"
#define output3 "pressure"
#define output4 "seismo"
#define output5 "parameters"
//---------------------------------------------------------------------------
