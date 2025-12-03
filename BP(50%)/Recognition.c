#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bpnet.h"

void calculation()
	{
		int i,j;
		double sum;
		for ( i = 0; i < num_hidden - 1; i ++ )
			{
        		sum = 0.0;
        		for ( j = 0; j < num_input; j ++ )
					{
            			sum = sum + input_unit[j] * weight_in_hidden[j][i];
					}
        		hidden_unit[i] = 1.0 / ( 1.0 + exp( - sum ) );
    		}
    	input_unit[num_input - 1] = 1.0; /* Threshold set unit */
  
    	for ( i = 0; i < num_output; i ++ )
			{
        		sum = 0.0;
        		for ( j = 0; j < num_hidden - 1; j ++ )
					{
            			sum = sum + hidden_unit[j] * weight_in_output[j][i];
					}
        		output_unit[i] = 1.0 / ( 1.0 + exp( - sum ) );
    		}
    	hidden_unit[num_hidden - 1] = 1.0; /* Threshold set unit */	   
	}

void pattern_recognition()
	{
    	int num;             
    	FILE *fp;            
    	int i, j;            
    	int num_data;
		int input;
		int temp;
		int check;        
   		
		fp=fopen("input_pattern.txt","r");
    	
		if (NULL == fp)
			{
        		printf("This file name does not exist\n");
        		exit(1);
    		}
			
    	fscanf(fp,"%d %d %d %d",&num_input,&num_hidden,&num_output,&num_pattern);
		
		printf("Number of input units: %d\n",num_input-1);
		printf("Number of hidden units: %d\n",num_hidden-1);
		printf("Number of output units: %d\n",num_output);
		printf("Number of Input pattern: %d\n",num_pattern);
		
		for(i=0;i<num_pattern;i++)
			{
				check=0;
				temp=0;
				
				printf("\nInput pattern %d: ",i+1);
				for(j=0;j<num_input-1;j++)
					{
						fscanf(fp,"%d",&input);
						
						printf("%d ",input);
						
						if(j==15 || j==31 || j==47 || j==63 || j==79 || j==95 || j==111 || j==127 || j==143 || j==159 || j==175 || j==191 || j==207 || j==223 || j==239 || j==255)
							printf("\n\t\t ");
						
						if(input==0)
							{
								input_unit[j]=0.1;
							}
						else 
							{
								input_unit[j]=0.9;
							}	 
					}
				input_unit[num_input-1]=1.0;
				
				calculation();
				
				printf("\nOutput: ");
				
				for(j=0;j<num_output;j++)
					{
            			if(output_unit[j]>=0.7) 
							{
								//printf("%f\n",output_unit[j]);
								output[j]=1;
							}
            			else if(output_unit[j]<=0.2)
							{
								//printf("%f\n",output_unit[j]);
								output[j]=0;
							}	 	 
            			else if(output_unit[j]<=0.4 && output_unit[j]>0.2)
							{
								//printf("%f\n",output_unit[j]);
								output[j]=0;
								temp=temp+1;
							}
						else if(output_unit[j]>=0.6 && output_unit[j]<0.7)
							{
								//printf("%f\n",output_unit[j]);
								output[j]=1;
								temp=temp+1;
							}
						else 
							{
								//printf("%f\n",output_unit[j]);
								printf("Input pattern....unable to recognize\n");
								check=1;
								//break;
							} 
						
						//printf("%f ",output[j]); 
        			}
				
				if(check==0)
					{
						if(temp>=1)
							{
								printf("Pattern is closely similar to: ");
								goto show;;
							}
						else 
							{
								goto show;
							}
				
						show: 
							for(j=0;j<num_output;j++)
								{
									printf("%d",output[j]);
								}
					}
				
				(void)getchar();
			}	 
		fclose(fp);
	}

int main()
	{	 	 
		int i,j;
		float f;
		
		/////  Read weights from file //////
		
		FILE *fp;
		fp=fopen("weights.txt","r");    
		
		fscanf(fp,"%d %d %d",&num_input,&num_hidden,&num_output);
		
		for ( i=0; i<num_input; i++ )
			{
        		for ( j=0; j<num_hidden; j++ )
					{
            			fscanf( fp,"%f",&f );    
						weight_in_hidden[i][j] = f;
        			}
			}
			
    	for ( i=0; i<num_hidden; i++ )
			{
        		for ( j=0; j<num_output; j++ )
					{
            			fscanf( fp,"%f",&f );    
						weight_in_output[i][j] = f;
        			}
			}
    	fclose(fp);
		
		////  Recognize Unknown pattern  ////
		
		pattern_recognition();
			
		return 0;
	}

