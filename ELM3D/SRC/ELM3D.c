////////////////////////////////////////////////////////////////////
///  3D Spring network                                
////////////////////////////////////////////////////////////////////
///  03/09/2005 Gareth O'Brien 
////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mpi.h>
#include"PARAMETERS.h"
#include"VARIABLES.h"
                                /* MAIN */
main(int argc ,char *argv[])
{
  int i,j,k;
  int dims[1],period[1],reorder;
  int rank,size;
  double start,finish,t;

////////////////////////////////////////////////////////////////////////////////
//  Initialising MPI
///////////////////////////////////////////////////////////////////////////////
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
dims[0]=size;
period[0]=1;
reorder=1;
MPI_Cart_create(MPI_COMM_WORLD, 1, dims, period, reorder, &new_comm);
MPI_Comm_rank(new_comm, &my_rank);
MPI_Comm_size(new_comm, &my_size);

if( argc!=1)
{
   printf(" Incorrect usage -- try again -- \n");
   MPI_Finalize(); exit(0);
}
start=MPI_Wtime();

////////////////////////////////////////////////////////////////////////////
// Initialising and Setting up Geometries
////////////////////////////////////////////////////////////////////////////
      initial_lattice_setup();
      
      absorb_fn();
      
      if(topography==1)
      setup_top();
      
      set_up_geometry_and_neighbours();

      if(NumGeo>0)
      trace_files();

      if(input_source<3)
      {
       source_routine();
      }
      
///////////////////////////////////////////////////////////////////////////////
///  MAIN TIME LOOP
for(run_time=0; run_time<Max_Time; run_time++)
{
   // Main Rock Evolution Routine
   evolve();
        
///////////////////////////////////////////////////////////////////////////////
// Outputs
///////////////////////////////////////////////////////////////////////////////
   if(NumGeo>0)
   write_trace();

   // output snap shots at various stages
   if(run_time>=snap_start && (run_time)%isnap==0 && NumSnaps<NumSnap)
   {
       snap_disp_LR();
       snap_vel_LR();
       MPI_Barrier(new_comm);
       NumSnaps++;
   }

  // if(my_rank==0)
  // printf("%d %e\n",run_time,Hall);
  
   if(my_rank==0 && run_time%20==0)
   printf("Time Step=%d \n",run_time);

}

///////////////////////////////////////////////////////////////////////////////
//  MERGING AND CLOSING FILES AND ENDING
///////////////////////////////////////////////////////////////////////////////

if(NumGeo>0)
close_trace();

//merge files
MPI_Barrier(new_comm);
if(my_rank==0 && NumSnap!=0)
{
 merge_disp_LR();
 merge_vel_LR();
}
//snap_surface();

 finish=MPI_Wtime();
 printf(" Time for run on node %d is %lf minutes \n",my_rank,(finish-start)/60);

 MPI_Finalize();

}

