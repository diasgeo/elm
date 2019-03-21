
void fractures()
{
  int i,j,m,n;
  double x1[NoFrac],y1[NoFrac],x2[NoFrac],y2[NoFrac];
  double Comp[NoFrac],fno[NoFrac],slope[NoFrac],cept[NoFrac];
  double xx,xmax,xmin,yy,ymax,ymin,l;
  FILE *input;

   if(( input= fopen(input3,"r")) ==NULL )
   {
     printf("Error opening velocity file on node %d\n",my_rank);
     MPI_Finalize();
     exit(0);
   }
   i=0;  
   for(i=0; i<NoFrac; i++)
   {
     fscanf(input,"%lf %lf %lf %lf %lf %lf\n",&x1[i],&y1[i],&x2[i],&y2[i],&Comp[i],&l);
     
     slope[i]=(y2[i]-y1[i])/(x2[i]-x1[i]);
     
     if(x2[i]==x1[i])
     slope[i]=-999.0;
     
     //x1[i]=x1[i]/(dx);
    // y1[i]=y1[i]/(dx);
    // x2[i]=x2[i]/(dx);
     //y2[i]=y2[i]/(dx);
    // Comp[i]=0;
     
     x1[i]=x1[i];
     y1[i]=y1[i];
     x2[i]=x2[i];
     y2[i]=y2[i];
     cept[i]=-slope[i]*x1[i]+y1[i];
//printf("%lf %lf %lf %lf %lf %lf %lf\n",x1[i],y1[i],x2[i],y2[i],Comp[i],fno[i],slope[i]);    
   }
   
   for(i=0; i<NoFrac; i++)
   {
   for(m=0; m<Ny; m++)
   {
    if(slope[i]!=0 && slope[i]!=-999.0)
    {
     xx=(m-cept[i])/slope[i];
     xmin=Min(x1[i],x2[i]);
     xmax=Max(x1[i],x2[i]);
      
      if(xx>=xmin && xx<=xmax)
      {    
        j=floor(xx);
	if(locate_node(j)==my_rank && j>=0 && (j%Nx)<Nx)
	{
         kspring[m][j%Nx][3]=Comp[i];
	}
      }
    }
   }
   }
   
   for(i=0; i<NoFrac; i++)
   {
   for(m=0; m<Nx; m++)
   {
     yy=slope[i]*(m+Nx*my_rank)+cept[i];
     xx=m+Nx*my_rank;
     ymin=Min(y1[i],y2[i]);
     ymax=Max(y1[i],y2[i]); 
     xmin=Min(x1[i],x2[i]);
     xmax=Max(x1[i],x2[i]);
  
     if( xx>=xmin && xx<=xmax)
     {    
       j=floor(yy);
       if(j>=0 && j<Ny)
       kspring[j][m][1]=Comp[i];
     }   
   }
   }
   
   for(i=0; i<NoFrac; i++)
   {
   for(m=-Ny-1; m<Ny; m++)
   {
    if(slope[i]!=1 && slope[i]!=-999.0)
    {
     xx=(m-cept[i])/(slope[i]-1.0);
     yy=slope[i]*xx+cept[i];
     
     ymin=Min(y1[i],y2[i]);
     ymax=Max(y1[i],y2[i]);  
     xmin=Min(x1[i],x2[i]);
     xmax=Max(x1[i],x2[i]);
     j=floor(xx); n=floor(yy); 
       
     if(xx>=xmin && xx<=xmax && yy>=ymin && yy<=ymax) 
     {    
       if(locate_node(j)==my_rank)
       {
         if(n>=0 && n<Ny && j>=0 && (j%Nx)<Nx)
         kspring[n][j%Nx][2]=Comp[i];
       }
     } 
    }  
   }
   }
   
   for(i=0; i<NoFrac; i++)
   {
   for(m=0; m<2*Ny; m++)
   {
    if(slope[i]!=-1 && slope[i]!=-999.0)
    {
     xx=(m-cept[i])/(slope[i]+1.0);
     yy=slope[i]*xx+cept[i];
     
     ymin=Min(y1[i],y2[i]);
     ymax=Max(y1[i],y2[i]);  
     xmin=Min(x1[i],x2[i]);
     xmax=Max(x1[i],x2[i]);
     j=floor(xx); n=floor(yy); 
          
     if(xx>=xmin && xx<=xmax && yy>=ymin && yy<=ymax) 
     {    
       if(locate_node(j)==my_rank)
       {
         if(n>=0 && n<Ny && j>=0 && (j%Nx)<Nx)
         kspring[n][j%Nx][0]=Comp[i];
	// printf("%d %lf %lf %d %d %lf %lf %d\n",i,xx,yy,j,n,ymin,ymax,m);              
       }
     } 
    }  
   }
   }
   
   for(i=0; i<NoFrac; i++)
   {
    if(slope[i]==-999.0)
    {
     for(m=0; m<Ny; m++)
     {
      ymin=Min(y1[i],y2[i]);
      ymax=Max(y1[i],y2[i]);  
      xmin=Min(x1[i],x2[i]);
      xmax=Max(x1[i],x2[i]);
       
       xx=xmax;  yy=m;
       j=floor(xx); 
       if(yy>=ymin && yy<=ymax) 
       { 
       if(locate_node(j)==my_rank && j>=0 && (j%Nx)<Nx)
       {
         kspring[m][j%Nx][3]=Comp[i];
	 kspring[m][j%Nx][2]=Comp[i];          
       }
       }
       
       j=ceil(xx); 
       if(yy>=ymin && yy<=ymax) 
       {
       if(locate_node(j)==my_rank && j>=0 && (j%Nx)<Nx)
       {
         kspring[m][j%Nx][0]=Comp[i];     
       }     
       }
         
     }
    }
   }
   
}    // End or routine

