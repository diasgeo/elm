
void set_up_geometry_and_neighbours()
{
  int i,j,k,n;
  int in,jn,kn;
  double dist,dxx,dyy,dzz;
  double g=1.0;
  double add_on1=0,add_on2=0;

send_dens_vp(larray1,rarray1,1); // sending vp
send_dens_vp(larray2,rarray2,2); // sending vs
send_dens_vp(larray3,rarray3,3); // sending dens
send_posn();  // sending positions

  g=1.0;  
  
 for(i=0; i<Ny; i++)
 {
 for(j=0; j<Nx; j++)
 {
 for(k=0; k<Nz; k++)
 {
  for(n=0; n<9; n++)
  {
   kspring[i][j][k][n]=0.0;
   cbond[i][j][k][n]=0.0;
   in=IndexY(n)+i;
   jn=IndexX(n)+j;
   kn=IndexZ(n)+k;
     
   if(warp_around==1)
   {
     if(in==Ny) { in=0;  }
     if(in==-1) { in=Ny-1; } 
     if(kn==Nz) { kn=0;  }
     if(kn==-1) { kn=Nz-1; } 
   }
   
   if(in>=0 && in<Ny && kn>=0 && kn<Nz)
   {
    if(j==0)
    {
      if(IndexX(n)==-1)
      {
       if(my_rank==0)
       {
        add_on1=(dx*my_size*Nx);
       }
       else
       {
        add_on1=0;
       }
       dxx=posn[i][j][k][0]-left_p[in][kn][0]+add_on1;
       dyy=posn[i][j][k][1]-left_p[in][kn][1];
       dzz=posn[i][j][k][2]-left_p[in][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);

       kspring[i][j][k][n]=dx*( (vp[i][j][k]+larray1[in][kn])*(vp[i][j][k]+larray1[in][kn])/4.0
                                   -(vs[i][j][k]+larray2[in][kn])*(vs[i][j][k]+larray2[in][kn])/4.0 )
                                      *((dens[i][j][k]+larray3[in][kn])/4.0);

       cbond[i][j][k][n]=(dx*dx*dx*(dens[i][j][k]+larray3[in][kn])/8.0)
                              *( -(vp[i][j][k]+larray1[in][kn])*(vp[i][j][k]+larray1[in][kn])/4.0
                                  +3.0*(vs[i][j][k]+larray2[in][kn])*(vs[i][j][k]+larray2[in][kn])/4.0  );

	if(vp[i][j][k]==-1974.0 || larray1[in][kn]==-1974.0)
        {
          kspring[i][j][k][n]=0.0;  cbond[i][j][k][n]=0.0;
        }
      }
      else
      {
       dxx=posn[i][j][k][0]-posn[in][jn][kn][0];
       dyy=posn[i][j][k][1]-posn[in][jn][kn][1];
       dzz=posn[i][j][k][2]-posn[in][jn][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);

       kspring[i][j][k][n]=dx*( (vp[i][j][k]+vp[in][jn][kn])*(vp[i][j][k]+vp[in][jn][kn])/4.0
                                    -(vs[i][j][k]+vs[in][jn][kn])*(vs[i][j][k]+vs[in][jn][kn])/4.0 )
                                      *((dens[i][j][k]+dens[in][jn][kn])/4.0);

       cbond[i][j][k][n]=(dx*dx*dx*(dens[i][j][k]+dens[in][jn][kn])/8.0)
                              *( -(vp[i][j][k]+vp[in][jn][kn])*(vp[i][j][k]+vp[in][jn][kn])/4.0
                                  +3.0*(vs[i][j][k]+vs[in][jn][kn])*(vs[i][j][k]+vs[in][jn][kn])/4.0  );

	if(vp[i][j][k]==-1974.0 || vp[in][jn][kn]==-1974.0)
        {
          kspring[i][j][k][n]=0.0;cbond[i][j][k][n]=0.0;
        }
      }
    }
    else if(j==Nx-1)
    {
      if(IndexX(n)==1)
      {
       if( my_rank==(my_size-1) )
       {
        add_on2=(dx*my_size*Nx);
       }
       else
       {
        add_on2=0;
       }
       dxx=posn[i][j][k][0]-right_p[in][kn][0]-add_on2;
       dyy=posn[i][j][k][1]-right_p[in][kn][1];
       dzz=posn[i][j][k][2]-right_p[in][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);

      kspring[i][j][k][n]=dx*( (vp[i][j][k]+rarray1[in][kn])*(vp[i][j][k]+rarray1[in][kn])/4.0
                                    -(vs[i][j][k]+rarray2[in][kn])*(vs[i][j][k]+rarray2[in][kn])/4.0 )
                                      *((dens[i][j][k]+rarray3[in][kn])/4.0);

       cbond[i][j][k][n]=(dx*dx*dx*(dens[i][j][k]+rarray3[in][kn])/8.0)
                              *( -(vp[i][j][k]+rarray1[in][kn])*(vp[i][j][k]+rarray1[in][kn])/4.0
                                  +3.0*(vs[i][j][k]+rarray2[in][kn])*(vs[i][j][k]+rarray2[in][kn])/4.0  );
				  
	if(vp[i][j][k]==-1974.0 || rarray1[in][kn]==-1974.0)
        {
          kspring[i][j][k][n]=0.0;cbond[i][j][k][n]=0.0;
        }
      }
      else
      {
       dxx=posn[i][j][k][0]-posn[in][jn][kn][0];
       dyy=posn[i][j][k][1]-posn[in][jn][kn][1];
       dzz=posn[i][j][k][2]-posn[in][jn][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);

       kspring[i][j][k][n]=dx*( (vp[i][j][k]+vp[in][jn][kn])*(vp[i][j][k]+vp[in][jn][kn])/4.0
                                    -(vs[i][j][k]+vs[in][jn][kn])*(vs[i][j][k]+vs[in][jn][kn])/4.0 )
                                      *((dens[i][j][k]+dens[in][jn][kn])/4.0);

       cbond[i][j][k][n]=(dx*dx*dx*(dens[i][j][k]+dens[in][jn][kn])/8.0)
                              *( -(vp[i][j][k]+vp[in][jn][kn])*(vp[i][j][k]+vp[in][jn][kn])/4.0
                                  +3.0*(vs[i][j][k]+vs[in][jn][kn])*(vs[i][j][k]+vs[in][jn][kn])/4.0  );
				  
	if(vp[i][j][k]==-1974.0 || vp[in][jn][kn]==-1974.0)
        {
          kspring[i][j][k][n]=0.0;cbond[i][j][k][n]=0.0;
        }
      }
    }
    else
    {
       dxx=posn[i][j][k][0]-posn[in][jn][kn][0];
       dyy=posn[i][j][k][1]-posn[in][jn][kn][1];
       dzz=posn[i][j][k][2]-posn[in][jn][kn][2];
       dist=sqrt(dxx*dxx+dyy*dyy+dzz*dzz);

       kspring[i][j][k][n]=dx*( (vp[i][j][k]+vp[in][jn][kn])*(vp[i][j][k]+vp[in][jn][kn])/4.0
                                    -(vs[i][j][k]+vs[in][jn][kn])*(vs[i][j][k]+vs[in][jn][kn])/4.0 )
                                      *((dens[i][j][k]+dens[in][jn][kn])/4.0);

       cbond[i][j][k][n]=(dx*dx*dx*(dens[i][j][k]+dens[in][jn][kn])/8.0)
                              *( -(vp[i][j][k]+vp[in][jn][kn])*(vp[i][j][k]+vp[in][jn][kn])/4.0
                                  +3.0*(vs[i][j][k]+vs[in][jn][kn])*(vs[i][j][k]+vs[in][jn][kn])/4.0  );
				  
	if(vp[i][j][k]==-1974.0 || vp[in][jn][kn]==-1974.0)
        {
          kspring[i][j][k][n]=0.0;cbond[i][j][k][n]=0.0;
        }
    }

    }//if in
  } //n
 } //k
 }  //j
 } //i

  for(n=0; n<9; n++)
  {
   r0[n]=0;
   r0[n]=sqrt(IndexY(n)*IndexY(n)*dx*dx+IndexX(n)*IndexX(n)*dx*dx+IndexZ(n)*IndexZ(n)*dx*dx);
  }

 if(warp_around==0)
 {
  if(my_rank==0)
  {
   for(i=0; i<Ny; i++)
   {
   for(k=0; k<Nz; k++)
   {
   for(n=0; n<9; n++)
   {
     if(IndexX(n)==-1)
     {
      kspring[i][0][k][n]=0.0; cbond[i][0][k][n]=0.0;
     }
   }
   }
   }
  }

  if(my_rank==(my_size-1) )
  {
   for(i=0; i<Ny; i++)
   {
   for(k=0; k<Nz; k++)
   {
   for(n=0; n<9; n++)
   {
     if(IndexX(n)==1)
     {
      kspring[i][Nx-1][k][n]=0.0; cbond[i][Nx-1][k][n]=0.0;
     }
   }
   }
   }
  }
 }
/////////////////////////////////////////////////////
// Breaks diagonal bonds to replicate a cubic array
   for(i=1; i<Ny-1; i++)
   {
   for(j=0; j<Nx; j++)
   {
   for(k=1; k<Nz-1; k++)
   {
     if(kspring[i][j][k][5]==0.0)
     {
       kspring[i][j][k][4]=cbond[i][j][k][4]=0;
       kspring[i][j][k][6]=cbond[i][j][k][6]=0;
       kspring[i][j][k][7]=cbond[i][j][k][7]=0;
       kspring[i][j][k][8]=cbond[i][j][k][8]=0;
     }
     if(kspring[i][j][k][1]==0.0)
     {
       kspring[i][j][k][0]=cbond[i][j][k][0]=0;
       kspring[i][j][k][2]=cbond[i][j][k][2]=0;
       kspring[i][j][k][6]=cbond[i][j][k][6]=0;
     }
     if(kspring[i][j][k][3]==0.0)
     {
       kspring[i][j][k][2]=cbond[i][j][k][2]=0;
       kspring[i][j][k][8]=cbond[i][j][k][8]=0;
     }
   }
   }
   }
   
  for(i=0; i<9; i++)
  {
   ux[i]=dx*IndexX(i);
   uy[i]=dx*IndexY(i);
   uz[i]=dx*IndexZ(i);
   
 //  if(my_rank==0)
 //  printf("%d | %e %e %e | %e %e\n",i,ux[i],uy[i],uz[i],kspring[5][5][5][i],cbond[5][5][5][i]);
  } 
   
  /* for(i=0; i<Ny; i++)
   {
   for(j=0; j<Nx; j++)
   {
   for(k=0; k<Nz; k++)
   {
   for(n=0; n<9; n++)
   {
      cbond[i][j][k][n]=0.0;
   }
   }
   }
   }*/
  
}


