#include<stdio.h>

int main()
	{
		FILE *fp,*fp1;
		int i,j,p,q,count,pixel[32],k,max,input[512],matra_detect,temp=0;
		
		fp=fopen("nouka.txt","r");
		fp1=fopen("nou.txt","w");
		
		for(i=0;i<1;i++)
			{
				for(j=0;j<512;j++)
					{
						fscanf(fp,"%d",&p);
						q=p;
						
						if(q!=0)
							{
								q=1;
							}
							
						fprintf(fp1,"%d ",q);
						
						if((j+1)%32==0)
							{
								fprintf(fp1,"\n");
							}
					}
				fprintf(fp1,"\n");
			}
			
		fclose(fp); 
		fclose(fp1);
		
		fp=fopen("nou.txt","r");
		
		count=0;
		j=0;
		max=0;
		
		for(i=1;i<=512;i++)
			{
				fscanf(fp,"%d",&p);
				q=p;
				input[i]=p;
				if(q==0)
					{
						count++;
					}
				if(i%32==0)
					{
						pixel[j]=count;
						j++;
						count=0;
					}
			}
			
		printf("Line\tPixels\tHistogram\n");
			
		for(i=0;i<j;i++)
			{
				printf("%d",i+1);
				if(i<10)
					{
						printf(" \t");	  
					}
				else 
					printf("\t");
					
				printf("%d",pixel[i]);
				if(pixel[i]<10)
					{
						printf(" \t");
					}
				else 
					{
						printf("\t");
					}
				
				for(k=0;k<pixel[i];k++)
					{
						printf("*");
					}
				printf("\n");
				
				if(pixel[i]>max)
					{
						max=pixel[i];
					}
			}
		
		//printf("\nMax: %d\n",max);
		
		for(i=0;i<j;i++)
			{
				if(pixel[i]==max)
					{
						matra_detect=i+1;
						printf("\nMatra is detected in line %d\n",matra_detect);
						break;
					}
			}
		
		fclose(fp);
		
		fp=fopen("char_seg.pgm","w");
		
		fprintf(fp,"P2\n32 16\n1\n");
		
		for(i=1;i<=512;i++)
			{
				temp=(matra_detect-1)*32;
				if(i>temp && i<(temp+33))
					{
						if(input[i]==0)
							{
								fprintf(fp,"1 ");
							}	 
						else 
							fprintf(fp,"%d ",input[i]);	 
					}
				else 
					fprintf(fp,"%d ",input[i]);
				
				if(i%32==0)
					fprintf(fp,"\n");	
			}
		
		fclose(fp);
		
		return 0;
	}

