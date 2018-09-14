/***********************************************************************************************************************************************************
Filename:			ass1.cpp																															   *
Version: 			1.0																																	   *
Author:				Niladri Sengupta																													   *
Student No:  		040777969																															   *
Course Name/Number:	CST 8233 (Numerical Computing)																										   *
Lab Sect: 			302																																	   *
Assignment #:		01																																	   *
Assignment name:	Ring Tone																															   *
Due Date:			October 16, 2016																													   *
Submission Date:	October 16, 2016																													   *
Professor:			Andrew Tyler																														   *
Purpose:			To understand and calculate the MacLaurin Series values for the function ((1 - (exp^(-t))) * sin(t)), where t is the number of seconds *
for the Ring Tone. Calculating using the math.h and the 5 non-zero equations to compare the relative erros.												   *
Note:				This program was made in Visual Studio 2013. For optimal performance, run it in Visual Studio										   *
************************************************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS //To avoid any sort of warnings (scanf())
#include <stdio.h>
#include <math.h>

/*UNCHECK THE LINE BELOW IF YOU HAVE THE MEMORY CHECK PLUG-IN FOR VISUAL STUDIO 2013*/
//#include <vld.hdeclaration

/*Global in > order to use the function anywhere in the program*/
int calculate_non_zero_terms(void);


/********************************************************************************************
* Function Name:	main																	*
* Purpose:			To give the user option to either calculate the MacLaurin series or quit*
* In Parameters:	none																	*
* Out Parameters:	none																	*
* Version:			1.0																		*
* Author:			Niladri Sengupta														*
*********************************************************************************************/
int main(void) {
	bool loop = true;
	char choice; /*char choice for switch case*/

	while (loop) {
		printf ("Evaluate the Taylor Series approximation to (1-exp(-t))*sin(t)");
		printf ("\n\n1. Evaluate the series\n");
		printf ("2. quit\n");
		scanf("%c", &choice);
		fflush(stdin);
		/*Switch case for calculating the MacLaurin Series or quit*/
		switch (choice) {
		case '1':
			calculate_non_zero_terms();
			break;
		case '2':
			loop = false;
			break;
		default:
			printf("\nPlease enter one of the two options\n");
			break;
		} 
	}
	return 0;
}

/****************************************************************************************************************
* Function Name:	calculate_non_zero_terms																	*
* Purpose:			To calculate the given MacLaurin equation with relative erroes and printing out the values	*
* In Parameters:	void																						*
* Out Parameters:	Returning 1 if successful																	*
* Version:			1.0																							*
* Author:			Niladri Sengupta																			*
*****************************************************************************************************************/
int calculate_non_zero_terms(void) {
	/*Declarations for all variables for keeping track*/
	int i, num_of_terms = 0; int counter = 0;
	/*Declarations for all variables for calculation and storage*/
	double x = 0.0; double t = 0.0; double truncation = 0.0; double series_value = 0.0; double exact_value = 0.0; double relative_series_error = 0.0; double relative_exact_error = 0.0;
	double non_zero_terms[6] = { 0.0 };
	/*Inputs*/
	printf("Evaluating the series\n");
	printf("Please enter the number of non-zero terms in the series (1, 2, 3 or 4): ");
	scanf("%d", &num_of_terms); //get number of terms from user
	fflush(stdin);
	/*Verify the validity of input for number of terms, if not valid return to main*/
	if ((num_of_terms <= 0) || (num_of_terms > 4)) {
		printf("%d is not a valid input\n", num_of_terms);
		return 1;
	}
	printf("Please enter the range of t to evaluate in equal in 10 increments (0.0 < t < +1.0): ");
	scanf("%lf", &t);// get the time from user
	fflush(stdin);

	/*Verify the validity of input for time, if not valid return to main*/
	if ((t <= 0.0) || (t > 1.0)) {
		printf("%f is not a valid input.\n", t);
		return 1;
	}

	printf("\nMACLAURIN SERIES\n");
	printf("  t          F(t)Series     F1(t)Exact        %%RExactE      %%RSerE\n");
	/*A loop of 10 calculating the non-zero elements, printing values and errors 10 times*/
	for (counter = 0; counter <= 10; counter++) {
		/*Storing the first five non-zero elements of the equation ((1 - (exp(-x))) * sin(x)) using the following formulae (series)*/
		non_zero_terms[0] =           (x * x);
		non_zero_terms[1] =         (x * x * x) / (-2.0f);
		non_zero_terms[2] =     (x * x * x * x * x) / (24.0f);
		non_zero_terms[3] =   (x * x * x * x * x * x) / (-90.0f);
		non_zero_terms[4] = (x * x * x * x * x * x * x) / (720.0f);

		/*Calculating the sum of the series in order to find the estimated MacLaurin series values*/
		for (i = 0; i <num_of_terms; i++) { 
			series_value += non_zero_terms[i];
		}
		/************************************************************************************
		 * The following equations were provided by Professor Andrew Tyler:					*
		 * truncation = last term of the series												*
		 * % Relative Exact Error (%RExactE) =100*(exact value – series value)/exact value  *
		 * % Relative Series Error (%RSerE) =100*first truncated term/series value			*
		 ************************************************************************************/

		truncation = non_zero_terms[num_of_terms]; /*Truncation = the last term*/
		exact_value = ((1 - (exp(-x))) * sin(x)); /*Calculating the exact value of the series using the math.h library*/
		/*Making sure that the exact value is not 0, otherwise division will not be possible*/
		if (exact_value == 0){
			exact_value = 1;
		}
		relative_exact_error = 100 * ((exact_value - series_value) / exact_value); /* Relative Exact Error*/
		relative_series_error = 100 * (truncation / series_value); /* Relative Series Error*/
		/* Setting the Relative Series Error if the series_value = 0 because it would be divided by 0 regardless*/
		if (series_value == 0){
			relative_series_error = 0;
		}
		/* After finishing the calculation for this cycle, printing the values accordingly*/
		printf("%.3e   %.5e   %.5e   %.5e   %.5e\n", x, series_value, exact_value, relative_exact_error, relative_series_error); /* print calculated values */
		x = (t * (counter + 1)) / 10.0; /* Increases in 10% - Time*/
		series_value = 0; /* Resetting the series value*/
	}
	printf("\n");
	return 1;
}
