  // Locates the node from the coordinate
int locate_node(int coord)
{
 int i,node=0;

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
  int j;

  char file_name[50];
  char  string[50];
  FILE *in;

   sprintf(string,"%s",input0);
   if((in=fopen(string,"r"))==NULL)
   {
      printf("Error 4006 opening file %s \n", string);
      fclose(in);
      MPI_Finalize();
      exit(1);
   }

  for(j=0; j<NumGeo; j++)
  {
    fscanf(in,"%d  %d  %d\n",&geo[j][1], &geo[j][0],&geo[j][2]);
    phone[j][0]=-1;
    phone[j][1]=-1; 
    phone[j][2]=-1;
  }
  fclose(in);

  for(j=0; j<NumGeo; j++)
  {
    if(locate_node(geo[j][1])==my_rank)
    {
      phone[j][0]=geo[j][0];
      phone[j][1]=geo[j][1]%Nx;
      phone[j][2]=geo[j][2];
    }
  }

   for(j=0; j<NumGeo; j++)
   {
     if(locate_node(geo[j][1])==my_rank)
     {
      sprintf(file_name,"%s%d_%d_%d",output4,geo[j][1],geo[j][0],geo[j][2]);
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
  int jp,ip,kp;
  double a,b,c;
  j=0;

  for(i=0; i<NumGeo; i++)
  {
    ip=phone[i][0]; jp=phone[i][1]; kp=phone[i][2];
    if(locate_node(geo[i][1])==my_rank && phone[i][1]!=-1)
    {
      a=posn[ip][jp][kp][0]-eqposn[ip][jp][kp][0];
      b=posn[ip][jp][kp][1]-eqposn[ip][jp][kp][1];
      c=posn[ip][jp][kp][2]-eqposn[ip][jp][kp][2];

      fprintf(out_trace[i],"%e %e %e %e %e %e\n",a,b,c,
                        upx[ip][jp][kp],upy[ip][jp][kp],upz[ip][jp][kp]);

   /*   fprintf(out_trace[i],"%e %e %e\n",upx[ip][jp][kp],
                                         upy[ip][jp][kp],upz[ip][jp][kp]);*/

    }
  }

}  // End of Routine


// Closing files
void close_trace()
{
  int i;

  for(i=0; i<NumGeo; i++)
  {
    if(locate_node(geo[i][1])==my_rank)
    {
      fclose(out_trace[i]);
    }
  }
}     // End of routine






