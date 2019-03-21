
///////////////////////////////////
// snapshots
//////////////////////////////////
void snap_vel()
{
int i, j, n, m;
double p,p1;
FILE *out;
char  string[50];

   sprintf( string,"%s_%d_%d",output2,my_rank,NumSnaps);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s_%d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }

// data output on each node:
   for(j=0; j<Nx; j++)
   { 
   for(i=0; i<Ny; i++)
   {
      fprintf(out,"%e %e\n",upx[i][j],upy[i][j]); 
      //fprintf(out,"%e %e\n",force[i][j][0],force[i][j][1]);
      //fprintf(out,"%e %e\n",vp[i][j],vs[i][j]);
   }
   }
   fclose(out);
   MPI_Barrier(new_comm);

}


///////////////////////////////////
// snapshots
//////////////////////////////////
void snap_disp()
{
int i, j, n, m;
double press;
FILE *out;
char  string[50];

   sprintf( string,"%s_%d_%d",output6,my_rank,NumSnaps);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s_%d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }

// data output on each node:
   for(j=0; j<Nx; j++)
   { 
   for(i=0; i<Ny; i++)
   {
     fprintf(out,"%e %e\n",disp[i][j][0],disp[i][j][1]);       
     //fprintf(out,"%e %e\n",vp[i][j],vs[i][j]);     
   }
   }
   fclose(out);
   MPI_Barrier(new_comm);

}


