#include<stdio.h>
#include<string.h>
//#include "training(bp).c"

int weights[60][4096][20];

int main()
	{
		FILE *fp;
		int i,j,k;
		char sign[60][20],file_sign[60][20];
		int input_pattern[60][4200],output_pattern[60][20],out_value[60][6];
		int input,num_pattern,product,sum,output,num_sign,out;
		
		int weight_matrix[4200][20],weight_trans_matrix[20][4200];
		
		fp=fopen("training_input.txt","r");
		
		fscanf(fp,"%d",&num_pattern);
		printf("Total Pattern: %d\n",num_pattern);
		
		for(i=0;i<num_pattern;i++)
			{
				fscanf(fp,"%s",&sign[i]);
				
				printf("Input Pattern %d: ",i+1);
				for(j=0;j<4096;j++)
					{
						fscanf(fp,"%d",&input);
						printf("%d ",input);
						
						if(input==0)
							input_pattern[i][j]=-1;
						else 
							input_pattern[i][j]=input;
					}
				
				printf("\nDesired Output Pattern: ");	 
				for(j=0;j<16;j++)
					{
						fscanf(fp,"%d",&input);
						printf("%d ",input);
						
						if(input==0)
							output_pattern[i][j]=-1;
						else 
							output_pattern[i][j]=input;
					}
				printf("\n");
			}
		fclose(fp);
		
		printf("\nIn Bipolar Form\n");
		
		for(i=0;i<num_pattern;i++)
			{
				printf("Input Pattern %d: ",i+1);
				for(j=0;j<4096;j++)
					{
						printf("%d ",input_pattern[i][j]);
					}
				printf("\nDesired Output Pattern: ");
				for(j=0;j<16;j++)
					{
						printf("%d ",output_pattern[i][j]);
					}
				printf("\n");
			}
		
		printf("\nWeight matrix\n");
		for(i=0;i<num_pattern;i++)
			{
				for(j=0;j<4096;j++)
					{
						for(k=0;k<16;k++)
							{
								product=input_pattern[i][j]*output_pattern[i][k];
								weights[i][j][k]=product;
								//printf("%d ",product);
							}
						//printf("\n");
					}
				//printf("\n");
			}
		
		for(i=0;i<4096;i++)
			{
				for(j=0;j<16;j++)
					{
						sum=0;
						for(k=0;k<num_pattern;k++)
							{
								sum=sum+weights[k][i][j];
							}
						printf("%d ",sum);
						weight_matrix[i][j]=sum;
					}
				printf("\n");
			}
			
		fp=fopen("bam_weights.txt","w");
		
		for(i=0;i<16;i++)
			{
				for(j=0;j<4096;j++)
					{
						weight_trans_matrix[i][j]=weight_matrix[j][i];
						fprintf(fp,"%d ",weight_trans_matrix[i][j]);
					}
				fprintf(fp,"\n");
			}
		fclose(fp);
		
		//for(i=0;i<256;i++)
		
		fp=fopen("sign.txt","r");
		
		fscanf(fp,"%d",&num_sign);
		
		for(i=0;i<num_sign;i++)
			{
				fscanf(fp,"%s",&file_sign[i]);
				for(j=0;j<6;j++)
					{
						fscanf(fp,"%d",&out);
						out_value[i][j]=out;
					}
			}
			
		fclose(fp);
		
		fp=fopen("bp_input.txt","w");
		
		fprintf(fp,"%d",num_pattern);
		fprintf(fp,"\n");
			
		for(i=0;i<num_pattern;i++)
			{
				printf("\nAssociated output for pattern (%d)\n",i+1);
				
				for(j=0;j<16;j++)
					{
						output=0;
						for(k=0;k<4096;k++)
							{
								output=output+weight_trans_matrix[j][k]*input_pattern[i][k];
							}
						
						if(output<0)
							output=0;
						else 
							output=1;
						
						if(j==4 || j==8 || j==12)
							{
								fprintf(fp,"\n");
							}
						
						printf("%d ",output);
						fprintf(fp,"%d ",output);
					}
					
				for(j=0;j<num_sign;j++)
							{
								if(strcmp(sign[i],file_sign[j])==0)
									{
										for(k=0;k<6;k++)
												fprintf(fp,"%d ",out_value[j][k]);
									}
							}
				printf("\n");
				fprintf(fp,"\n\n");
			}
		fclose(fp);
			
		//training();
	
		return 0;
	}

