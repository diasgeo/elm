//---------------------------------------------------------------------------------
//Input/Output File
#define Max(x,y) ( (x)>=(y)  ?  (x) : (y) )
#define Min(x,y) ( (x)<=(y)  ?  (x) : (y) )
#define Gauss(x,y,a)  exp( -(x*x+y*y)/(a*a) )
//#define output5		"vel"
#define ff 2
#define P 8
#define Pl 8

//---------------------------------------------------------------------------------
FILE *out_trace[NumGeo];
int phone[NumGeo][2],geo[NumGeo][2];
FILE *trace_node[256];
int run_time,NumSnaps,NumSnapsS;
int source[3][NumSource];
int lr_count,lr_countx,lr_county,lr_countz;
//double msource[Max_Time][9][NumSource];
double psource[Max_Time],psource1[Max_Time],gauss[Nx][Ny];

double posn[Nx+2][Ny][2], force[Nx+2*ff][Ny][2];
double eqposn[Nx][Ny][2],up[Nx][Ny][2],dens[Nx+2][Ny];
double vp[Nx+2][Ny],vs[Nx+2][Ny];
double kspring[Nx][Ny][P], cbond[Nx][Ny][P];

int IndexX[P],IndexY[P],IndexZ[P];
double r0[Nx][Ny][P], ra[P],ux[P],uy[P],uz[P],iroot2,dt2;
double abx[Nx],aby[Ny];

//---------------------------------------------------------------------------------
//MPI
#define MAX_NB_OF_COMM 512
int my_rank, my_size;
MPI_Comm new_comm;
MPI_Status status;
const  int  TAG_SEND   = 50;
const  int  ndims      = 1;
MPI_Datatype fcol;             // new datatype for the slice
MPI_Datatype scol;             // new datatype for the slice
MPI_Request array_of_requests[MAX_NB_OF_COMM];
MPI_Status  array_of_statuses[MAX_NB_OF_COMM];

//---------------------------------------------------------------------------------
#include"initial.h"
#include"transfer.h"
#include"absorb_fn.h"
#include"assign.h"
#include"source.h"
#include"evolution.h"
#include"trace.h"
#include"output_snaps.h"
//---------------------------------------------------------------------------------

