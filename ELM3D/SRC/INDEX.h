
                       /* Routine for x direction indexs in propagate*/
int IndexX(int k)
{
  int kx=0;

  if(k==0 || k==7)
  {
    kx=-1;
  }
  else if(k==1 || k==4 || k==5 || k==6)
  {
    kx=0;
  }
  else if(k==2 || k==3 || k==8)
  {
    kx=1;
  }

  return kx;
}

                        /* Routine for y direction indexs in propagate */
int IndexY(int k)
{
  int ky=0;

  if(k==4)
  {
    ky=-1;
  }
  else if(k==3 || k==5 || k==8 || k==7)
  {
    ky=0;
  }
  else if(k==1 || k==2 || k==6 || k==0)
  {
    ky=1;
  }

  return ky;
}
                       /* Routine for y direction indexs in propagate */
int IndexZ(int k)
{
  int kz=0;

  if(k==0 || k==1 || k==2 || k==3)
  {
    kz=0;
  }
  else if(k==4 || k==5 || k==6 || k==7 || k==8)
  {
    kz=1;
  }

  return kz;
}
