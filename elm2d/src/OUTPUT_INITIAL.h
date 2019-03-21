

void output_initial_geometry_sn()
{
 int i,j,m,n,k;
 double a1, a2;
 char string[50];
 FILE *out,*input[my_size];

   sprintf( string,"%s_%d",output0, my_rank);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening 1 file %s_%d  \n",output0,my_rank);
      MPI_Finalize();
      exit(0); fclose(out);
   }

   for(i=0; i<Nx; i++)
   {
   for(j=0; j<Ny; j++)
   {
      if(vp[j][i]!=-1974)
      {
      fprintf(out," %e %e\n", eqposn[j][i][0], eqposn[j][i][1]);
      }
      else
      {
      fprintf(out," %e %e\n", 0, 0);
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
  for(j=0; j<Ny; j++)
  {
  for(i=0; i<Nx; i++)
  {
    fscanf( input[n],"%lf %lf\n", &a1, &a2);
    fprintf( out,"%e %e\n", a1, a2);
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

/*
void output_parameters()
{
 char string[50];
 FILE *out;

if(my_rank==0)
{
   printf( string,"%s",output5);
   if(( out = fopen( string,"w")) ==NULL )
   {
      printf("Error opening file %s \n",output5);
      MPI_Finalize();
      exit(0); fclose(out);
   }
   
   fprintf(out," Max time \t\t%d  \n",Max_Time);
   
   fprintf(out," \t\t %e \n",bound);
   fprintf(out," \t\t %e \n",lambda);
   fprintf(out," \t\t %e \n",width);

   fprintf(out," \t\t %e  \n",dt);
   fprintf(out," \t\t %e  \n",density);
   fprintf(out," \t\t %e  \n",velp);
   fprintf(out," \t\t %e \n",Nx);
   fprintf(out," \t\t %e \n",Ny);
   fprintf(out," \t\t %e  \n",dx);

   fprintf(out," \t\t %e \n",input_source);
   fprintf(out," \t\t %s \n",input1);
   fprintf(out," \t\t %e \n",NumSource);
   fprintf(out," \t\t %e \n",sdir);
   fprintf(out," \t\t %e \n",sscale);
   fprintf(out," \t\t %s \n",input2);

   fprintf(out," \t\t %e \n",NumGeo);
   fprintf(out," \t\t %s \n",input0);
   fprintf(out," \t\t %e \n",NumSnap);
   fprintf(out," \t\t %e \n",isnap);
   fprintf(out," \t\t %e \n",snap_start);

   fprintf(out," \t\t %s \n",output0);
   fprintf(out," \t\t %s \n",output1);
   fprintf(out," \t\t %s \n",output2);
   fprintf(out," \t\t %s \n",output3);
   fprintf(out," \t\t %s \n",output4);
   fprintf(out," \t\t %s \n",output5);

}

}

*/
