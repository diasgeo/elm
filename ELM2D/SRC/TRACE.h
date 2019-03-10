  // Locates the node from the coordinate
int locate_node(int coord)
{
 int i,node;

 for(i=0; i<my_size; i++)
 {
   if( coord < ((Nx)*i+Nx) && coord >= (Nx*i) )
   {
     node=i;
   }
 }
 return node;

}

// Open trace files and locate them correctly
void trace_files()
{
  int i,j;

  char file_name[50];
  char  string[50];
  FILE *in;

   sprintf( string,"%s",input0);
   if(( in= fopen(string,"r")) ==NULL)
   {
      printf("Error 4006 opening file %s \n", string);
      MPI_Finalize();
      fclose(in);
      exit(1);
   }

  for(j=0; j<NumGeo; j++)
  {
    fscanf(in," %d  %d\n",&geo[j][0], &geo[j][1]);
    phone[j][0]=-1;
    phone[j][1]=-1;
  }
  fclose(in);

  for(j=0; j<NumGeo; j++)
  {
    if(locate_node(geo[j][0])==my_rank)
    {
      phone[j][0]=geo[j][0]%Nx;
      phone[j][1]=geo[j][1];
    }
  }

   for(j=0; j < NumGeo; j++)
   {
     if(locate_node(geo[j][0])==my_rank)
     {
      sprintf(file_name,"%s%d_%d",output4,geo[j][0],geo[j][1]);
      if((out_trace[j]= fopen(file_name,"w")) ==NULL )
      {
         printf("Error opening trace file on node %d\n",my_rank);
         MPI_Finalize();
         exit(0);
      }
     }
   }


}     // End of Routine

// Writing the correct trace position to correct file

void write_trace()
{
  int i,j;
  int jp,ip,p;
  double pore,porey;
  j=0;

  for(i=0; i<NumGeo; i++)
  {
    ip=phone[i][1]; jp=phone[i][0];
    pore=0;
    if(locate_node(geo[i][0])==my_rank && phone[i][0]!=-1)
    {
    
fprintf(out_trace[i],"%e %e\n",upx[ip][jp],upy[ip][jp]);

    }
  }

}  // End of Routine


// Closing files
void close_trace()
{
  int i,j;

  for(i=0; i<NumGeo; i++)
  {
    if(locate_node(geo[i][0])==my_rank)
    {
      fclose(out_trace[i]);
    }
  }
}     // End of routine






