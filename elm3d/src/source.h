
void source_routine()
{
 int s,i,j,k,n;
 FILE *in;
 char string[50];

 for (s = 0; s < NumSource; s++)
 { 
// Calculating source
 if(input_source==1)
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
     fscanf(in,"%lf\n",&msource[i][s]);
   }
   fclose(in);
  }
 }

   // Read in the x and y positions of sources:
 sprintf( string,"%s",input2);
 if(( in= fopen(string,"r")) ==NULL)
 {
    printf("Error opening file %s \n", string);
    MPI_Finalize();
    fclose(in);
    exit(1);
 }

 for (s = 0; s < NumSource; s++)
 {
      source[0][s]=source[1][s]=source[2][s]=0;
      fscanf( in,"%d %d %d\n", &source[0][s], &source[1][s], &source[2][s]);
 }
 fclose(in);
 n=0;
 


}

void moment_source()
{
  int i,j,k,jp,jm,s,im,ip,km,kp;
//  double mxx,myy,mzz,mxy,mxz,myz;
  
 // mxx=1.0;
  //myy=1.0;
  //mzz=1.0;
  //mxy=0.0;
  //mxz=0.0;
  //myz=0.0;
  
 for (s = 0; s < NumSource; s++)
 {
   i=source[0][s]%Nx;  im=(source[0][s]-1)%Nx; ip=(source[0][s]+1)%Nx;
   j=source[1][s];     jm=source[1][s]-1;      jp=source[1][s]+1;
   k=source[2][s];     km=source[2][s]-1;      kp=source[2][s]+1;
 
   if(jm==Ny) { jm=0;  }
   if(jm==-1) { jm=Ny-1; } 
   if(km==Nz) { km=0;  }
   if(km==-1) { km=Nz-1; }  
   
   if(jp==Ny) { jp=0;  }
   if(jp==-1) { jp=Ny-1; } 
   if(kp==Nz) { kp=0;  }
   if(kp==-1) { kp=Nz-1; }
  
   if(locate_node(source[0][s] + 0) == my_rank)
   {
     force[i + ff][j][kp][0] = force[i + ff][j][kp][0] + mxz*sscale*msource[run_time][s];
     force[i + ff][j][kp][1] = force[i + ff][j][kp][1] + myz*sscale*msource[run_time][s];
     force[i + ff][j][kp][2] = force[i + ff][j][kp][2] + mzz*sscale*msource[run_time][s];
     
     force[i + ff][j][km][0] = force[i + ff][j][km][0] - mxz*sscale*msource[run_time][s];
     force[i + ff][j][km][1] = force[i + ff][j][km][1] - myz*sscale*msource[run_time][s];
     force[i + ff][j][km][2] = force[i + ff][j][km][2] - mzz*sscale*msource[run_time][s];
     
     force[i + ff][jp][k][0] = force[i + ff][jp][k][0] + mxy*sscale*msource[run_time][s];
     force[i + ff][jp][k][1] = force[i + ff][jp][k][1] + myy*sscale*msource[run_time][s];
     force[i + ff][jp][k][2] = force[i + ff][jp][k][2] + myz*sscale*msource[run_time][s];
     
     force[i + ff][jm][k][0] = force[i + ff][jm][k][0] - mxy*sscale*msource[run_time][s];
     force[i + ff][jm][k][1] = force[i + ff][jm][k][1] - myy*sscale*msource[run_time][s];
     force[i + ff][jm][k][2] = force[i + ff][jm][k][2] - myz*sscale*msource[run_time][s];
   }
   if(locate_node(source[0][s]+ 1)==my_rank)
   {
     force[ip + ff][j][k][0] = force[ip + ff][j][k][0] + mxx*sscale*msource[run_time][s];
     force[ip + ff][j][k][1] = force[ip + ff][j][k][1] + mxy*sscale*msource[run_time][s];
     force[ip + ff][j][k][2] = force[ip + ff][j][k][2] + mxz*sscale*msource[run_time][s];
     
   }
   if(locate_node(source[0][s]-1)==my_rank)
   { 
     force[im + ff][j][k][0] = force[im + ff][j][k][0] - mxx*sscale*msource[run_time][s];
     force[im + ff][j][k][1] = force[im + ff][j][k][1] - mxy*sscale*msource[run_time][s];
     force[im + ff][j][k][2] = force[im + ff][j][k][2] - mxz*sscale*msource[run_time][s];
   }
   
 }

}

