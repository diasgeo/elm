////////////////////////////////////////////////////////////////////
//  2D ELM - Gareth O'Brien 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mpi.h>
#include"parameters.h"
#include"variable.h"
////////////////////////////////////////////////////////////////////
// MAIN 
int main(int argc ,char *argv[])
{
 int i,j,k;
 int dims[1],period[1],reorder;
 int rank,size;
 double start, finish,t;

//////////////////////////////////////////////////////////////////
//           Initialising MPI
 MPI_Init(&argc,&argv);
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

 create_mpi_data_type();

/////////////////////////////////////////////////////////////////
// Initialising and Setting up Geometries
 initial_lattice_setup();

 //absorb_fn();

 if(layer==1) 
 {
   //setup_layer1();
   //setup_layer2();
 }
 if(topography==1) 
 {
  // setup_top();
 }

 set_up_geometry_and_neighbours();

 if(NumGeo>0)
 trace_files();

 if(input_source==1)
 source_routine();

////////////////////////////////////////////////////////////////
//  MAIN TIME LOOP
 for(run_time=0; run_time<Max_Time; run_time++)
 {
   // Main Rock Evolution Routine
   evolve();

    // Output seismograms
    if(NumGeo>0)
    write_trace();

    // Output snap shots at various stages
    if(run_time>=snap_start && (run_time)%isnap==0 && NumSnaps<NumSnap)
    {
      //snap_disp(); 
      snap_vel();
      NumSnaps++;
    }

    if(my_rank==0 && run_time%100==0)
    printf("Time Step=%d \n",run_time);
  }

///////////////////////////////////////////////////////////////////
//  MERGING AND CLOSING FILES AND ENDING
  if(NumGeo>0)
  close_trace();

  if(my_rank==1 && NumSnap!=0)
  {
    merge_vel();
  }


 finish=MPI_Wtime();
 printf(" OUPUT LR t=%d x=%d %d y=%d z=%d\n",lr_count,lr_countx,lr_countx*my_size,lr_county,lr_countz);
 printf("Time for run on node %d is %lf minutes \n",my_rank,(finish-start)/60);

 MPI_Finalize();

}

