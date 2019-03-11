

// Open trace files and locate them correctly
void trace_files()
{
  int i,j,k,l;
  
  char file_name[50];
  char  string[50];
  FILE *in;
  
  sprintf(string,"%s",input1);
  if((in=fopen(string,"r"))==NULL)
    {
      printf("Error 4006 opening file %s \n", string);
      fclose(in);
      MPI_Finalize();
      exit(1);
   }
  
  for(j=0; j<NumGeo; j++)
  {
      fscanf(in,"%d  %d  %d\n",&geo[j][0], &geo[j][1],&geo[j][2]);
  }
  fclose(in);
  
  for(l=0; l<NumGeo; l++)
  {
    if(locate_node(geo[l][0])==my_rank)
    {

	i=geo[l][0]%Nx;
        j=geo[l][1];
        k=geo[l][2];
	
      if(vp[i+1][j][k]==-1974.0)
      {
       geo[l][2]=geo[l][2]-1;
      }
      k=geo[l][2];

      if(vp[i+1][j][k]==-1974.0)
      {
       geo[l][2]=geo[l][2]-1;
      }
      k=geo[l][2];

      if(vp[i+1][j][k]==-1974.0)
      {
       geo[l][2]=geo[l][2]-1;
      }
      
    }
  }

  sprintf(file_name,"%s_node%d",output4,my_rank);
  if((trace_node[my_rank]= fopen(file_name,"w")) ==NULL )
  {
       printf("Error opening 5034 trace file on node %d\n",my_rank);
       MPI_Finalize();
       exit(0);
  }


}     // End of Routine



void write_trace()
{
  int i,j,l;
  int jp,ip,kp;
  double a,b,c,aa[3];
  j=0;

  for(l=0; l<NumGeo; l++)
  {
    ip=geo[l][0]%Nx; jp=geo[l][1];  kp=geo[l][2];
    if(locate_node(geo[l][0])==my_rank)
    {
      a=posn[ip + 1][jp][kp][0]-eqposn[ip][jp][kp][0];
      b=posn[ip + 1][jp][kp][1]-eqposn[ip][jp][kp][1];
      c=posn[ip + 1][jp][kp][2]-eqposn[ip][jp][kp][2];

      aa[0]=a;   aa[1]=b; aa[2]=c;
      fwrite(&aa, sizeof(double), 3, trace_node[my_rank]);
    }
  }

}

// Closing files
void close_trace()
{
  int i;

  fclose(trace_node[my_rank]);

}     // End of routine

