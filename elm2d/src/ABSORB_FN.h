

void absorb_fn()
{
 int i,j,k;
 
 abx=v_alloc1d(Nx);
 abz=v_alloc1d(Ny);

if(absorb_model==1.0)
{
 /// zzzz
 for(k=0; k<Ny; k++)
 {
  abz[k]=1.0;
  if(k<width)
  {
    abz[k]=exp( -lambda*(width-k)*(width-k) );
  }
  else if(k>Ny-width)
  {
    abz[k]=exp( -lambda*(-Ny+width+k)*(-Ny+width+k) );
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
/// zzzz
 for(k=0; k<Ny; k++)
 {
  abz[k]=1.0;
  if(k<width)
  {
    abz[k]=exp( -lambda*(width-k)*(width-k) );
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
else
{
 for(j=0; j<Nx; j++)
 {
   abx[j]=1.0;
 }
 for(k=0; k<Ny; k++)
 {
   abz[k]=1.0;
 }
}

}

void absorb()
{
 int j,i;
     
 for(i=0; i<Ny; i++)
 {
 for(j=0; j<Nx; j++)
 {
    upx[i][j]=upx[i][j]*abx[j]*abz[i];
    upy[i][j]=upy[i][j]*abx[j]*abz[i]; 
    force[i][j][0] = force[i][j][0]*abx[j]*abz[i] ;
    force[i][j][1] = force[i][j][1]*abx[j]*abz[i] ;
 }
 }
 
}

