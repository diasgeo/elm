
// Absorbing routine: Wavefield multplied by exponential along boundaries. Node 0 and
// my_size-1 are extremes and all nodes at the top and bottom.

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
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(width-j)*(width-j) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(width-j)*(width-j) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(width-j)*(width-j) );
        }
        }
	}
      }
      if( my_rank==1 && width>Nx )
      {  //       left
        for(i=0; i<Ny; i++)
        {
        for(j=0; j<(width-Nx); j++)
        {
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );

        }
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
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
        }
        }
	}
      }
      if(my_rank==(my_size-2) && width>Nx )
      {  // right absorbing
        for(i=0; i<Ny; i++)
        {
        for(j=2*Nx-width; j<Nx; j++)
        {
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
        }
        }
	}
      }
    //  else  // On internal grid: Only consider bottom and left and right
    //  { // bottom
        for(i=0; i<Ny; i++)
        {
        for(j=0; j<Nx; j++)
        {
	for(k=0; k<=width; k++)
        {
           upx[i][j][k]=upx[i][j][k]*exp( -lambda*(width-k)*(width-k) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(width-k)*(width-k) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(width-k)*(width-k) );

        }
        }
	}
	 //top
	for(i=0; i<Ny; i++)
        {
        for(j=0; j<Nx; j++)
        {
	for(k=Nz-width; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(-Nz+width+k)*(-Nz+width+k) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(-Nz+width+k)*(-Nz+width+k) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(-Nz+width+k)*(-Nz+width+k) );

        }
        }
	}
	// i direction
	for(i=0; i<=width; i++)
        {
        for(j=0; j<Nx; j++)
        {
	for(k=0; k<Nz; k++)
        {
           upx[i][j][k]=upx[i][j][k]*exp( -lambda*(width-i)*(width-i) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(width-i)*(width-i) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(width-i)*(width-i) );

        }
        }
	}
	 // i-direction
	for(i=Ny-width; i<Ny; i++)
        {
        for(j=0; j<Nx; j++)
        {
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );   

        }
        }
	}



}

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
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(width-j)*(width-j) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(width-j)*(width-j) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(width-j)*(width-j) );
        }
        }
	}
      }
      if( my_rank==1 && width>Nx )
      {  //       left
        for(i=0; i<Ny; i++)
        {
        for(j=0; j<(width-Nx); j++)
        {
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(width-j-Nx)*(width-j-Nx) );
        }
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
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(j-Nx+width)*(j-Nx+width) );
        }
        }
	}
      }
      if(my_rank==(my_size-2) && width>Nx )
      {  // right absorbing
        for(i=0; i<Ny; i++)
        {
        for(j=2*Nx-width; j<Nx; j++)
        {
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(j-2*Nx+width)*(j-2*Nx+width) );
        }
        }
	}
      }
        
	for(i=0; i<Ny; i++)
        {
        for(j=0; j<Nx; j++)
        {
	for(k=0; k<=width; k++)
        {
           upx[i][j][k]=upx[i][j][k]*exp( -lambda*(width-k)*(width-k) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(width-k)*(width-k) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(width-k)*(width-k) );
        }
        }
	}

	// i direction
	for(i=0; i<=width; i++)
        {
        for(j=0; j<Nx; j++)
        {
	for(k=0; k<Nz; k++)
        {
           upx[i][j][k]=upx[i][j][k]*exp( -lambda*(width-i)*(width-i) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(width-i)*(width-i) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(width-i)*(width-i) );
        }
        }
	}
	 // i-direction
	for(i=Ny-width; i<Ny; i++)
        {
        for(j=0; j<Nx; j++)
        {
	for(k=0; k<Nz; k++)
        {
	   upx[i][j][k]=upx[i][j][k]*exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );
           upy[i][j][k]=upy[i][j][k]*exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );
           upz[i][j][k]=upz[i][j][k]*exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );
        }
        }
	}
    //  }

}

// end of routinue

