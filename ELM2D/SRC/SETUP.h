
void set_up_geometry_and_neighbours()
{
  int i,j,k,n,m;
  int in,jn;
  double dist,dxx,dyy;
  double dummy1[Ny],dummy2[Ny];
  double g=1.0;

send_dens_vp(larray1,rarray1,1);// sending vp
send_dens_vp(larray2,rarray2,2);// sending vs
send_dens_vp(larray3,rarray3,3);// sending dens
send_posn();// sending positions

 for(i=0; i<Ny; i++)
 {
 for(j=0; j<Nx; j++)
 {
//----------------------------------------------------------------------------------------
  for(n=0; n<4; n++)
  {
   kspring[i][j][n]=0; 
   r0[i][j][n]=0;
   in=Index_NeighY(n)+i;
   jn=Index_NeighX(n)+j;

   g=(1.0);
   if(n==0 || n==2)
   { g=(0.5); } 
   
   if(in>=0 && in<Ny)
   {
    if(j==0)
    {
      if(n==0)
      {
        if(my_rank!=0)
	{
	  dxx=posn[i][j][0]-left_p[in][0];
          dyy=posn[i][j][1]-left_p[in][1];
          dist=sqrt((dxx*dxx)+(dyy*dyy));

	  r0[i][j][n]=dist;
          kspring[i][j][n]=g*( (vp[i][j]+larray1[in])*(vp[i][j]+larray1[in])/4.0
	                             -(vs[i][j]+larray2[in])*(vs[i][j]+larray2[in])/4.0 )
                                      *((dens[i][j]+larray3[in])/2.0);
			 
	  if(vp[i][j]==-1974.0 || larray1[in]==-1974.0)
          {
          kspring[i][j][n]=0.0;
          }
	}
      }
      else
      {
       dxx=posn[i][j][0]-posn[in][jn][0];
       dyy=posn[i][j][1]-posn[in][jn][1];
       dist=sqrt(dxx*dxx+dyy*dyy);

       r0[i][j][n]=dist;	    
       kspring[i][j][n]=g*( (vp[i][j]+vp[in][jn])*(vp[i][j]+vp[in][jn])/4.0
	                          -(vs[i][j]+vs[in][jn])*(vs[i][j]+vs[in][jn])/4.0 )
                                      *((dens[i][j]+dens[in][jn])/2.0);
			
	if(vp[i][j]==-1974.0 || vp[in][jn]==-1974.0)
        {
          kspring[i][j][n]=0.0;	  
        }
      }
    }
    else if(j==Nx-1)
    {
      if(n==2 || n==3)
      {
         if(my_rank!=(my_size-1) )
	 {
           dxx=posn[i][j][0]-right_p[in][0];
           dyy=posn[i][j][1]-right_p[in][1];
           dist=sqrt(dxx*dxx+dyy*dyy);
	   
	  r0[i][j][n]=dist;
          kspring[i][j][n]=g*( (vp[i][j]+rarray1[in])*(vp[i][j]+rarray1[in])/4.0
	                             -(vs[i][j]+rarray2[in])*(vs[i][j]+rarray2[in])/4.0 )
                                      *((dens[i][j]+rarray3[in])/2.0);
		
	  if(vp[i][j]==-1974.0 || rarray1[in]==-1974.0)
          {
          kspring[i][j][n]=0.0; 
          }
	  
	 }
      }
      else
      {
       dxx=posn[i][j][0]-posn[in][jn][0];
       dyy=posn[i][j][1]-posn[in][jn][1];
       dist=sqrt(dxx*dxx+dyy*dyy);

       r0[i][j][n]=dist;	    
       kspring[i][j][n]=g*( (vp[i][j]+vp[in][jn])*(vp[i][j]+vp[in][jn])/4.0
	                          -(vs[i][j]+vs[in][jn])*(vs[i][j]+vs[in][jn])/4.0 )
                                      *((dens[i][j]+dens[in][jn])/2.0);
				  
	if(vp[i][j]==-1974.0 || vp[in][jn]==-1974.0)
        {
          kspring[i][j][n]=0.0;
        }
      }
    }
    else
    {
      dxx=posn[i][j][0]-posn[in][jn][0];
      dyy=posn[i][j][1]-posn[in][jn][1];
      dist=sqrt(dxx*dxx+dyy*dyy);

      r0[i][j][n]=dist;
      kspring[i][j][n]=g*( (vp[i][j]+vp[in][jn])*(vp[i][j]+vp[in][jn])/4.0
	                         -(vs[i][j]+vs[in][jn])*(vs[i][j]+vs[in][jn])/4.0 )
                                      *((dens[i][j]+dens[in][jn])/2.0);
				  
	if(vp[i][j]==-1974.0 || vp[in][jn]==-1974.0)
        {
          kspring[i][j][n]=0.0; 
        }
     }
//if(i==205 && j==0 && my_rank==3)
//printf("T=%d | K(%d)=%e \n",n,n,kspring[i][j][n]); 
    }//if in
  } //n4
//------------------------------------------------------------------------------ 
/*}
}
//------------------------------------------------------------------------------ 
for(i=0; i<Ny; i++)
 {
 for(j=0; j<Nx; j++)
 {*/
//-----
 for(n=0; n<8; n++)
 {
   cbond[i][j][n]=0.0;
   in=Index_NeighY(n)+i;
   jn=Index_NeighX(n)+j;
   
  if(in>=0 && in<Ny)
  {
    if(j==0)
    {
      if(n==0 || n==6 || n==7)
      {
        if(my_rank!=0)
	{
         cbond[i][j][n]=(dx*dx*(dens[i][j]+larray3[in])/4.0)
	                      *( -((vp[i][j]+larray1[in])*(vp[i][j]+larray1[in])/4.0)
	           +(3.0/4.0)*(vs[i][j]+larray2[in])*(vs[i][j]+larray2[in]) );	  
	if(vp[i][j]==-1974.0 || larray1[in]==-1974.0)
        {
         cbond[i][j][n]=0.0;
        }
       }
      }
      else
      {
       cbond[i][j][n]=(dx*dx*(dens[i][j]+dens[in][jn])/4.0)
	                      *( -((vp[i][j]+vp[in][jn])*(vp[i][j]+vp[in][jn])/4.0)
	           +(3.0/4.0)*(vs[i][j]+vs[in][jn])*(vs[i][j]+vs[in][jn]) );
				  
	if(vp[i][j]==-1974.0 || vp[in][jn]==-1974.0)
        {
         cbond[i][j][n]=0.0;
        }
      }	
     }
     else if(j==(Nx-1) )
     {
       if(n==2 || n==3 || n==4)
       {
         if(my_rank!=(my_size-1))
	 {
	  cbond[i][j][n]=(dx*dx*(dens[i][j]+rarray3[in])/4.0)
	                      *( -((vp[i][j]+rarray1[in])*(vp[i][j]+rarray1[in])/4.0)
	                          +(3.0/4.0)*(vs[i][j]+rarray2[in])*(vs[i][j]+rarray2[in]) );
				  
	  if(vp[i][j]==-1974.0 || rarray1[in]==-1974.0)
          {
            cbond[i][j][n]=0.0;
          }
	 }
	}
        else
        { 
           cbond[i][j][n]=(dx*dx*(dens[i][j]+dens[in][jn])/4.0)
	                      *( -((vp[i][j]+vp[in][jn])*(vp[i][j]+vp[in][jn])/4.0)
	                          +(3.0/4.0)*(vs[i][j]+vs[in][jn])*(vs[i][j]+vs[in][jn]) );
				  
	   if(vp[i][j]==-1974.0 || vp[in][jn]==-1974.0)
           {
            cbond[i][j][n]=0.0;
           }
         }
	}
        else
	{
	 cbond[i][j][n]=(dx*dx*(dens[i][j]+dens[in][jn])/4.0)
	                      *( -((vp[i][j]+vp[in][jn])*(vp[i][j]+vp[in][jn])/4.0)
	                          +(3.0/4.0)*(vs[i][j]+vs[in][jn])*(vs[i][j]+vs[in][jn]) );
	   if(vp[i][j]==-1974.0 || vp[in][jn]==-1974.0)
           {
            cbond[i][j][n]=0.0;
           }
	}
	
//if(i==205 && j==5 && my_rank==3)
//printf("T=%d | C(%d)=%e \n",n,n,cbond[i][j][n]); 
       
    } //if in 
    } // end n8
//-----------------------------------------------------------------------------------
 }  //j
 } //i

 
 
 
   
}




