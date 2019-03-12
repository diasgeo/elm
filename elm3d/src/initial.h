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

void initial_lattice_setup()
{
 int i,j,k;
 double fake1,fake2,fake3,aa;
 FILE *inputvel[my_size];
 char string[50];
 size_t bytes_read;

 iroot2=(1.0/sqrt(2.0));
 dt2=(dt*0.5);

 NumSnaps=0;
 NumSnapsS=0;

 ///////////////////////////////////////////////////////////////////
 IndexX[0]=-1;
 IndexX[1]=0;
 IndexX[2]=1;
 IndexX[3]=1;
 IndexX[4]=0;
 IndexX[5]=0;
 IndexX[6]=0;
 IndexX[7]=-1;
 IndexX[8]=1;

 IndexY[0]=1;
 IndexY[1]=1;
 IndexY[2]=1;
 IndexY[3]=0;
 IndexY[4]=-1;
 IndexY[5]=0;
 IndexY[6]=1;
 IndexY[7]=0;
 IndexY[8]=0;

 IndexZ[0]=0;
 IndexZ[1]=0;
 IndexZ[2]=0;
 IndexZ[3]=0;
 IndexZ[4]=1;
 IndexZ[5]=1;
 IndexZ[6]=1;
 IndexZ[7]=1;
 IndexZ[8]=1;

///////////////////////////////////////////////////////////////////
 // Assigning Initial Homogeneous Values
 for(i=0; i<Nx+2; i++)
 {
 for(j=0; j<Ny; j++)
 {
 for(k=0; k<Nz; k++)
 {

   if(i<Nx)
   {
   up[i][j][k][0]=0.0;
   up[i][j][k][1]=0.0; 
   up[i][j][k][2]=0.0;
   }

   dens[i][j][k]=density;
   vp[i][j][k]=velp;
   vs[i][j][k]=vels;

 }
 }
 }

 // Opening Velocity file on all nodes
 if(velocity_model==1)
 {
   sprintf(string,"%s%d",input0,my_rank);
   if(( inputvel[my_rank]= fopen(string,"r")) ==NULL )
   {
      printf("Error opening velocity file on node %d\n",my_rank);
      MPI_Finalize();
      exit(0);
   }

   for(i=0; i<Nx; i++)
   {
   for(j=0; j<Ny; j++)
   {
   for(k=0; k<Nz; k++)//for(k=0; k<Nz-1; k++)
   {
     bytes_read=fread(&aa, sizeof(double), 1, inputvel[my_rank]);

     if(aa==0.0)
     aa=-1974.0;

     vp[i+1][j][k]=aa;
     vs[i+1][j][k]=aa*0.5774;
     dens[i+1][j][k]=1700.0+0.2*aa;
   }
   }
   }

  /* for(i=0; i<Nx; i++)
   {
   for(j=0; j<Ny; j++)
   {
     k=Nz-1;
     //bytes_read=fread(&aa, sizeof(double), 1, inputvel[my_rank]);
     vp[i+1][j][k]=-1974.0;
     vs[i+1][j][k]=aa*0.5774;
     dens[i+1][j][k]=1700.0+0.2*aa;
 
   }
   }*/

   fclose(inputvel[my_rank]);
 }



 for(i=0; i<Nx; i++)
 {
 for(j=0; j<Ny; j++)
 {
 for(k=0; k<Nz; k++)
 {
    posn[i+1][j][k][0]=i*dx+my_rank*dx*Nx;
    posn[i+1][j][k][1]=dx*j;
    posn[i+1][j][k][2]=dx*k;

    eqposn[i][j][k][0]=posn[i+1][j][k][0];
    eqposn[i][j][k][1]=posn[i+1][j][k][1];
    eqposn[i][j][k][2]=posn[i+1][j][k][2];

  }
  }
  }

  lr_count=lr_countx=lr_county=lr_countz=0;
  for(i=0; i<Nx; i=i+LR)
  {  
     lr_countx++; 
     lr_countz=0;
  for(k=0; k<Nz; k=k+LR)
  { 
	lr_countz++;
	lr_county=0;
  for(j=0; j<Ny; j=j+LR)
  {
	lr_count++; 
	lr_county++;
  }
  }
  }
 
  
}

