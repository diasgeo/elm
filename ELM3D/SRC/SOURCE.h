
// Source Routine

void source_routine()
{
 int i;
 FILE *in;
 char string[50];

 psource=v_alloc1d(Max_Time);
 //psource2=v_alloc1d(Max_Time);
 //psource3=v_alloc1d(Max_Time);


// Calculating source
 if(input_source==0)
 {
  for(i=0; i<Max_Time; i++)
  {
   psource[i]=exp( -0.5*(2*center_freq*dt*i)*(2*center_freq*dt*i))*cos(2*3.141*dt*center_freq*i);
  }
 }
 else if(input_source==1)
 {
   sprintf( string,"%s",input3);
   if(( in= fopen(string,"r")) ==NULL)
   {
      printf("Error opening file %s \n",string);
      MPI_Finalize();
      fclose(in);
      exit(1);
   }
  for(i=0; i<Max_Time; i++)
  {
    fscanf(in,"%lf\n",&psource[i]);
    //fscanf(in,"%lf %lf %lf\n",&psource[i],&psource2[i],&psource3[i]);
  }
  fclose(in);
 }

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
      source[0][i]=source[1][i]=source[2][i]=0;
      fscanf( in,"%d %d %d\n", &source[0][i], &source[1][i], &source[2][i]);
   }
   fclose(in);

}


