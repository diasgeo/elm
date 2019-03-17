
///////////////////////////////////
// snapshots
//////////////////////////////////

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
   for(i=0; i<Nx; i++)
   {
   for(j=0; j<Ny; j++)
   {
     fprintf(out,"%e %e\n",up[i][j][0],up[i][j][1]); 
     //fprintf(out,"%e %e\n",kspring[i][j][0],kspring[i][j][1]); 
     //fprintf(out,"%e %e\n",r0[i][j][2],r0[i][j][3]); 
    // fprintf(out,"%e %e %e\n",a,b,c);
   }
   }
   fclose(out);
   //   MPI_Barrier(new_comm);

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
      sprintf(string,"%s%d",output5,(nosnaps*isnap+snap_start)); //nosnaps
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

  for(n = 0; n < my_size; n++)
  {
  for(i = 0; i < Ny; i++)
  {
  for(j = 0; j < Nx; j++)
  {
    fscanf( input[n],"%lf %lf\n", &a1, &a2);
   // fprintf( out,"%e %e\n", a1, a2);
    aa[0]=a1; aa[1]=a2;
    fwrite(&aa, sizeof(double), 2, out);
  }
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


