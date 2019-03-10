
///////////////////////////////////
// snapshots
//////////////////////////////////
void snap_disp()
{
int i, j, k;
double a,b,c;
FILE *out;
char  string[50];

   sprintf( string,"%s_%d_%d",output2,my_rank,NumSnaps);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s on %d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }

// data output on each node:
   for(j=0; j<Nx; j++)
   {
   for(k=0; k<Nz; k++)
   {
   for(i=0; i<Ny; i++)
   {
      a=posn[i][j][k][0]-eqposn[i][j][k][0];
      b=posn[i][j][k][1]-eqposn[i][j][k][1];
      c=posn[i][j][k][2]-eqposn[i][j][k][2];
     // a=vp[i][j][k];
     fprintf(out,"%e %e %e\n",a,b,c);
     //fprintf(out,"%e %e %e\n",a,b,c);
     //fprintf(out,"%e %e %e\n",upx[i][j][k],upy[i][j][k],upz[i][j][k]);
   }
   }
   }
   fclose(out);
   MPI_Barrier(new_comm);

}


///////////////////////////////////
// snapshots
//////////////////////////////////
void snap_disp_LR()
{
int i, j, k;
double a,b,c;
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
   for(j=0; j<Nx; j=j+LR)
   {
   for(k=0; k<Nz; k=k+LR)
   {
   for(i=0; i<Ny; i=i+LR)
   {
      a=posn[i][j][k][0]-eqposn[i][j][k][0];
      b=posn[i][j][k][1]-eqposn[i][j][k][1];
      c=posn[i][j][k][2]-eqposn[i][j][k][2];
      //a=vp[i][j][k];b=vs[i][j][k];c=dens[i][j][k];
     fprintf(out,"%e %e %e\n",a,b,c);
   }
   }
   }
   fclose(out);
   MPI_Barrier(new_comm);

}

///////////////////////////////////
// snapshots
//////////////////////////////////
void snap_vel_LR()
{
int i, j, k;
double a,b,c;
FILE *out;
char  string[50];

   sprintf( string,"%s_%d_%d",output5,my_rank,NumSnaps);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s_%d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }

// data output on each node:
   for(j=0; j<Nx; j=j+LR)
   {
   for(k=0; k<Nz; k=k+LR)
   {
   for(i=0; i<Ny; i=i+LR)
   {
     fprintf(out,"%e %e %e\n",upx[i][j][k],upy[i][j][k],upz[i][j][k]);
   }
   }
   }
   fclose(out);
   MPI_Barrier(new_comm);

}

void snap_surface()
{
int i, j, k,n;
double a,b,c;
FILE *out;
char  string[50];
double a1,a2,a3,aa[3];

   sprintf( string,"%s_%d",output6,my_rank);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s on %d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }

// data output on each node:
   for(j=0; j<Nx; j++)
   {
   for(i=0; i<Ny; i++)
   {
   for(k=0; k<Nz; k++)
   {
      a=posn[i][j][k][0]-eqposn[i][j][k][0];
      b=posn[i][j][k][1]-eqposn[i][j][k][1];
      c=posn[i][j][k][2]-eqposn[i][j][k][2];
    if(k<(Nz-1))
    {
      if(vp[i][j][k+1]==-1974.0 && vp[i][j][k]!=-1974.0)
      {
       fprintf(out,"%e %e %e \n",a,b,c);
                        //upx[i][j][k],upy[i][j][k],upz[i][j][k]);
      }
    }
    else
    {
      if(vp[i][j][k]!=-1974.0)
      {
       fprintf(out,"%e %e %e \n",a,b,c);
                        //upx[i][j][k],upy[i][j][k],upz[i][j][k]);
      }
    }
   }
   }
   }
   fclose(out);
   MPI_Barrier(new_comm);
/////////////////////////////////////////////////////
if(my_rank==0)
{
   sprintf(string,"%s",output6);
   if( (out = fopen( string,"w")) ==NULL )
   {
         printf("Error opening  file %s  \n",string);
         MPI_Finalize();
         exit(0); fclose(out);
   }

  for(j=0; j<my_size; j++)
  {
    sprintf(string,"%s_%d",output6,j);
    if((input[j] = fopen(string,"r")) ==NULL )
    {
      printf("Error 3 opening file %s \n",string);
      MPI_Finalize(); exit(0);
    }
  }

  for(n=0; n<my_size; n++)
  {
  for(i=0; i<Nx*Ny; i++)
  {
    fscanf(input[n],"%lf %lf %lf \n", &a1, &a2 ,&a3);
    //aa[0]=a1; aa[1]=a2; aa[2]=a3;
    //fwrite(&aa, sizeof(double), 3, out);
    fprintf(out,"%e %e %e  \n",a1,a2,a3);
  }
  }

 // close files
  for (j = 0; j < my_size; j++)
  {
   fclose(input[j]);
   sprintf(string,"%s_%d",output6,j);
   remove(string);
  }

 fclose(out);
}
/////////////////////////////////////////////////////////
}