int **alloc2d_int(int n1,int n2)
{
  int i;
  int **v;

 v=(int **) calloc(n1,sizeof(int *));
 if (v==NULL)
 {
    printf(" Could not allocate memory 301\n");
    exit(1);
 }
 for(i=0; i<n1; i++)
 {
   v[i]=(int *) calloc(n2,sizeof(int ));
   if (v[i]==NULL)
   {
      printf(" Could not allocate memory 302\n");
      exit(1);
   }
 }

 return v;

}

// Freeing 2d array
void free_array2d_int_other(int **dummy)
{
  int i;
 for(i=0; i<Ny*Nx*my_size; i++)
 {
    free(dummy[i]);
 }
 free(dummy);

}


void setup_top()
{
  int k,n,p;
  FILE *input;
 // int topo[Nx*Ny*my_size][3];
  int **topo;

  topo=alloc2d_int(Nx*Ny*my_size,3);

  if(( input= fopen(input5,"r"))==NULL )
  {
      printf("Error 5001: opening topography file on node %d\n",my_rank);
      MPI_Finalize();
      exit(0);
  }

  // scan in topography file
  for (n=0; n<(Nx*Ny*my_size); n++)
  {
    fscanf(input,"%d %d %d\n",&topo[n][0],&topo[n][1],&topo[n][2]);
  }
  fclose(input);

  for(n=0; n<Nx*Ny*my_size; n++)
  {
    if(my_rank==locate_node(topo[n][0]))
    {
       p=(topo[n][0]%Nx);
       for(k=topo[n][2]; k<Nz; k++)
       {
         vp[p+1][topo[n][1]][k]=-1974.0;
       }
    }
  }
  free_array2d_int_other(topo);
}


void setup_layer1()
{
  int i,j,k,n,p;
  FILE *input;
  int **topo;
  //int topo[Nx*Ny*my_size][3];

  topo=alloc2d_int(Ny*Nx*my_size,3);

  if(( input= fopen(input5,"r"))==NULL )
    {
      printf("Error 5001: opening topography file on node %d\n",my_rank);
      MPI_Finalize();
      exit(0);
    }

  // scan in topography file
  for (n=0; n<(Ny*Nx*my_size); n++)
    {
      fscanf(input,"%d %d %d\n",&topo[n][0],&topo[n][1],&topo[n][2]);
 }
  fclose(input);

   for(n=0; n<Ny*Nx*my_size; n++)
   {
      if(my_rank==locate_node(topo[n][0]))
      {
	  p=(topo[n][0]%Nx);
	  for(k=topo[n][2]; k>=topo[n][2]-13; k--)
	  {
	      vp[p+1][topo[n][1]][k] = 1000.0 + (topo[n][2]-k)*76.9231;
	      vs[p+1][topo[n][1]][k] = 575.0 + (topo[n][2]-k)*48.0769;
	      dens[p+1][topo[n][1]][k] = 1700.0 + 0.2*vp[p+1][topo[n][1]][k];
	  }
       }
    }
  free_array2d_int_other(topo);

}



void setup_layer2()
{
  int i,j,k,n,p;
  FILE *input;
  int **topo;
  //int topo[Nx*Ny*my_size][3];

  topo=alloc2d_int(Ny*Nx*my_size,3);

  if(( input= fopen(input5,"r"))==NULL )
    {
      printf("Error 5001: opening topography file on node %d\n",my_rank);
      MPI_Finalize();
      exit(0);
    }

  // scan in topography file
  for (n=0; n<(Ny*Nx*my_size); n++)
    {
      fscanf(input,"%d %d %d\n",&topo[n][0],&topo[n][1],&topo[n][2]);
 }
  fclose(input);

   for(n=0; n<Ny*Nx*my_size; n++)
   {
      if(my_rank==locate_node(topo[n][0]))
      {
	  p=(topo[n][0]%Nx);
	  for(k=topo[n][2]-14; k>=0; k--)
	  {
	      vp[p+1][topo[n][1]][k]=2000.0 + (topo[n][2]-14-k)*3.9894;
	      vs[p+1][topo[n][1]][k]=1200.0 + (topo[n][2]-14-k)*2.1277;
	      dens[p+1][topo[n][1]][k]=1700.0 + 0.2*vp[p+1][topo[n][1]][k];
	  }
       }
    }
  free_array2d_int_other(topo);

}


