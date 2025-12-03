#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bpnet.h"


double random_double( double n )
	{
    	return (double)rand( ) / ( (double)RAND_MAX + 1.0 ) * n;
	}

void weights_initialization()
	{
		int i,j,seed;
		
		printf("Enter the seed value (positive integer): ");
		scanf("%d",&seed);
		
		if(seed<1)
			{
				seed=1;
			}
		
		srand(seed);
		
		//// Initial weights in hidden layer ////
		for(i=0;i<num_input;i++)
			{
				for(j=0;j<num_hidden;j++)
					{
						weight_in_hidden[i][j] = 2.0 * MAX_WEIGHT * random_double( 1.0 ) - MAX_WEIGHT;
					}
			}
			
		//// Initial weights in output layer  ////
		for(i=0;i<num_hidden;i++)
			{
				for(j=0;j<num_output;j++)
					{
						weight_in_output[i][j] = 2.0 * MAX_WEIGHT * random_double( 1.0 ) - MAX_WEIGHT;
					}
			}
	}
	
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

double error_of_NN( )
	{
    	int i, j;          
    	double err;   

    	double error = 0.0;
    
    	for ( i = 0; i < num_pattern; i ++ )
			{
        		for ( j = 0; j < num_input - 1; j ++ )
					{
            			if ( input_data[i][j] < 0.5 )
							{
                				input_unit[j] = 0.1;
							}
            			else 
							{
								input_unit[j] = 0.9;
							}
        			}
        		input_unit[num_input - 1] = 1.0; /* Set threshold unit */
		
        		calculation( );
				/* The output error margin is calculated */ 
        
				for ( j = 0; j < num_output; j ++ )
					{
            			err = output_data[i][j] - output_unit[j];
            			error = error + err * err;  /* The second power of the error margin accumulates */
        			}
    		}
    	error = error / (double)num_pattern; /* The error margin is leveled by the number of data */
    	return( error );
	}
	
void save_weights()
	{
		FILE *fp;
		int i,j;
		
		fp=fopen("bp_weights.txt","w");
		
		fprintf( fp, "%d %d %d\n", num_input, num_hidden, num_output );
    	
		for ( i = 0; i < num_input; i ++ )
			{
        		for ( j = 0; j < num_hidden; j ++ )
					{
            			fprintf( fp, "%f\n", weight_in_hidden[i][j] );
					}
			}
			
    	for ( i = 0; i < num_hidden; i ++ )
			{
        		for ( j = 0; j < num_output; j ++ )
					{
            			fprintf( fp, "%f\n", weight_in_output[i][j] );
					}
			}
    
		printf("Data has been successfully written in file (weights.txt)\n");
		
		fclose(fp);
	} 

//void training()
int main()
	{
		
		int counter, learn_num;  
    	int learning_time;     
    	double acceptable_error;  
    	double error;
    	int i, j, k;   
    
    	double delta_W, output_value, yin, hid_value;
    	double data_hidden[MAX_HIDDEN][MAX_OUTPUT], data_in;
    	double sum;
		int input,output;
	
		/////  Read training inputs from file //////
		
		FILE *fp,*fp1;
		fp=fopen("bp_input.txt","r");    	  // Training input file name: training_pattern.txt
		fp1=fopen("iterationVSerror.txt","w");
		
		if ( NULL == fp )
			{
        		printf("This file name does not exist\n");
        		exit(1);
    		}
			
		num_input=17;
		num_hidden=9;
		num_output=6;
		
		fscanf(fp,"%d",&num_pattern);
		
		//printf("Number of input units: %d\n",num_input-1);
		//printf("Number of hidden units: %d\n",num_hidden-1);
		//printf("Number of output units: %d\n",num_output);
		//printf("Number of learning pattern: %d\n",num_pattern);
		
		for(i=0;i<num_pattern;i++)
			{
				printf("Input pattern: ");
				for(j=0;j<num_input-1;j++)
					{
						fscanf(fp,"%d",&input);
						input_data[i][j]=input;
						printf("%d ",input);
					}
				printf("\nDesired Output: ");
				for(j=0;j<num_output;j++)
					{
						fscanf(fp,"%d",&output);
						output_data[i][j]=output;
						printf("%d ",output);
					}
				printf("\n");
			}
			
		printf("\n");
		
		fclose(fp);
		
		/////  Initialize weights  //////
		
		weights_initialization();   // Method of initializing weights of both hidden and output layer
		
		////   Learning   ////
		
		step1:
		
		printf("Allowable error margin (From 0 to 0.01): ");
		scanf("%lf",&acceptable_error);	   	   
		
		if(acceptable_error<0 || acceptable_error>0.01)
			{
				goto step1;
			}
		
		learning_time = 1;    
		counter = 0;    
		learn_num = 0;
		
		do 
			{
				for ( i=0; i<num_input-1; i++ )
					{
            			input_unit[i] = input_data[learn_num][i];
					}
				input_unit [num_input-1] = 1.0; 
				
				/// Calculate hidden and output layer unit /// 

				calculation();
				
				/// Update weights of both hidden and output layer ///
				
				for (j = 0; j < num_hidden; j ++ )
					{
            			for (i = 0; i < num_output; i ++ )
							{               
                				output_value = output_unit[i];   
                				yin  = output_data[learn_num][i]; 
								
                				data_hidden[j][i] = ( output_value - yin ) * output_value * ( 1.0 - output_value );
								
                				hid_value = hidden_unit[j];
								
                				delta_W = - E * data_hidden[j][i] * hid_value;
								
                				/// Update weights ///
               					weight_in_output[j][i] = weight_in_output[j][i] + delta_W;
            				}
        			}
        	
        		for ( j = 0; j < num_input; j ++ )
					{
            			for ( i = 0; i < num_hidden; i ++ )
							{
                				sum = 0.0;
								
                				for ( k = 0; k < num_output; k ++ )
									{
                    					sum = sum + weight_in_output[i][k] * data_hidden[i][k];
									}
									
                				data_in = sum * hidden_unit[i] * ( 1.0 - hidden_unit[i] );
								
                				delta_W = - E * data_in * input_unit[j];
								
                				/// Update weights ///
                				weight_in_hidden[j][i] = weight_in_hidden[j][i] + delta_W;
            				}
        			}
					
				error = error_of_NN();
				
				learning_time++;
				counter++;
				
				printf("No.%d : error = %f\n", learning_time, error);
				
				fprintf(fp1,"%d %f\n",learning_time,error);
				
				if(counter>learning_period)
					{
						counter=0;
						learn_num++;
						
						if(learn_num>num_pattern)
							{
								learn_num=0;
							}
					}
				
				//if(learning_time > 160000)
					//break;
											
			}while(error > acceptable_error || learning_time < 2000);
		
		save_weights();
		
		fclose(fp1);
		
		return 0;
			
	}

