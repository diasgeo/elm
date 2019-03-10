//Input/Output File
#define Fin 20                   // max. no. of input files
#define Fout 50                  // max. no. of output files

FILE *input[Fin],*output[Fout],*output_node[Fout],*out_trace_surf;

int phone[NumGeo][2],geo[NumGeo][2];
FILE *out_trace[NumGeo];

// Functions:
#define Max(x,y) ( (x)>=(y)  ?  (x) : (y) )
#define Min(x,y) ( (x)<=(y)  ?  (x) : (y) )
#define damp(x,y) ( 1-exp(-x*x*y) )
#define pi (3.1415927)
#define dt2 (dt*0.5)
#define root2 sqrt(2.0)

int m,run_time,NumSnaps;
int source[2][NumSource];

double ***force, ***posn,**upx,**upy;
double **vp,**vs,**dens,disp[Ny][Nx][2],***eqposn;
double ***r0, ***kspring,***cbond;
double *psource;
double left_v[2][Ny],right_v[2][Ny],templeft_v[2][Ny],tempright_v[2][Ny];
double left_p[Ny][2],right_p[Ny][2],temp_left_p[Ny][2],temp_right_p[Ny][2];
double left_f[Ny][2],right_f[Ny][2],temp_forcer[Ny][2],temp_forcel[Ny][2];
double larray1[Ny],rarray1[Ny];
double larray2[Ny],rarray2[Ny];
double larray3[Ny],rarray3[Ny];
double ux[8],uz[8];

char  *file_name[50], file_name7[50];

//MPI
int my_rank, my_size;
MPI_Comm new_comm;
MPI_Status status;

// Modules:
#include"ALLOCATE.h"
#include"SOURCE.h"
#include"TRACE.h"
#include"ABSORB_VEL.h"
#include"OUTPUT.h"
#include"INDEX.h"
#include"SEND.h"
#include"SETUP.h"
#include"OUTPUT_INITIAL.h"
#include"MERGE.h"
#include"INITIAL.h"
#include"EVOLVE.h"
