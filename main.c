// Include stdio.h(Standard Input/Output)
#include <stdio.h>
// Libraries that include helper functions
#include <string.h>
#include <stdlib.h>

//include newline
#include "rmnewline.c"
//include the haversine formula
#include "haversine.c"

int validate_lat(double lat){
    if(lat < -90 || lat > 90){
        return 0;
    }else{
        return 1;
    }
}

int validate_lon(double lon){
    if(lon < -180 || lon > 180){
        return 0;
    }else{
        return 1;
    }
}


int main(int argc, char **argv){

    // Declaration

    // File to search in
    char *input_file = NULL;
    // Flag to check if input file was given
    int input_given =0;
    

    // Loop through arguments to get passed in options
    // Start on argv[1] because [0] is program name

    for(int i=1;i<=argc-1;i++){
        // Parse arguments
        if(argv[i][0]=='-' && strlen(argv[i])==2){
            switch(argv[i][1]){

                case 'i' :
                // if "-i" change input_file to filename passed in
                input_file = (char*)malloc(strlen(argv[i+1]));
                strcpy(input_file,argv[i+1]);
                input_given = 1;
                break;

                default:
                printf("--Error parsing arguments.--\n");
                exit(EXIT_FAILURE);
                break;
            }
        }
    }

    FILE *ifp;

    //Open input file
    //If file fails to open, output message and exit
    if(!input_given){
        ifp = stdin;
    }else if((ifp = fopen(input_file, "r")) == NULL){
        printf("Can't open input file: %s\n",input_file);
        exit(EXIT_FAILURE);
    }else{
        printf("Opened file: %s to read from\n",input_file);
    }

    // To simplify, max length for the description is 200 chars
    char description[200];

    char line[200];

    // Get the first line and put it in description
    // If input is taken from stdin, print a message to the user
    if(!input_given){
        printf("Enter the description for your route\n");
    }

    fgets(description, 200, ifp);

    double total = 0;

    // Temp char* for the tokens when using strtok
    char *token;

    // Flag for user input
    int cont_input =1;

    // Initialise latitudes and longitudes to values that aren't possible values
    // Latitude is never > 90 or < -90 and Longitude is never > 180 or < -180
    double lat1;
    double lon1;
    double lat2 = 111;
    double lon2 = 222;

    int counter = 1;

    if(!input_given){
        printf("Enter coordinates in the following format:\n");
        printf("\t[latitude],[longitude]\n");
        printf("After entering all the coordinated type --quit--\n");
    }

    while((cont_input == 1) && (fgets(line, 512, ifp) != NULL)){

        if(!strcmp(line,"--quit--")){
            // Change condition to beak out of the loop
            cont_input = 0;
        }else{

        // Get 1st token
        token = strtok(line, ",");

        // Turn it into a float
        lat1 = atof(token);


        // Get the other token
        token = strtok(NULL, ",");

        lon1 = atof(token);


        // Avoid calculating on the first iteration
        if(validate_lat(lat1) && validate_lat(lat2) && validate_lon(lon1) && validate_lon(lon2)){
            // printf("RUNNING WITH VALUES:\n");
            // printf("\t--LAT1:%f\n\t--LON1:%f\n\t--LAT2:%f\n\t--LON2:%f\n", lat1,lon1,lat2,lon2);
            total += dist(lat1,lon1,lat2,lon2);
            // printf("TOTALLING\n");
            // printf("NEW TOTAL: %f\n",total);
        }

        // Swap values
        lat2 = lat1;
        lon2 = lon1;

        // Increase number of inputs taken
        counter++;
    }

}


    /* Americans don't know kilometers */
    printf("dist: %.1f km (%.1f mi.)\n", total, total / 1.609344);

        //Close the files if still open.
    if(ifp){
        fclose(ifp);
    }

    if(input_file != NULL){
        free(input_file);
    }

    return 0;

}