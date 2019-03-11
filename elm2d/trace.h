

// Open trace files and locate them correctly
void trace_files()
{
  int i,j,a1;
  double ss1,ss2,m1, m2, m3;
  char file_name[50];
  char  string[50];
  FILE *in;

   sprintf( string,"%s",input6);
   if(( in= fopen(string,"r")) ==NULL)
   {
      printf("Error 4006 opening file %s \n", string);
      MPI_Finalize();
      fclose(in);
      exit(1);
   }

  for(j=0; j<NumGeo; j++)
  {
    //fscanf(in,"%d  %d\n",&geo[j][0], &geo[j][1]); 
    //printf("%d  %d  %d\n",my_rank,geo[j][0], geo[j][1]);
    fscanf(in,"%d %lf %lf %lf  %lf %lf\n",&a1, &m1, &m2, &ss1, &ss2, &m3); 

      geo[j][0]=round(ss1/dx);
      geo[j][1]=round(ss2/dx);

      if(ss2==(Ny-1)*dx)
      {
        geo[j][1]=Ny-1;
      }
    
      if(geo[j][1]*dx>topo1[geo[j][0]][1])
      {
        geo[j][1]=geo[j][1]-1;
      }
      if(geo[j][1]*dx>topo1[geo[j][0]][1])
      {
        geo[j][1]=geo[j][1]-1;
      } 
      if(geo[j][1]*dx>topo1[geo[j][0]][1])
      {
        geo[j][1]=geo[j][1]-1;
      }
      if(geo[j][1]*dx>topo1[geo[j][0]][1])
      {
        geo[j][1]=geo[j][1]-1;
      }
      if(geo[j][1]*dx>topo1[geo[j][0]][1])
      {
        geo[j][1]=geo[j][1]-1;
      }
      if(geo[j][1]*dx>topo1[geo[j][0]][1])
      {
        geo[j][1]=geo[j][1]-1;
      }


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
      sprintf(file_name,"%s%d",output4,j);
      //printf("%d %s%d_%d",my_rank, output4,geo[j][0],geo[j][1]);
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
      ip=phone[i][0]; jp=phone[i][1];
    if(locate_node(geo[i][0])==my_rank && phone[i][0]!=-1)
    {  

      fprintf(out_trace[i],"%e %e \n",up[ip][jp][0],up[ip][jp][1]);
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