void vol_source()
{
  int i,j,k,ii,s;


 for (s = 0; s < NumSource; s++)
 {

   i=source[0][s]%Nx; 
   ii=(source[0][s]+1)%Nx;
   j=source[1][s];
   k=source[2][s];

   if(j==Ny) { j=0;  }
   if(j==-1) { j=Ny-1; } 
   if(k==Nz) { k=0;  }
   if(k==-1) { k=Nz-1; } 

   if(locate_node(source[0][s])==my_rank)
   {
          force[i+ff][j][k][0] = force[i+ff][j][k][0] - sscale*msource[run_time][s];
          force[i+ff][j][k][1] = force[i+ff][j][k][1] - sscale*msource[run_time][s];
          force[i+ff][j][k][2] = force[i+ff][j][k][2] - sscale*msource[run_time][s];

          force[i+ff][j+1][k][0] = force[i+ff][j+1][k][0] - sscale*msource[run_time][s];
          force[i+ff][j+1][k][1] = force[i+ff][j+1][k][1] + sscale*msource[run_time][s];
          force[i+ff][j+1][k][2] = force[i+ff][j+1][k][2] - sscale*msource[run_time][s];

          force[i+ff][j][k+1][0] = force[i+ff][j][k+1][0] - sscale*msource[run_time][s];
          force[i+ff][j][k+1][1] = force[i+ff][j][k+1][1] - sscale*msource[run_time][s];
          force[i+ff][j][k+1][2] = force[i+ff][j][k+1][2] + sscale*msource[run_time][s];

          force[i+ff][j+1][k+1][0] = force[i+ff][j+1][k+1][0] - sscale*msource[run_time][s];
          force[i+ff][j+1][k+1][1] = force[i+ff][j+1][k+1][1] + sscale*msource[run_time][s];
          force[i+ff][j+1][k+1][2] = force[i+ff][j+1][k+1][2] +  sscale*msource[run_time][s];
   }
   if(locate_node(source[0][s]+1)==my_rank)
   {
          force[ii+ff][j][k][0] = force[ii+ff][j][k][0] + sscale*msource[run_time][s];
          force[ii+ff][j][k][1] = force[ii+ff][j][k][1] - sscale*msource[run_time][s];
          force[ii+ff][j][k][2] = force[ii+ff][j][k][2] - sscale*msource[run_time][s];

          force[ii+ff][j+1][k][0] = force[ii+ff][j+1][k][0] + sscale*msource[run_time][s];
          force[ii+ff][j+1][k][1] = force[ii+ff][j+1][k][1] + sscale*msource[run_time][s];
          force[ii+ff][j+1][k][2] = force[ii+ff][j+1][k][2] - sscale*msource[run_time][s];

          force[ii+ff][j][k+1][0] = force[ii+ff][j][k+1][0] + sscale*msource[run_time][s];
          force[ii+ff][j][k+1][1] = force[ii+ff][j][k+1][1] - sscale*msource[run_time][s];
          force[ii+ff][j][k+1][2] = force[ii+ff][j][k+1][2] + sscale*msource[run_time][s];

          force[ii+ff][j+1][k+1][0] = force[ii+ff][j+1][k+1][0] + sscale*msource[run_time][s];
          force[ii+ff][j+1][k+1][1] = force[ii+ff][j+1][k+1][1] + sscale*msource[run_time][s];
          force[ii+ff][j+1][k+1][2] = force[ii+ff][j+1][k+1][2] + sscale*msource[run_time][s];
   }

  }

}


void force_source()
{
  int i,j,k,s;

 for (s = 0; s < NumSource; s++)
 {

   i=source[0][s]%Nx; 
   j=source[1][s];
   k=source[2][s];

   if(j==Ny) { j=0;  }
   if(j==-1) { j=Ny-1; } 
   if(k==Nz) { k=0;  }
   if(k==-1) { k=Nz-1; } 

   if(locate_node(source[0][s])==my_rank)
   {
     force[i+ff][j][k][sdir] = force[i+ff][j][k][sdir] + sscale*msource[run_time][s];
   }

 }

}

void plane_waveX()
{
 int i,j,k,s;

 if(my_rank==0)
 {
  i=0;
  for(j=0; j<Ny; j++)
  {
  for(k=0; k<Nz; k++)
  {
     force[i+ff][j][k][0] = force[i+ff][j][k][0] + sscale*msource[run_time][0];
  }
  }
 }

}

void plane_waveY()
{
 int i,j,k,s;

  j=0;
  for(i=0; i<Nx; i++)
  {
  for(k=0; k<Nz; k++)
  {
     force[i+ff][j][k][1] = force[i+ff][j][k][1] + sscale*msource[run_time][0];
  }
  }

}

void plane_waveZ()
{
 int i,j,k,s;

  k=0;
  for(i=0; i<Nx; i++)
  {
  for(j=0; j<Ny; j++)
  {
     force[i+ff][j][k][2] = force[i+ff][j][k][2] + sscale*msource[run_time][0];
  }
  }

}


////////////////////////////////////////////////////////////////////////

