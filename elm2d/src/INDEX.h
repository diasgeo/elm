

int Index_NeighX(int n)
{
  int m;

  if(n==0)
  {
    m=-1;
  }
  else if(n==1)
  {
    m=0;
  }
  else if(n==2)
  {
    m=1;
  }
  else if(n==3)
  {
    m=1;
  }
  else if(n==4)
  {
    m=1;
  }
  else if(n==5)
  {
    m=0;
  }
  else if(n==6)
  {
    m=-1;
  }
  else if(n==7)
  {
    m=-1;
  }

  return m;
}

int Index_NeighY(int n)
{
  int m;

  if(n==0)
  {
    m=1;
  }
  else if(n==1)
  {
    m=1;
  }
  else if(n==2)
  {
    m=1;
  }
  else if(n==3)
  {
    m=0;
  } 
  else if(n==4)
  {
    m=-1;
  }
  else if(n==5)
  {
    m=-1;
  }
  else if(n==6)
  {
    m=-1;
  }
  else
  {
    m=0;
  }

  return m;
}

int Index_NeighX1(int n)
{
  int m;

  if(n==0)
  {
    m=-1;
  }
  else if(n==1)
  {
    m=0;
  }
  else if(n==2)
  {
    m=1;
  }
  else
  {
    m=1;
  }

  return m;
}

int Index_NeighY1(int n)
{
  int m;

  if(n==0)
  {
    m=1;
  }
  else if(n==1)
  {
    m=1;
  }
  else if(n==2)
  {
    m=1;
  }
  else
  {
    m=0;
  }

  return m;
}
