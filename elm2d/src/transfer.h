

void create_mpi_data_type()
{

 int count = 1;
 int blocklen = Ny;
 int stride = 0;

 MPI_Type_vector(count, blocklen, stride,MPI_DOUBLE, &scol);
 MPI_Type_commit(&scol);

 count = 1;
 blocklen = Ny*2;
 stride = 0;

 MPI_Type_vector(count, blocklen, stride,MPI_DOUBLE, &fcol);
 MPI_Type_commit(&fcol);

}

void vp_mpi()
{
 int index_of_comm = 0; // index for the above array

 if(my_rank==0)
 {
   MPI_Isend(&vp[1][0],1,scol,my_size-1,50,new_comm, &array_of_requests[index_of_comm++]);
   MPI_Irecv(&vp[Nx+1][0],1,scol,my_rank+1,50,new_comm, &array_of_requests[index_of_comm++]);

   MPI_Irecv(&vp[0][0],1,scol,my_size-1,50,new_comm, &array_of_requests[index_of_comm++] );
   MPI_Isend(&vp[Nx][0],1,scol,my_rank+1,50,new_comm, &array_of_requests[index_of_comm++]);
 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Isend(&vp[1][0],1,scol,my_rank-1,50,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Irecv(&vp[Nx+1][0],1,scol,my_rank+1,50,new_comm, &array_of_requests[index_of_comm++]);

  MPI_Irecv(&vp[0][0],1,scol,my_rank-1,50,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Isend(&vp[Nx][0],1,scol,my_rank+1,50,new_comm,  &array_of_requests[index_of_comm++]);
 }
 else if( my_rank == (my_size-1) )
 {
   MPI_Irecv(&vp[Nx+1][0],1,scol,0,50,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Isend(&vp[1][0],1,scol,my_rank-1,50,new_comm,  &array_of_requests[index_of_comm++]);

   MPI_Isend(&vp[Nx][0],1,scol,0,50,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Irecv(&vp[0][0],1,scol,my_rank-1,50,new_comm, &array_of_requests[index_of_comm++]);
 }
 MPI_Waitall(index_of_comm, array_of_requests, array_of_statuses);

}

void vs_mpi()
{
 int index_of_comm = 0; // index for the above array

 if(my_rank==0)
 {
   MPI_Isend(&vs[1][0],1,scol,my_size-1,51,new_comm, &array_of_requests[index_of_comm++]);
   MPI_Irecv(&vs[Nx+1][0],1,scol,my_rank+1,51,new_comm, &array_of_requests[index_of_comm++]);

   MPI_Irecv(&vs[0][0],1,scol,my_size-1,51,new_comm, &array_of_requests[index_of_comm++] );
   MPI_Isend(&vs[Nx][0],1,scol,my_rank+1,51,new_comm, &array_of_requests[index_of_comm++]);
 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Isend(&vs[1][0],1,scol,my_rank-1,51,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Irecv(&vs[Nx+1][0],1,scol,my_rank+1,51,new_comm, &array_of_requests[index_of_comm++]);

  MPI_Irecv(&vs[0][0],1,scol,my_rank-1,51,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Isend(&vs[Nx][0],1,scol,my_rank+1,51,new_comm,  &array_of_requests[index_of_comm++]);
 }
 else if( my_rank == (my_size-1) )
 {
   MPI_Irecv(&vs[Nx+1][0],1,scol,0,51,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Isend(&vs[1][0],1,scol,my_rank-1,51,new_comm,  &array_of_requests[index_of_comm++]);

   MPI_Isend(&vs[Nx][0],1,scol,0,51,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Irecv(&vs[0][0],1,scol,my_rank-1,51,new_comm, &array_of_requests[index_of_comm++]);
 }
 MPI_Waitall(index_of_comm, array_of_requests, array_of_statuses);

}

void dens_mpi()
{
 int index_of_comm = 0; // index for the above array

 if(my_rank==0)
 {
   MPI_Isend(&dens[1][0],1,scol,my_size-1,52,new_comm, &array_of_requests[index_of_comm++]);
   MPI_Irecv(&dens[Nx+1][0],1,scol,my_rank+1,52,new_comm, &array_of_requests[index_of_comm++]);

   MPI_Irecv(&dens[0][0],1,scol,my_size-1,52,new_comm, &array_of_requests[index_of_comm++] );
   MPI_Isend(&dens[Nx][0],1,scol,my_rank+1,52,new_comm, &array_of_requests[index_of_comm++]);
 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Isend(&dens[1][0],1,scol,my_rank-1,52,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Irecv(&dens[Nx+1][0],1,scol,my_rank+1,52,new_comm, &array_of_requests[index_of_comm++]);

  MPI_Irecv(&dens[0][0],1,scol,my_rank-1,52,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Isend(&dens[Nx][0],1,scol,my_rank+1,52,new_comm,  &array_of_requests[index_of_comm++]);
 }
 else if( my_rank == (my_size-1) )
 {
   MPI_Irecv(&dens[Nx+1][0],1,scol,0,52,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Isend(&dens[1][0],1,scol,my_rank-1,52,new_comm,  &array_of_requests[index_of_comm++]);

   MPI_Isend(&dens[Nx][0],1,scol,0,52,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Irecv(&dens[0][0],1,scol,my_rank-1,52,new_comm, &array_of_requests[index_of_comm++]);
 }
 MPI_Waitall(index_of_comm, array_of_requests, array_of_statuses);

}


void send_posn()
{
 int index_of_comm = 0;

 if(my_rank==0)
 {
   MPI_Isend(&posn[1][0][0],1,fcol,my_size-1,54,new_comm, &array_of_requests[index_of_comm++]);
   MPI_Irecv(&posn[Nx+1][0][0],1,fcol,my_rank+1,54,new_comm, &array_of_requests[index_of_comm++]);

   MPI_Irecv(&posn[0][0][0],1,fcol,my_size-1,54,new_comm, &array_of_requests[index_of_comm++] );
   MPI_Isend(&posn[Nx][0][0],1,fcol,my_rank+1,54,new_comm, &array_of_requests[index_of_comm++]);
 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Isend(&posn[1][0][0],1,fcol,my_rank-1,54,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Irecv(&posn[Nx+1][0][0],1,fcol,my_rank+1,54,new_comm, &array_of_requests[index_of_comm++]);

  MPI_Irecv(&posn[0][0][0],1,fcol,my_rank-1,54,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Isend(&posn[Nx][0][0],1,fcol,my_rank+1,54,new_comm,  &array_of_requests[index_of_comm++]);
 }
 else if( my_rank == (my_size-1) )
 {
   MPI_Irecv(&posn[Nx+1][0][0],1,fcol,0,54,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Isend(&posn[1][0][0],1,fcol,my_rank-1,54,new_comm,  &array_of_requests[index_of_comm++]);

   MPI_Isend(&posn[Nx][0][0],1,fcol,0,54,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Irecv(&posn[0][0][0],1,fcol,my_rank-1,54,new_comm, &array_of_requests[index_of_comm++]);
 }

 MPI_Waitall(index_of_comm, array_of_requests, array_of_statuses);

 //MPI_Type_free(&fcol);

}

void send_force()
{
 int index_of_comm = 0;

 if(my_rank==0)
 {
   MPI_Isend(&force[1][0][0],1,fcol,my_size-1,53,new_comm, &array_of_requests[index_of_comm++]);
   MPI_Irecv(&force[Nx+3][0][0],1,fcol,my_rank+1,53,new_comm, &array_of_requests[index_of_comm++]);

   MPI_Irecv(&force[0][0][0],1,fcol,my_size-1,53,new_comm, &array_of_requests[index_of_comm++] );
   MPI_Isend(&force[Nx+2][0][0],1,fcol,my_rank+1,53,new_comm, &array_of_requests[index_of_comm++]);
 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Isend(&force[1][0][0],1,fcol,my_rank-1,53,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Irecv(&force[Nx+3][0][0],1,fcol,my_rank+1,53,new_comm, &array_of_requests[index_of_comm++]);

  MPI_Irecv(&force[0][0][0],1,fcol,my_rank-1,53,new_comm, &array_of_requests[index_of_comm++]);
  MPI_Isend(&force[Nx+2][0][0],1,fcol,my_rank+1,53,new_comm,  &array_of_requests[index_of_comm++]);
 }
 else if( my_rank == (my_size-1) )
 {
   MPI_Irecv(&force[Nx+3][0][0],1,fcol,0,53,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Isend(&force[1][0][0],1,fcol,my_rank-1,53,new_comm,  &array_of_requests[index_of_comm++]);

   MPI_Isend(&force[Nx+2][0][0],1,fcol,0,53,new_comm,  &array_of_requests[index_of_comm++]);
   MPI_Irecv(&force[0][0][0],1,fcol,my_rank-1,53,new_comm, &array_of_requests[index_of_comm++]);
 }

 MPI_Waitall(index_of_comm, array_of_requests, array_of_statuses);

 //MPI_Type_free(&fcol);

}

