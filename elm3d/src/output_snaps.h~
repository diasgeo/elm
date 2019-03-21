
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
      printf("Error opening file %s_%d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }
  
// data output on each node:
   for(i=0; i<Nx; i=i+LR)
   {
   for(k=0; k<Nz; k=k+LR)
   {
   for(j=0; j<Ny; j=j+LR)
   {
      a=posn[i + 1][j][k][0]-eqposn[i][j][k][0];
      b=posn[i + 1][j][k][1]-eqposn[i][j][k][1];
      c=posn[i + 1][j][k][2]-eqposn[i][j][k][2];

     // a=vp[i + 1][j][k];
      //b=vs[i + 1][j][k];
     // c=dens[i + 1][j][k];

       fprintf(out,"%e %e %e\n",a,b,c);
    }
    }
    }
   fclose(out);

}

///////////////////////////////////
// snapshots
//////////////////////////////////
void snap_vel()
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
   for(i=0; i<Nx; i=i+LR)
   {
   for(k=0; k<Nz; k=k+LR)
   {
   for(j=0; j<Ny; j=j+LR)
   {
     fprintf(out,"%e %e %e\n",up[i][j][k][0],up[i][j][k][1],up[i][j][k][2]); 
    // fprintf(out,"%e %e %e\n",a,b,c);
   }
   }
   }
   fclose(out);
   //   MPI_Barrier(new_comm);

}

void merge_disp()
{
int i, j, k, n;
int nosnaps;
double a1,a2,a3,aa[3];
char string[50];
FILE *out,*input[my_size];

for(nosnaps=0; nosnaps<NumSnap; nosnaps++)
{
   sprintf(string,"%s%d",output2,nosnaps);
   if( (out = fopen( string,"w")) ==NULL )
   {
         printf("Error opening  file %s  \n",string);
         MPI_Finalize();
         exit(0); fclose(out);
   }

  for(j=0; j<my_size; j++)
  {
    sprintf(string,"%s_%d_%d",output2,j,nosnaps);
    if((input[j] = fopen(string,"r")) ==NULL )
    {
      printf("Error 3 opening file %s \n",string);
      MPI_Finalize(); exit(0);
    }
  }

  for(n=0; n<my_size; n++)
  {
  for(i=0; i<lr_count; i++)
  {
    fscanf(input[n],"%lf %lf %lf \n", &a1, &a2 ,&a3);
    aa[0]=a1; aa[1]=a2; aa[2]=a3;
    fwrite(&aa, sizeof(double), 3, out);
    //fprintf(out,"%e %e %e\n",a1,a2,a3);
  }
  }

 // close files
  for (j = 0; j < my_size; j++)
  {
   fclose(input[j]);
   sprintf(string,"%s_%d_%d",output2,j,nosnaps);
   remove(string);
  }

 fclose(out);

}

}

void merge_vel()
{
  int i, j, k, n;
  int nosnaps;
  double a1,a2,a3,aa[3];
  char string[50];
  FILE *out,*input[my_size];

    for(nosnaps=0; nosnaps<NumSnap; nosnaps++)
    {
      sprintf(string,"%s%d",output5,nosnaps);
      if( (out = fopen( string,"w")) ==NULL )
        {
          printf("Error opening  file %s  \n",string);
          MPI_Finalize();
          exit(0); fclose(out);
      }

      for(j=0; j<my_size; j++)
      {
          sprintf(string,"%s_%d_%d",output5,j,nosnaps);
          if((input[j] = fopen(string,"r")) ==NULL )
            {
              printf("Error 3 opening file %s \n",string);
              MPI_Finalize(); exit(0);
            }
      }

      for(n=0; n<my_size; n++)
      {
          for(i=0; i<lr_count; i++)
          {
              fscanf(input[n],"%lf %lf %lf \n", &a1, &a2 ,&a3);
              aa[0]=a1; aa[1]=a2; aa[2]=a3;
              fwrite(&aa, sizeof(double), 3, out);
              //fprintf(out,"%e %e %e\n",a1,a2,a3);
           }
       }

      // close files
      for (j = 0; j < my_size; j++)
      {
          fclose(input[j]);
          sprintf(string,"%s_%d_%d",output5,j,nosnaps);
          remove(string);
      }

      fclose(out);

    }

}



void surface_snap()
{
int i, j, k,n;
double a,b,c;
FILE *out;
char  string[50];
double a1,a2,a3,aa[3];

   sprintf( string,"%s_%d_%d",output6,my_rank,NumSnapsS);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s on %d  \n",string,my_rank);
      MPI_Finalize();
      exit(0);
      fclose(out);
   }


// data output on each node:
   for(i=0; i<Nx; i++)
   {
   for(j=0; j<Ny; j++)
   {
   for(k=0; k<Nz; k++)
   {
      a=posn[i + 1][j][k][0]-eqposn[i][j][k][0];
      b=posn[i + 1][j][k][1]-eqposn[i][j][k][1];
      c=posn[i + 1][j][k][2]-eqposn[i][j][k][2];

    if(k<(Nz-1))
    {
      if(vp[i+1][j][k+1]==-1974.0 && vp[i+1][j][k]!=-1974.0)
      {
       fprintf(out,"%e %e %e %e %e %e \n",a,b,c,up[i][j][k][0],up[i][j][k][1],up[i][j][k][2]);
      }
    }
    else
    {
      if(vp[i+1][j][k]!=-1974.0)
      {
       fprintf(out,"%e %e %e %e %e %e \n",a,b,c,up[i][j][k][0],up[i][j][k][1],up[i][j][k][2]);
      }
    }

   }
   }
   }
   fclose(out);
   //MPI_Barrier(new_comm);

}


void merge_surface()
{
int i, j, k, n;
int nosnaps;
double a1,a2,a3,a4,a5,a6,aa[6];
char string[50];
FILE *out,*input[my_size];

for(nosnaps=0; nosnaps<NumSnapS; nosnaps++)
{
   sprintf(string,"%s%d",output6,nosnaps);
   if( (out = fopen( string,"w")) ==NULL )
   {
         printf("Error opening  file %s  \n",string);
         MPI_Finalize();
         exit(0); fclose(out);
   }

  for(j=0; j<my_size; j++)
  {
    sprintf(string,"%s_%d_%d",output6,j,nosnaps);
    if((input[j] = fopen(string,"r")) ==NULL )
    {
      printf("Error 77 opening file %s \n",string);
      MPI_Finalize(); exit(0);
    }
  }

  for(n=0; n<my_size; n++)
  {
  for(i=0; i<Nx*Ny; i++)
  {
    fscanf(input[n],"%lf %lf %lf %lf %lf %lf\n", &a1,&a2,&a3,&a4,&a5,&a6);
    aa[0]=a1; aa[1]=a2; aa[2]=a3;aa[3]=a4; aa[4]=a5; aa[5]=a6;
    fwrite(&aa, sizeof(double), 6, out);
    //fprintf(out,"%e %e %e\n",a1,a2,a3);
  }
  }

 // close files
  for (j = 0; j < my_size; j++)
  {
   fclose(input[j]);
   sprintf(string,"%s_%d_%d",output6,j,nosnaps);
   remove(string);
  }

 fclose(out);

}

}










