/////////////////////////
// merge.h
////////////////////////

void merge_disp()
{
int i, j, k, n;
int nosnaps;
double a1,a2,a3,aa[3];
char string[50];
FILE *out;

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
  for(i=0; i<Nx*Ny*Nz; i++)
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


void merge_disp_LR()
{
int i, j, k, n;
int nosnaps;
double a1,a2,a3,aa[3];
char string[50];
FILE *out;

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
  for(i=0; i<Nx*Ny*Nz/(LR*LR*LR); i++)
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

void merge_vel_LR()
{
int i, j, k, n;
int nosnaps;
double a1,a2,a3,aa[3];
char string[50];
FILE *out;

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
  for(i=0; i<Nx*Ny*Nz/(LR*LR*LR); i++)
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
