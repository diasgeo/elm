#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

///----------------------------------------------
#define my_size         64                  // number of nodes used
#define Nx             (2)                 // X DIR 
#define Max_Time       (10001)               // Max run iterations
#define NumGeo       	13             // Number geophone locations
#define input0         "recorders"                 // trace coordinates in x y format
#define input1         "bulk_rec_node"                 // trace coordinates in x y format
#define output1        "station"
///----------------------------------------------


int locate_node(int coord);


main(int argc ,char *argv[])
{
  int i,j,k,ts,x,y,z;
  int geo[NumGeo][3],newG[NumGeo][3];
  int number_on_node,node;
  int Numlines,no;
  size_t bytes_read;
  double aa[3],vx,vy,vz,dx,dy,dz;
  char  string[50];
  char *d,c[50];
  FILE *in,*out[NumGeo];

  //---------------------------------------------------
  // open recorder location file
  sprintf(string,"%s",input0);
  if((in=fopen(string,"r"))==NULL)
  {
    printf("Error 1001 opening file %s \n", string);
    fclose(in);
    exit(1);
  }
  for(i=0; i<NumGeo; i++)
  {
    fscanf(in,"%d  %d  %d\n",&geo[i][0], &geo[i][1],&geo[i][2]); 
  }
  fclose(in);

  //--------------------------------------------------- 
  // count number of stations in this region 
for(node=0; node<my_size; node++)
{
  number_on_node=0;
  for(i=0; i<NumGeo; i++)
  {
    newG[number_on_node][0]=newG[number_on_node][1]=newG[number_on_node][2]=0; 
    if(locate_node(geo[i][0])==node)
    {
     newG[number_on_node][0]=geo[i][0];
     newG[number_on_node][1]=geo[i][1];
     newG[number_on_node][2]=geo[i][2]; 
     number_on_node++;
    }
  }
  Numlines = number_on_node*Max_Time;

  printf("... %d number of points in this node file %d\n",number_on_node,node);

  //---------------------------------------------------
  // scan data file for correct location and trace   
 if(number_on_node!=0)
 {
  for(no=0; no<number_on_node; no++)
  { 
   // open output file 
   sprintf(string,"%s%d_%d_%d",output1,newG[no][0],newG[no][1],newG[no][2]);   
   if((out[no]=fopen(string,"w"))==NULL)
   {
    printf("Error 1003 opening file %s \n", string);
    fclose(out[no]);
    exit(0);
   }
  }

  // open data file - seismic traces
  sprintf(string,"%s%d",input1,node);
  if((in=fopen(string,"r"))==NULL)
  {
    printf("Error 1004 opening file %s \n", string);
    fclose(in);
    exit(0);
  }

  for(j=0; j<Max_Time; j++)
  {
  for(i=0; i<number_on_node; i++)
  {
  /// 6 column output
  //  fscanf(in,"%lf %lf %lf %lf %lf %lf\n",&dx,&dy,&dz,&vx,&vy,&vz);  
  //  fprintf(out[i],"%e %e %e %e %e %e\n",dx,dy,dz,vx,vy,vz); 

 /// 3 column output ascii
  //  fscanf(in,"%lf %lf %lf\n",&vx,&vy,&vz); 
  //  fprintf(out[i],"%e %e %e\n",vx,vy,vz);

/// 3 column output binary 
   // fscanf(in,"%lf %lf %lf\n",&vx,&vy,&vz);  
    bytes_read=fread(&aa, sizeof(double), 3, in);
    vx=aa[0];  vy=aa[1]; vz=aa[2];
    fprintf(out[i],"%e %e %e\n",vx,vy,vz);   
 
 
  }
  }

  fclose(in);
  for(no=0; no<number_on_node; no++)
  {
   fclose(out[no]);
  }
 } /// file is empty
} /// loop over nodes

 //system("find * -size 0 -exec rm {} \;");
 //system("ls");

}


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


/*int main (void)
{
	FILE *fp;
        char *path = "path\\to\\file";
	long size;

	fp = fopen(path, "r");

	if (fp)
	{
		fseek (fp, 0, SEEK_END);
		size = ftell(fp);
		printf("Size of the file in bytes: %lu\n", size);
		fclose(fp);
	}
	return 0;
}*/

