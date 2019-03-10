

void output_initial_geometry_sn()
{
 int i,j,n,k;
 double a1,a2,a3,aa[3];
 char string[50];
 FILE *out,*input[my_size];

   sprintf( string,"%s_%d",output0, my_rank);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening 1 file %s_%d  \n",output0,my_rank);
      MPI_Finalize();
      exit(0); fclose(out);
   }
   

   for(j=0; j<Nx; j++)
   {
   for(k=0; k<Nz; k++)
   {
   for(i=0; i<Ny; i++)
   {
      if(vp[i][j][k]!=-1974)
      {
      fprintf(out," %e %e %e\n", eqposn[i][j][k][0], eqposn[i][j][k][1],eqposn[i][j][k][2]);
      }
      else
      {
      fprintf(out," %e %e %e\n", 0.0, 0.0,0.0);
      }
   }
   }
   }
   fclose(out);
   MPI_Barrier(new_comm);

if(my_rank==0)
{

   sprintf(string,"%s",output0);

   if( (out = fopen( string,"w")) ==NULL )
   {
         printf("Error opening  file %s  \n",string);
         MPI_Finalize();
         exit(0); fclose(out);
   }

  for(j=0; j<my_size; j++)
  {
    sprintf(string,"%s_%d",output0,j);
    if((input[j] = fopen(string,"r")) ==NULL )
    {
      printf("Error 3 opening file %s \n",string);
      MPI_Finalize(); exit(0);
    }
  }
 
 
  for(n=0; n<my_size; n++)
  {
  for(i=0; i<Nx; i++)
  {
  for(j=0; j<Ny; j++)
  {
  for(k=0; k<Nz; k++)
  {
    fscanf( input[n],"%lf %lf %lf\n", &a1, &a2 ,&a3);
    aa[0]=a1; aa[1]=a2; aa[2]=a3;
    fwrite(&aa, sizeof(double), 3, out);
    //fprintf( out,"%e %e %e\n", a1, a2, a3);
  }
  }
  }
  }
 
 // close files
 for (j = 0; j < my_size; j++)
 {
   fclose(input[j]);
   sprintf(string,"%s_%d",output0,j);
   remove(string);
 }
 fclose(out);
}
MPI_Barrier(new_comm);
 
}


