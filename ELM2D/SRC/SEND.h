
void send_dens_vp(double arrayl[Ny],double arrayr[Ny],int property)
{
 int i,j,k;
 int bcol[1],d[1];
 double slarray[Ny],srarray[Ny];
 MPI_Datatype col;
 MPI_Status status;

 bcol[0]=Ny;   d[0]=0;
 MPI_Type_indexed(1,bcol,d,MPI_DOUBLE,&col);
 MPI_Type_commit(&col);

  for(i=0; i<Ny; i++)
  {
    if(property==1)
    {
      slarray[i]=vp[i][0];
      srarray[i]=vp[i][Nx-1];
    }
    else if(property==2)
    {
      slarray[i]=vs[i][0];
      srarray[i]=vs[i][Nx-1];
    }
    else if(property==3)
    {
      slarray[i]=dens[i][0];
      srarray[i]=dens[i][Nx-1];
    }
  /*  else if(property==3)
    {
      slarray[i]=mass[i][0];
      srarray[i]=mass[i][Nx-1];
    }*/
    arrayl[i]=arrayr[i]=0;
  }

 MPI_Barrier(new_comm);
 if(my_rank==0)
 {
   //MPI_Send(s,1,col,my_size-1,50,new_comm);
   MPI_Recv(arrayr,1,col,my_rank+1,50,new_comm,&status);

   //MPI_Recv(array,1,col,my_size-1,50,new_comm,&status);
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
 //  MPI_Recv(array,1,col,0,50,new_comm,&status);
   MPI_Send(slarray,1,col,my_rank-1,50,new_comm);

 //  MPI_Send(send_array,1,col,0,50,new_comm);
   MPI_Recv(arrayl,1,col,my_rank-1,50,new_comm,&status);

 }
 MPI_Barrier(new_comm);

 MPI_Type_free(&col);



}


void send_posn()
{
 int i,j,k;
 int bcol[1],d[1];
 MPI_Datatype col;
 MPI_Status status;

 bcol[0]=Ny*2;   d[0]=0;
 MPI_Type_indexed(1,bcol,d,MPI_DOUBLE,&col);
 MPI_Type_commit(&col);


  for(i=0; i<Ny; i++)
  {
     temp_left_p[i][0]=posn[i][0][0];
     temp_left_p[i][1]=posn[i][0][1];

     temp_right_p[i][0]=posn[i][Nx-1][0];
     temp_right_p[i][1]=posn[i][Nx-1][1];

     left_p[i][0]=0; right_p[i][0]=0;
     left_p[i][1]=0; right_p[i][1]=0;
  }

 MPI_Barrier(new_comm);
 if(my_rank==0)
 {
   //MPI_Send(s,1,col,my_size-1,50,new_comm);
   MPI_Recv(right_p,1,col,my_rank+1,50,new_comm,&status);

   //MPI_Recv(array,1,col,my_size-1,50,new_comm,&status);
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
 //  MPI_Recv(array,1,col,0,50,new_comm,&status);
   MPI_Send(temp_left_p,1,col,my_rank-1,50,new_comm);

 //  MPI_Send(send_array,1,col,0,50,new_comm);
   MPI_Recv(left_p,1,col,my_rank-1,50,new_comm,&status);

 }
 MPI_Barrier(new_comm);

 MPI_Type_free(&col);

}


void send_forces()
{
 int i,j,k;
 int bcol[1],d[1];
 MPI_Datatype col;
 MPI_Status status;

 bcol[0]=Ny*2;   d[0]=0;
 MPI_Type_indexed(1,bcol,d,MPI_DOUBLE,&col);
 MPI_Type_commit(&col);


  for(i=0; i<Ny; i++)
  {
     left_f[i][0]=0; right_f[i][0]=0;
     left_f[i][1]=0; right_f[i][1]=0;
  }

 MPI_Barrier(new_comm);
 if(my_rank==0)
 {
   //MPI_Send(s,1,col,my_size-1,50,new_comm);
   MPI_Recv(right_f,1,col,my_rank+1,50,new_comm,&status);

   //MPI_Recv(array,1,col,my_size-1,50,new_comm,&status);
   MPI_Send(temp_forcer,1,col,my_rank+1,50,new_comm);

 }
 else if( my_rank>0 && my_rank< (my_size-1) )
 {
  MPI_Send(temp_forcel,1,col,my_rank-1,50,new_comm);
  MPI_Recv(right_f,1,col,my_rank+1,50,new_comm,&status);

  MPI_Recv(left_f,1,col,my_rank-1,50,new_comm,&status);
  MPI_Send(temp_forcer,1,col,my_rank+1,50,new_comm);

 }
 else if( my_rank == (my_size-1) )
 {
 //  MPI_Recv(array,1,col,0,50,new_comm,&status);
   MPI_Send(temp_forcel,1,col,my_rank-1,50,new_comm);

 //  MPI_Send(send_array,1,col,0,50,new_comm);
   MPI_Recv(left_f,1,col,my_rank-1,50,new_comm,&status);

 }
 MPI_Barrier(new_comm);

 MPI_Type_free(&col);

}

