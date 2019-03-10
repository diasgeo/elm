/////////////////////////
// merge.h
////////////////////////

void merge_vel()
{
int i, j, k, n;
int nosnaps;
double a1, a2,a3,a4,aa[2];
char string[50];
FILE *out;

for(nosnaps=0; nosnaps<NumSnap; nosnaps++)
{
   sprintf(string,"%s%d",output2,(nosnaps*isnap+snap_start) );
   if( (out = fopen( string,"w")) ==NULL )
   {
         printf("Error opening  file %s  \n",string);
         MPI_Finalize();
         exit(0); fclose(out);
   }

  for(j=0; j<my_size; j++)
  {
    sprintf(string,"%s_%d_%d",output2,j,nosnaps );
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
   sprintf(string,"%s_%d_%d",output2,j,nosnaps);
   remove(string);
  }

 fclose(out);

}

}

void merge_disp()
{
int i, j, k, n;
int nosnaps;
double a1, a2,a3,a4,aa[2];
char string[50];
FILE *out;

for(nosnaps=0; nosnaps<NumSnap; nosnaps++)
{
   sprintf(string,"%s%d",output6,(nosnaps*isnap+snap_start) );
   if( (out = fopen( string,"w")) ==NULL )
   {
         printf("Error opening  file %s  \n",string);
         MPI_Finalize();
         exit(0); fclose(out);
   }

  for(j=0; j<my_size; j++)
  {
    sprintf(string,"%s_%d_%d",output6,j,nosnaps );
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
   sprintf(string,"%s_%d_%d",output6,j,nosnaps);
   remove(string);
  }

 fclose(out);

}

}

