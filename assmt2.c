/*  C programming is fun.Engineering computation: Assignment 2
	Name: Xiaoqian Xie   StudentID: 709716   Date: 19/10/2015 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define NUM_OF_NOISE_SOURCE 99
/* define a type for every noise source */
typedef struct{
	char data_type;
	double x;
	double y;
	double noise_level;
} data_t;
/* define a type for lines, each line is consist of two points */
typedef struct{
	double x;
	double y;
} point_t;
typedef struct{
	point_t p1;
	point_t p2;
} line_t;

int inputdata(data_t *noisesource);
void stage_1(data_t *noisesource,double x,double y);
void stage_2(data_t *noisesource,int Lines);
void stage_3(data_t *noisesource);
void stage_4(data_t *noisesource);
void stage_5(data_t *noisesource,int Lines);
double distance(double x,double y,double m,double n);
double L2(double L1,double x,double y,double m,double n);
int lineIntersect(line_t l1, line_t l2);

int
main(int argc,char *argv[]){
	data_t NOISE_SOURCE[NUM_OF_NOISE_SOURCE];
	/* use Lines to count how many lines in the input file */
	int Lines;
	Lines = inputdata(NOISE_SOURCE);
	/* (0,0)is the original point */
	stage_1(NOISE_SOURCE,0,0);
	stage_2(NOISE_SOURCE,Lines);
	stage_3(NOISE_SOURCE);
	stage_4(NOISE_SOURCE);
	stage_5(NOISE_SOURCE,Lines);
return 0;
}
/* read the data from the .txt file, and store the data in an array of data_t,  
 * return how many lines of data are in the file. */
int inputdata(data_t noise_source[]){
	int i;
	i = 0;
	while(scanf(" %c %lf %lf %lf ",&noise_source[i].data_type,
		&noise_source[i].x,&noise_source[i].y,&noise_source[i].noise_level) 
		!= EOF){
		i++;
		}
	return i;
}
/* Stage 1 */
void stage_1(data_t noise_source[],double x,double y){
	int i,n;
	/* sum is the sum of 10^Li/10, L_sum is Lsum */
	double sum,L_sum;
	sum = 0;n=0;
	for(i=0;i<NUM_OF_NOISE_SOURCE;i++){
	if(noise_source[i].data_type == 'N'&& L2(noise_source[i].noise_level,
			noise_source[i].x,noise_source[i].y,x,y)!=0){
		sum = sum +  pow(10.0,L2(noise_source[i].noise_level,
			noise_source[i].x,noise_source[i].y,x,y)/10.0);
		/* count how many noise soureces in the input data */
		n++;
		}
	}
	L_sum = 10 * log10(sum);
	printf("Stage 1\n==========\n");	
	printf("Number of noise sources: %02d\n",n);
	printf("Noise level at (0000.0, 0000.0): %5.2f dB\n\n",L_sum);
}
/* Stage 2 */
void stage_2(data_t noise_source[],int lines){
	printf("Stage 2\n==========\n");
	int i,j;
	double sum;
	for(j=0;j<lines;j++){
/* calculate the Lsum from each observation point starts with "P" */		
		if(noise_source[j].data_type == 'P'){
			sum =0;
			for(i=0;i<lines;i++){
				if(noise_source[i].data_type == 'N'&&
					L2(noise_source[i].noise_level,noise_source[i].x,
				noise_source[i].y,noise_source[j].x,noise_source[j].y)!=0)
					{sum = sum +  pow(10.0,L2(noise_source[i].noise_level,
						noise_source[i].x,noise_source[i].y,noise_source[j].x,
						noise_source[j].y)/10.0);
				}
			}
		printf("Noise level at (%6.1f, %6.1f): %5.2f dB\n",noise_source[j].x,
			noise_source[j].y,10 * log10(sum));
		}
	}
	printf("\n");
}
/* Stage 3 */
void stage_3(data_t noise_source[]){
	int i,j,k,m,n;
	k=0;n=0;
	for(i=100;i<=7700;i=i+100){
		for(j=100;j<=7700;j=j+100){
/* use n count how many points are sampled */		
			n++;
		double sum,L_sum;
		sum = 0;
		for(m=0;m<NUM_OF_NOISE_SOURCE;m++){
				if(noise_source[m].data_type == 'N'&& 
				L2(noise_source[m].noise_level,noise_source[m].x,
				noise_source[m].y,i,j)!=0){sum = sum +  
				pow(10.0,L2(noise_source[m].noise_level,noise_source[m].x
				,noise_source[m].y,i,j)/10.0);	
				}
			}
	L_sum = 10 * log10(sum);
/* use k count how many points are >= 86dB */
	if(L_sum >= 85){
		k++;
			}
		}
	}
	printf("Stage 3\n==========\n");
	printf("%d points sampled\n",n);
	printf("%04d points (%05.2f%%) have noise level >= 85 dB\n\n",k,
	(double)k/n*100);
}
/* Stage 4 */
void stage_4(data_t noise_source[]){
	printf("Stage 4\n==========\n");
	int i,j,m;
	double sum,L_sum;
	for(i=7700;i>0;i=i-200){
		for(j=50;j<=7800;j=j+100){
		sum = 0;
			for(m=0;m<NUM_OF_NOISE_SOURCE;m++){
					if(noise_source[m].data_type == 'N'&& 
					L2(noise_source[m].noise_level,noise_source[m].x,
					noise_source[m].y,i,j)!=0){sum = sum + 
					pow(10.0,L2(noise_source[m].noise_level,noise_source[m].x,
					noise_source[m].y,j,i)/10.0);	
					}
				}
			L_sum = 10 * log10(sum);
			if(L_sum < 20){
							printf("-");
				}else if(L_sum < 30){
							printf(" ");
				}else if(L_sum < 40.0){
							printf("4");
				}else if(L_sum < 50){
							printf(" ");
				}else if(L_sum < 60){
							printf("6");
				}else if(L_sum < 70){
							printf(" ");
				}else if(L_sum < 80){
							printf("8");
				}else if(L_sum < 85){
							printf(" ");
				}else {
							printf("+");
				}
		}
		printf("\n");
	}
	printf("\n");
}
/* Stage 5 */
void stage_5(data_t noise_source[],int Lines){
	printf("Stage 5\n==========\n");
	line_t LINES[NUM_OF_NOISE_SOURCE];
	line_t line0;
/* (X,Y) is the centriod of the polygon boundary points */
	double X=0,Y=0;
	int a,b,c;
	int i,j=0,k;
/* store the data of 4 points started with "V" in 4 line_t type variables */
	for(i=0;i<Lines;i++){
		if(noise_source[i].data_type == 'V'&& (i!= Lines)){
		LINES[j].p1.x=noise_source[i].x;LINES[j].p1.y=noise_source[i].y;
		LINES[j].p2.x=noise_source[i+1].x;LINES[j].p2.y=noise_source[i+1].y;
			j++;
		}
	}
/* the line betweent last point to the first point */ 	
	LINES[j+1].p1.x=noise_source[i].x;LINES[j+1].p1.y=noise_source[i].y;
	LINES[j+1].p1.x=noise_source[0].x;LINES[j+1].p1.y=noise_source[0].y;
/* to find the centriod of the polygon boundary points */
	for(k=0;k<=j;k++){
		X= X + LINES[k].p1.x;
		Y= Y + LINES[k].p1.y;
	}
	line0.p1.x = X/j;
	line0.p1.y = Y/j;
/* draw the plot */
	double sum,L_sum;
	for(a=7700;a>0;a=a-200){
		for(b=50;b<=7800;b=b+100){
			sum = 0;
				for(c=0;c<NUM_OF_NOISE_SOURCE;c++){
						if(noise_source[c].data_type == 'N'&& 
						L2(noise_source[c].noise_level,noise_source[c].x,
						noise_source[c].y,i,j)!=0){sum = sum + 
						pow(10.0,L2(noise_source[c].noise_level,
						noise_source[c].x,noise_source[c].y,b,a)/10.0);	
						}
					}
	L_sum = 10 * log10(sum);
/* p2 of the line0 */	
	line0.p2.x = b;
	line0.p2.y = a;
/* if the lines between the test point and the centriod of the polygon boundary
 * points intersect any of 4 boundaries,print "#". else print the plot the same 
 * as stage 4 */
	if((lineIntersect(line0 , LINES[0]) || lineIntersect(line0 , LINES[1]) || 
	lineIntersect(line0 , LINES[2]) || lineIntersect(line0 , LINES[3]))!=0)
						{
						printf("#");
	}else if(L_sum < 20){
						printf("-");
			}else if(L_sum < 30){
						printf(" ");
			}else if(L_sum < 40.0){
						printf("4");
			}else if(L_sum < 50){
						printf(" ");
			}else if(L_sum < 60){
						printf("6");
			}else if(L_sum < 70){
						printf(" ");
			}else if(L_sum < 80){
						printf("8");
			}else if(L_sum < 85){
						printf(" ");
			}else {
						printf("+");
			}
		}
		printf("\n");
	}
	
}
/* calculate the distance between to points (x,y) and (m,n) */
double distance(double x,double y,double m,double n){
	return sqrt((x - m)*(x - m)+(y - n)*(y - n));
}
/* calculate the noise level measured from (m,n) */
double L2(double L1,double x,double y,double m,double n){
  double L2,r2;
  r2 = distance(x,y,m,n);
  L2 = L1 + 20 * log10(1/r2);
  return L2;
}

