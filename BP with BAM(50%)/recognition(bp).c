#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bpnet.h"

int sign_print[10][20];

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
    	FILE *fp,*fp1;            
    	int i,j,k,l;            
    	int num_data,num_pat;
		int input;
		int temp;
		int check,pat,count;
		int val[10][16];
		char sign[10][20];
		int pattern[10][4096];
		char in,num_sign;
		char file_sign[60][20];
			
		//num_pattern=1;
		num_input=17;
		num_hidden=9;
		num_output=6;
		
		fp=fopen("recognition_pattern.txt","r");
		
		fscanf(fp,"%d",&num_pat);
		
		for(i=0;i<num_pat;i++)
			{
				for(j=0;j<4096;j++)
					{
						fscanf(fp,"%d",&input);
						pattern[i][j]=input;
					}
			}
		fclose(fp);
		
		fp1=fopen("sign.txt","r");
		fscanf(fp1,"%d",&num_sign);
		
		for(i=0;i<num_sign;i++)
			{
				fscanf(fp,"%s",&file_sign[i]);
				for(j=0;j<6;j++)
					{
						fscanf(fp,"%d",&input);
						val[i][j]=input;
					}
			}
		fclose(fp1);
		
		fp=fopen("bp_recog_input.txt","r");
    	
		if (NULL == fp)
			{
        		printf("This file name does not exist\n");
        		exit(1);
    		}
		
		fscanf(fp,"%d",&num_pattern);
		
    	//fscanf(fp,"%d %d %d %d",&num_input,&num_hidden,&num_output,&num_pattern);
		
		//printf("Number of input units: %d\n",num_input-1);
		//printf("Number of hidden units: %d\n",num_hidden-1);
		//printf("Number of output units: %d\n",num_output);
		//printf("Number of Input pattern: %d\n",num_pattern);
		
		for(i=0;i<num_pattern;i++)
			{
				check=0;
				temp=0;
				
				printf("Input Pattern:\n");
				for(j=0;j<4096;j++)
					{	 
						printf("%d",pattern[i][j]);
						if((j+1)%64==0)
							printf("\n");
					}
				//printf("\n");
				
				printf("\nAssociated pattern %d: ",i+1);
				for(j=0;j<num_input-1;j++)
					{
						fscanf(fp,"%d",&input);
						
						printf("%d ",input);
						
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
				printf("\n");
				
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
						
						sign_print[i][j]=output[j];
						
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
				
				for(k=0;k<num_pattern;k++)
					{
						for(l=0;l<num_sign;l++)
							{
								for(j=0;j<6;j++)
									{
										if(sign_print[k][j]==val[l][j])
											{
												count=0;
											}
										else 
											{
												count=1;
												break;
											}
									}
							
								if(count==0)
									{
										pat=l;	  
									}
							//else 
								//pat=99;
							}
					//if(pat==99)
						//{
						//	  printf("Pattern is not matched\n");
					//	  }
					}
				
				(void)getchar();
				
				if(pat!=99) 
							{

								printf("The meaning of recognized sign is: %s",file_sign[pat]);
								printf("\n\n");
							}
			}
			
		fclose(fp);
	}

//void pattern_recog()
int main()
	{	 	 
		int i,j;
		float f;
		int input; 
		
		/////  Read weights from file //////
		
		FILE *fp;
		fp=fopen("bp_weights.txt","r");    
		
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
		
		//printf("\n");
		
		(void)getchar();
		
		return 0;
		
	}

