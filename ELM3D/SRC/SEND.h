
void send_dens_vp(double arrayl[Ny][Nz],double arrayr[Ny][Nz],int property)
{
 int i,k;
 int bcol[1],d[1];
 double slarray[Ny][Nz],srarray[Ny][Nz];
 MPI_Datatype col;
 MPI_Status status;

 bcol[0]=Ny*Nz;   d[0]=0;
 MPI_Type_indexed(1,bcol,d,MPI_DOUBLE,&col);
 MPI_Type_commit(&col);

  for(i=0; i<Ny; i++)
  {
  for(k=0; k<Nz; k++)
  {
    if(property==1)
    {
      slarray[i][k]=vp[i][0][k];
      srarray[i][k]=vp[i][Nx-1][k];
    }
    else if(property==2)
    {
      slarray[i][k]=vs[i][0][k];;
      srarray[i][k]=vs[i][Nx-1][k];
    }
    else if(property==3)
    {
      slarray[i][k]=dens[i][0][k];;
      srarray[i][k]=dens[i][Nx-1][k];
    }
    arrayl[i][k]=arrayr[i][k]=0;
  }
  }

 MPI_Barrier(new_comm);
 if(my_rank==0)
 {
   MPI_Send(slarray,1,col,my_size-1,50,new_comm);
   MPI_Recv(arrayr,1,col,my_rank+1,50,new_comm,&status);

   MPI_Recv(arrayl,1,col,my_size-1,50,new_comm,&status);
   MPI_Send(srarray,1,col,my_rank+1,50,new_comm);

 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Send(slarray,1,col,my_rank-1,50,new_comm);
  MPI_Recv(arrayr,1,col,my_rank+1,50,new_comm,&status);

  MPI_Recv(arrayl,1,col,my_rank-1,50,new_comm,&status);
  MPI_Send(srarray,1,col,my_rank+1,50,new_comm);

 }
 else if( my_rank == (my_size-1) )
 {
   MPI_Recv(arrayr,1,col,0,50,new_comm,&status);
   MPI_Send(slarray,1,col,my_rank-1,50,new_comm);

   MPI_Send(srarray,1,col,0,50,new_comm);
   MPI_Recv(arrayl,1,col,my_rank-1,50,new_comm,&status);

 }
 MPI_Barrier(new_comm);

 MPI_Type_free(&col);



}


void send_posn()
{
 int i,k;
 int bcol[1],d[1];
 MPI_Datatype col;
 MPI_Status status;

 bcol[0]=Ny*Nz*3;   d[0]=0;
 MPI_Type_indexed(1,bcol,d,MPI_DOUBLE,&col);
 MPI_Type_commit(&col);

  for(i=0; i<Ny; i++)
  { 
  for(k=0; k<Nz; k++)
  {
     temp_left_p[i][k][0]=posn[i][0][k][0];
     temp_left_p[i][k][1]=posn[i][0][k][1];
     temp_left_p[i][k][2]=posn[i][0][k][2];

     temp_right_p[i][k][0]=posn[i][Nx-1][k][0];
     temp_right_p[i][k][1]=posn[i][Nx-1][k][1];
     temp_right_p[i][k][2]=posn[i][Nx-1][k][2];

     left_p[i][k][0]=0; right_p[i][k][0]=0;
     left_p[i][k][1]=0; right_p[i][k][1]=0;
     left_p[i][k][2]=0; right_p[i][k][2]=0;
  }
  }

 MPI_Barrier(new_comm);
 if(my_rank==0)
 {
   MPI_Send(temp_left_p,1,col,my_size-1,50,new_comm);
   MPI_Recv(right_p,1,col,my_rank+1,50,new_comm,&status);

   MPI_Recv(left_p,1,col,my_size-1,50,new_comm,&status);
   MPI_Send(temp_right_p,1,col,my_rank+1,50,new_comm);

 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Send(temp_left_p,1,col,my_rank-1,50,new_comm);
  MPI_Recv(right_p,1,col,my_rank+1,50,new_comm,&status);

  MPI_Recv(left_p,1,col,my_rank-1,50,new_comm,&status);
  MPI_Send(temp_right_p,1,col,my_rank+1,50,new_comm);

 }
 else if( my_rank == (my_size-1) )
 {
   MPI_Recv(right_p,1,col,0,50,new_comm,&status);
   MPI_Send(temp_left_p,1,col,my_rank-1,50,new_comm);

   MPI_Send(temp_right_p,1,col,0,50,new_comm);
   MPI_Recv(left_p,1,col,my_rank-1,50,new_comm,&status);

 }
 MPI_Barrier(new_comm);

 MPI_Type_free(&col);

}


void send_forces()
{
 int i,k;
 int bcol[1],d[1];
 MPI_Datatype col;
 MPI_Status status;

 bcol[0]=Ny*Nz*3;   d[0]=0;
 MPI_Type_indexed(1,bcol,d,MPI_DOUBLE,&col);
 MPI_Type_commit(&col);


  for(i=0; i<Ny; i++)
  {
  for(k=0; k<Nz; k++)
  {
     left_f[i][k][0]=0; right_f[i][k][0]=0;
     left_f[i][k][1]=0; right_f[i][k][1]=0;
     left_f[i][k][2]=0; right_f[i][k][2]=0;
  }
  }

 MPI_Barrier(new_comm);
 if(my_rank==0)
 {
   MPI_Send(temp_left_f,1,col,my_size-1,50,new_comm);
   MPI_Recv(right_f,1,col,my_rank+1,50,new_comm,&status);

   MPI_Recv(left_f,1,col,my_size-1,50,new_comm,&status);
   MPI_Send(temp_right_f,1,col,my_rank+1,50,new_comm);

 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Send(temp_left_f,1,col,my_rank-1,50,new_comm);
  MPI_Recv(right_f,1,col,my_rank+1,50,new_comm,&status);

  MPI_Recv(left_f,1,col,my_rank-1,50,new_comm,&status);
  MPI_Send(temp_right_f,1,col,my_rank+1,50,new_comm);

 }
 else if( my_rank == (my_size-1) )
 {
   MPI_Recv(right_f,1,col,0,50,new_comm,&status);
   MPI_Send(temp_left_f,1,col,my_rank-1,50,new_comm);

   MPI_Send(temp_right_f,1,col,0,50,new_comm);
   MPI_Recv(left_f,1,col,my_rank-1,50,new_comm,&status);
 }
 MPI_Barrier(new_comm);

 MPI_Type_free(&col);

}


