#include<stdio.h>
//#include "recognition(bp).c"

int main()
	{
		FILE *fp,*fp1;
		int i,j,k;
		int sum,temp,value;
		int num_pattern;
		
		int input,weight[16][4096],pattern[2][4096],output[2][16];
		
		fp=fopen("bam_weights.txt","r");
		
		for(i=0;i<16;i++)
			{
				for(j=0;j<4096;j++)
					{
						fscanf(fp,"%d",&input);
						weight[i][j]=input;
					}
			}
		fclose(fp);
		
		fp=fopen("recognition_pattern.txt","r");
		
		fscanf(fp,"%d",&num_pattern);
		
		printf("Total Input pattern: %d\n",num_pattern);
		
		for(i=0;i<num_pattern;i++)
			{
				for(j=0;j<4096;j++)
					{
						fscanf(fp,"%d",&input);
						pattern[i][j]=input;
					}
			}
		fclose(fp);
		
		fp1=fopen("bp_recog_input.txt","w");
		fprintf(fp1,"%d",num_pattern);
		fprintf(fp1,"\n");
		
		for(i=0;i<num_pattern;i++)
			{	 
				for(j=0;j<16;j++)
					{
						sum=0;
						for(k=0;k<4096;k++)
							{
								sum=sum+(weight[j][k]*pattern[i][k]);
							}
						output[i][j]=sum;  	   
					}
		
				for(j=0;j<16;j++)
					{
						temp=output[i][j];
						
						if(j==4 || j==8 || j==12)
							{
								fprintf(fp1,"\n");
							}
						
						if(temp>0)
							{
								value=1;
								fprintf(fp1,"%d ",value);
							}
						if(temp<0)
							{
								value=0;
								fprintf(fp1,"%d ",value);
							}	 	 
					}
					
					fprintf(fp1,"\n\n");
			}
			
		fclose(fp1);
		
		//pattern_recog();
		
		return 0;
	}

