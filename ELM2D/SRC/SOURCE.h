
// Source Routine

void source_routine()
{
 int i,j;
 FILE *in;
 char  string[50];

   psource=v_alloc1d(Max_Time);

   sprintf( string,"%s",input2);
   if(( in= fopen(string,"r")) ==NULL)
   {
      printf("Error opening file %s \n", string);
      MPI_Finalize();
      fclose(in);
      exit(1);
   }
  for(i=0; i<Max_Time; i++)
  {
    fscanf(in,"%lf \n",&psource[i]);
  }
  fclose(in);


   // Read in the x and y positions of sources:
   sprintf( string,"%s",input1);
   if(( in= fopen(string,"r")) ==NULL)
   {
      printf("Error opening file %s \n", string);
      MPI_Finalize();
      fclose(in);
      exit(1);
   }
   for (i = 0; i < NumSource; i++)
   {
      source[0][i]=source[1][i]=0;
      fscanf( in,"%d %d\n", &source[0][i], &source[1][i]);
   }
   fclose(in);


}
