//---------------------------------------------------------------------------
// PARAMETERS.h
//---------------------------------------------------------------------------
#define Max_Time (10001)       // No of time steps
#define Nx ( 55)         // Length of x grid (mpi)
#define Ny ( 495 )        // Length of y grid (no mpi)
//---------------------------------------------------------------------------
// BOUNDARY CONDITIONS
#define absorb_model   2        // 0 -> off 1-> full on: 2 -> surface on;
#define lambda       (2.5e-6)     // decay constant for boundary (1/3n^2)
#define width         100        // no of absorbing columns
#define flat_surface   0        // 0- no flat surface 1-flat surface at Ny-4
#define topography     0        // 0-topography off ; 1-> topography on
#define input5      "./input/topo"    // topography file (x,y)
#define velocity_model 0        // 0-homogeneous: 1-input file:
#define input4    "./input/vp"    // P-velocity file
//---------------------------------------------------------------------------
// PHYSICAL VALUES
#define dt (0.0005)            // Time step 
#define dx (10.0)              // Grid spacing
#define density (2000.0)       // Density in kg/m^3
#define velp (3500.00)         // P-wave in m/s
#define vels (2500.00)         // S-wave in m/s
//---------------------------------------------------------------------------
// SOURCE
#define input_source 1          // 1-external input source; 3-no source
#define input1 "./input/source"       // Source location file
#define NumSource 1             // Number of entries in source_locations file
#define sdir 3                  // Source direction 0=x  1=z 3=explosive
#define sscale (1e+8)           // Scale source amplitude by this factor (Force)
#define input2 "./input/signal"       // Source file
#define mxx 1.0
#define mzz 1.0
#define mxz 0.0
//---------------------------------------------------------------------------
// RECEIVERS  &&  SNAPSHOTS
#define NumGeo 1              // Number of entries in geophone file
#define input0 "./input/stations" // Trace coordinates in x y format
#define NumSnap 2           // No of snapshots
#define isnap 500                // Snapshot record interval
#define snap_start 1000        // Start snapshots
//---------------------------------------------------------------------------
// Fracture models
#define fracture_model 0       // Fractures on 1 or off 0
#define NoFrac  105            // No of fractures
#define input3  "fractures"        // Fracture file
//---------------------------------------------------------------------------
// I/O FILES
#define output2 "vel"         // Velocity snapshots
#define output6 "disp"        // Displacement snapshots
#define output4 "station"     // Seismograms 
//---------------------------------------------------------------------------
