//Input/Output File
#define Fin 20                   // max. no. of input files
#define Fout 50                  // max. no. of output files
#define Max(x,y) ( (x)>=(y)  ?  (x) : (y) )
#define Min(x,y) ( (x)<=(y)  ?  (x) : (y) )
#define damp(x,y) ( 1-exp(-x*x*y) )
#define pi (3.1415927)
#define P 9
#define dt2 (dt*0.5)
#define NumSource 	1              // Number of entries in source_locations file
#define warp_around 1
//---------------------------------------------------------------------------------
// old rubbish
#define StartSource 0           // start source after 'StartSource' timesteps
#define center_freq  10          //
#define iroot2 (1.0/sqrt(2.0))
#define stress 0                 //0- no stress 1- stress
#define xposn  200
#define yposn  125
#define zposn  70
#define sigma1 (-100000)
#define incx 0
#define incy 0
#define incz 0
#define output6 "surface"
#define snap_surf 0  //0-no snap: 1-snap:
//---------------------------------------------------------------------------------

FILE *input[Fin],*output[Fout],*output_node[Fout],*out_trace_surf;
FILE *out_trace[NumGeo];

int phone[NumGeo][3],geo[NumGeo][3];
int m,run_time,NumSnaps;
int source[3][NumSource];

double H,Hall;
double ****force, ****posn,***upx,***upy,***upz;
double ***vp, ***vs,***dens, ****eqposn;
double r0[9], ux[9],uy[9],uz[9],****kspring,****cbond;
double *psource,*psource2,*psource3;
double abx[Nx];
double aby[Ny];
double abz[Nz];
char  *file_name[50], file_name7[50];

//MPI
int my_rank, my_size;
double left_p[Ny][Nz][3],right_p[Ny][Nz][3];
double temp_left_p[Ny][Nz][3],temp_right_p[Ny][Nz][3];

double temp_left_f[Ny][Nz][3],temp_right_f[Ny][Nz][3];
double left_f[Ny][Nz][3],right_f[Ny][Nz][3];

double larray1[Ny][Nz],rarray1[Ny][Nz];
double larray2[Ny][Nz],rarray2[Ny][Nz];
double larray3[Ny][Nz],rarray3[Ny][Nz];

MPI_Comm new_comm;
MPI_Status status;

// Modules:
#include"ALLOCATE.h"
#include"TRACE.h"
#include"ABSORB_FN.h"
#include"OUTPUT.h"
#include"SOURCE.h"
#include"INDEX.h"
#include"SEND.h"
#include"ASSIGN.h"
#include"OUTPUT_INITIAL.h"
#include"MERGE.h"
#include"INITIAL.h"
#include"EVOLUTION.h"