/* =============================================================== */

/* This function was adapted by Alistair Moffat in 2012 from 
 * http://local.wasp.uwa.edu.au/~pbourke/geometry/lineline2d/pdb.c
 * (no longer available at that URL in 2013)
 * and was written in the first instance by Paul Bourke
 *
 * Modified for use in a different assignment previously  by:
 *   . changing the argument type to two structs type line_t
 *   . making sure result is TRUE if an endpoint is on the other line
 */
#define TRUE 1
#define FALSE 0
#define EPS (1e-06)
#define ABS(x) (fabs(x))

int lineIntersect(line_t l1, line_t l2) {
   double x1=l1.p1.x, y1=l1.p1.y,
   	  x2=l1.p2.x, y2=l1.p2.y,
   	  x3=l2.p1.x, y3=l2.p1.y,
   	  x4=l2.p2.x, y4=l2.p2.y;
   double mua,mub;
   double denom,numera,numerb;

   denom  = (y4-y3) * (x2-x1) - (x4-x3) * (y2-y1);
   numera = (x4-x3) * (y1-y3) - (y4-y3) * (x1-x3);
   numerb = (x2-x1) * (y1-y3) - (y2-y1) * (x1-x3);

   /* Are the line coincident? */
   if (ABS(numera) < EPS && ABS(numerb) < EPS && ABS(denom) < EPS) {
      return(TRUE);
   }

   /* Are the line parallel */
   if (ABS(denom) < EPS) {
      return(FALSE);
   }

   /* Is the intersection along the the segments */
   mua = numera / denom;
   mub = numerb / denom;
   /* AM - use equality here so that "on the end" is not an
    * intersection; use strict inequality if "touching at end" is an
    * intersection */
   if (mua < 0 || mua > 1 || mub < 0 || mub > 1) {
      return(FALSE);
   }
   return(TRUE);
}
