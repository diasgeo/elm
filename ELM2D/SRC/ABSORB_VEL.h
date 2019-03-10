
// Absorbing routine: Wavefield multplied by exponential along boundaries.
// NEEDS TO BE REWRITTEN MORE EFFICIENTLY
void absorb()
{
   int i,j,k;
   int aw;

     if( my_rank==0 )
     {  //       left
        aw=width;
	if(width>Nx) aw=Nx;

        for(i=0; i<Ny; i++)
        {
        for(j=0; j<aw; j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(width-j)*(width-j) );
           upy[i][j]=upy[i][j]*exp( -lambda*(width-j)*(width-j) );
        }
        }
      }
      if( my_rank==1 && width>Nx )
      {  //       left
        for(i=0; i<Ny; i++)
        {
        for(j=0; j<(width-Nx); j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );
           upy[i][j]=upy[i][j]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );

        }
	}
      }

      //else
      if(my_rank==(my_size-1) )
      {  // right absorbing
        aw=Nx-width;
	if(width>Nx) aw=0;
        for(i=0; i<Ny; i++)
        {
        for(j=aw; j<Nx; j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
           upy[i][j]=upy[i][j]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
        }
	}
      }
      if(my_rank==(my_size-2) && width>Nx )
      {  // right absorbing
        for(i=0; i<Ny; i++)
        {
        for(j=2*Nx-width; j<Nx; j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
           upy[i][j]=upy[i][j]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
        }
	}
      }

	// i direction
	for(i=0; i<=width; i++)
        {
        for(j=0; j<Nx; j++)
        {
           upx[i][j]=upx[i][j]*exp( -lambda*(width-i)*(width-i) );
           upy[i][j]=upy[i][j]*exp( -lambda*(width-i)*(width-i) );
        }
	}
	 // i-direction
	for(i=Ny-width; i<Ny; i++)
        {
        for(j=0; j<Nx; j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );
           upy[i][j]=upy[i][j]*exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );
        }
	}



}


// Absorbing routine: Wavefield multplied by exponential along boundaries.
// NEEDS TO BE REWRITTEN MORE EFFICIENTLY
void absorb_free()
{
   int i,j,k;
   int aw;

     if( my_rank==0 )
     {  //       left
        aw=width;
	if(width>Nx) aw=Nx;

        for(i=0; i<Ny; i++)
        {
        for(j=0; j<aw; j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(width-j)*(width-j) );
           upy[i][j]=upy[i][j]*exp( -lambda*(width-j)*(width-j) );
        }
        }
      }
      if( my_rank==1 && width>Nx )
      {  //       left
        for(i=0; i<Ny; i++)
        {
        for(j=0; j<(width-Nx); j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );
           upy[i][j]=upy[i][j]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );

        }
	}
      }

      //else
      if(my_rank==(my_size-1) )
      {  // right absorbing
        aw=Nx-width;
	if(width>Nx) aw=0;
        for(i=0; i<Ny; i++)
        {
        for(j=aw; j<Nx; j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
           upy[i][j]=upy[i][j]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
        }
	}
      }
      if(my_rank==(my_size-2) && width>Nx )
      {  // right absorbing
        for(i=0; i<Ny; i++)
        {
        for(j=2*Nx-width; j<Nx; j++)
        {
	   upx[i][j]=upx[i][j]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
           upy[i][j]=upy[i][j]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
        }
	}
      }

	// i direction
	for(i=0; i<=width; i++)
        {
        for(j=0; j<Nx; j++)
        {
           upx[i][j]=upx[i][j]*exp( -lambda*(width-i)*(width-i) );
           upy[i][j]=upy[i][j]*exp( -lambda*(width-i)*(width-i) );
        }
	}



}

