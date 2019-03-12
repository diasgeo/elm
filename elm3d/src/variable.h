//---------------------------------------------------------------------------------
//Input/Output File
#define Max(x,y) ( (x)>=(y)  ?  (x) : (y) )
#define Min(x,y) ( (x)<=(y)  ?  (x) : (y) )
#define output5		"vel"
#define ff 2

//---------------------------------------------------------------------------------
int geo[NumGeo][3];
FILE *trace_node[256];
int run_time,NumSnaps,NumSnapsS;
int source[3][NumSource];
int lr_count,lr_countx,lr_county,lr_countz;
double msource[Max_Time][NumSource];

double posn[Nx+2][Ny][Nz][3], force[Nx+2*ff][Ny][Nz][3];
double eqposn[Nx][Ny][Nz][3],up[Nx][Ny][Nz][3],dens[Nx+2][Ny][Nz];
double vp[Nx+2][Ny][Nz],vs[Nx+2][Ny][Nz];
double kspring[Nx][Ny][Nz][9], cbond[Nx][Ny][Nz][9];

int IndexX[9],IndexY[9],IndexZ[9];
double r0[9], ux[9],uy[9],uz[9],iroot2,dt2;
double abx[Nx],aby[Ny],abz[Nz];

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

