void absorb_fn()
{
  int i,j,k;
  
  if(absorb_model==1.0)
  {

   /// yyyy
   for(i=0; i<Ny; i++)
   {
    aby[i]=1.0;
    if(i<width)
    {
      aby[i]=exp( -lambda*(width-i)*(width-i) );
    }
    else if(i>Ny-width)
    {
    aby[i]=exp( -lambda*(-Ny+width+i)*(-Ny+width+i) );
    }
  }
/// xxxx
  for(j=0; j<Nx; j++)
  {
    abx[j]=1.0;
    if( (j+my_rank*Nx) < width)
    {
      abx[j]=exp(-lambda*(width-j-my_rank*Nx)*(width-j-my_rank*Nx));
    }
    else if( (j+my_rank*Nx) > Nx*(my_size)-width)
    {
      abx[j]=exp(-lambda*(j+my_rank*Nx-Nx*(my_size)+width)*(j+my_rank*Nx-Nx*(my_size)+width));
    }
   }
  }
  else if(absorb_model==2.0)
  {
 ////////////////////////////////////////////////////////////////////
 /// yyyy
 for(i=0; i<Ny; i++)
 {
  aby[i]=1.0;
  if(i<width)
  {
    aby[i]=exp( -lambda*(width-i)*(width-i) );
  }
 }
////////////////////////////////////////////////////////////////////
/// xxxx
 for(j=0; j<Nx; j++)
 {
  abx[j]=1.0;
  if( (j+my_rank*Nx) < width)
  {
    abx[j]=exp(-lambda*(width-j-my_rank*Nx)*(width-j-my_rank*Nx));
  }
  else if( (j+my_rank*Nx) > Nx*(my_size)-width)
  {
  abx[j]=exp(-lambda*(j+my_rank*Nx-Nx*(my_size)+width)*(j+my_rank*Nx-Nx*(my_size)+width));
  }
 }

}
else
{
 for(j=0; j<Nx; j++)
 {
   abx[j]=1.0;
 }
 for(i=0; i<Ny; i++)
 {
   aby[i]=1.0;
 }

}

}

// NEEDS TO BE REWRITTEN MORE EFFICIENTLY
void absorb()
{
 int i,j;

        for(i=0; i<Nx; i++)
        {
        for(j=0; j<Ny; j++)
        {
	   up[i][j][0]=up[i][j][0]*abx[i]*aby[j];
           up[i][j][1]=up[i][j][1]*abx[i]*aby[j];
        }
	}

}
