#include<stdio.h>

int main()
	{
		FILE *fp,*fp1;
		int i,j,p,q;
		
		fp=fopen("input.txt","r");
		fp1=fopen("EQUI.txt","w");
		
		fprintf(fp1,"\n");
		
		//for(i=0;i<4;i++)
		//	  {
				for(j=0;j<6576;j++)
					{
						fscanf(fp,"%d",&p);
						q=p;
						
						if(q<140)
							{
								q=0;
							}
						else
							{
								q=255;
							}
							
							
						fprintf(fp1,"%d ",q);
						
						if((j+1)%64==0)
							{
								fprintf(fp1,"\n");
							}
					}
				fprintf(fp1,"\n");
		//	  }
			
		fclose(fp); 
		fclose(fp1);
		return 0;
	}

