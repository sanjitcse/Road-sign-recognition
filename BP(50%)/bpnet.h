#define MAX_INPUT  300       
#define MAX_HIDDEN 200       
#define MAX_OUTPUT  20       
#define MAX_WEIGHT  5.0      
                            
#define MAX_LEARN  50

#define E  0.3             
#define learning_period  5        

double weight_in_hidden[MAX_INPUT][MAX_HIDDEN];
    
double weight_in_output[MAX_HIDDEN][MAX_OUTPUT];
    
double input_data[MAX_LEARN][MAX_INPUT];
double output_data[MAX_LEARN][MAX_OUTPUT];
    
int num_input, num_hidden, num_output;
    
int num_pattern;
    
double input_unit[MAX_INPUT];
double hidden_unit[MAX_HIDDEN];
double output_unit[MAX_OUTPUT];
int output[MAX_OUTPUT];

