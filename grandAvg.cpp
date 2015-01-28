#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

#define rows 20     // define a constant for students
#define columns 8   // define a constant for quizzes

int grades[rows][columns];  // declare a global array

// Prototypes
double avgCol(int scores[][columns], int c);
double grandAvgCol (int scores[][columns]);
double avgRows(int scores[][columns], int r);
double grandAvgRows(int scores[][columns]);
int *insertionSort(int arr[], int length);
double studentAvgDrop(int scores[][columns], int r);
double grandAvgDropRows(int scores[][columns]);
double quizAvgDrop(int scores[][columns], int c);
double grandAvgDropCols(int scores[][columns]);
void printArray(int scores[][columns]);

int main ()
{
    ifstream my_file("E:\\grades.csv"); // get the input file
    string line; // place holder for the string; hold the rows
 
   
    int row = 0;	// set rows to zero
    int column = 0; // set columns to zero

  
  while (getline(my_file, line)) // this while loop takes the source file; this one gives a line
  {             
    stringstream linestream(line); // convert
    string item_string; // convert
  
    column = 0; // set column to zero each time to loop again
  
    while (getline(linestream, item_string, ','))  // this while loop gives a number
    {
       int number = atoi(item_string.c_str()); // atoi function converts the array from a string to an integer
       grades[row][column] = number; //  place value number into the array
       column++;  // left to right  top to bottom
    }

     row++;
  }
	
	printArray(grades);  // final print

	system ("pause");
	return 0;
}

/*
	This function calculates the average for every quiz (straight column average) 
	Precondition: all the elements of the array have been filled
	Post condition: the average of these elements is computed and returned
*/

double avgCol(int scores[][columns], int c)
{
    // Declare variables
    int j;
    double avg;
    double sum = 0;  // initialize sum
   
    for (j = 0; j < rows; j++) // read every row in each column
    {
       sum += grades[j][c]; 
	     avg = (double) sum / rows; // calculate average for each quiz 
	  }
        
       return avg; 
}
   
/*
     This function calculates the grand average of all quizzes (columns)
     (The average of all the averages)
     Precondition: all the averages of avgCol are computed and pass to this function
     Post condition: the average of these elements is computed and returned
*/
  
double grandAvgCol (int scores[][columns])
{
  double grandAvg = 0; // initialize grandAvg
	
	for (int i = 0; i < columns; i++) // read every column
        grandAvg += avgCol(scores, i); // call avgCol function and place the result in grandAvg
	grandAvg = grandAvg / (double)columns; // calculate grandAvg
	
	return grandAvg;
}

/*
	This function calculates the average for every student (straight row average) 
	Precondition: all the elements of the array have been filled
	Post condition: the average of these elements is computed and returned
*/

double avgRows(int scores[][columns], int r)
{
    // declare variables
    int j;
    double avg;
    double sum = 0;  // initialize sum
    
    for (j = 0; j < columns; j++) // read every column in each row
    {
      sum += scores[r][j];
      avg = (double)sum / columns;  // calculate average for each student
	  }
	return avg;
}

/*
    This function calculates the grand average of all students (rows)
    (The average of all the averages)
    Precondition: all the averages of avgRows are computed and pass to this function
    Post condition: the average of these elements is computed and returned
*/

double grandAvgRows (int scores[][columns])
{
    double grandAvg = 0; // initialize grandAvg

	for(int i = 0; i < rows; i++) // read every row
		grandAvg += avgRows(scores, i); // call avgRows function and place the result in grandAvg
		grandAvg = grandAvg / (double)rows;  // calculate grandAvg
	
  return grandAvg;
}

/*
 	Insertion sort is a simple sorting algorithm that builds the final sorted 
array (or list) one 	item at a time.
	Precondition: all the elements of the array have been filled
Post condition: this iteration will insert grades[rows][columns] into the 
sorted order
*/

int *insertionSort(int arr[], int length)
{
	int i, j, tmp;
	
	for (i = 1; i < length; i++) 
	{
		for(j = i; j > 0 && arr[j - 1] > arr[j]; j--)
		{
			tmp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = tmp;    
		}
	}
	return arr;
}


/*
   This function excludes the lowest and highest scores for each student and finds   
   the average of the remaining grades.
   This function will use the insertionSort function as a pointer.
   Precondition: all the elements of the array have been filled; elements must be 
   Sorted.
   Post condition: the average of these elements is computed and returned.
*/

double studentAvgDrop(int scores[][columns], int r)
{
   double sum = 0;
   double avg;
   int *tmp = new int[columns]; // initializing tmp of size column in memory 
	 
     for (int j = 0; j < columns; j++)
    {
		  tmp[j] = scores[r][j];  // Insert row into temp array
    }

	  tmp = insertionSort(tmp, columns);  // Sort array
       
    sum = 0;
    for (int j = 1; j < columns - 1; j++)  // Find avg by skipping the first and last element
    {
          sum += tmp[j]; 
    }
    avg = (double)sum / (columns - 2); // calculate the average 
	 
    delete tmp; 
    return avg;
}

/*
     This function calculates the grand average of all the students (rows)
     after dropping the highest and lowest scores (the average of all the averages).
     Precondition: all the averages of studentAvgDrop are computed and pass to this 
     function.
     Post condition: the average of these elements is computed and returned
*/

double grandAvgDropRows(int scores[][columns])
{
    int i;
    double grandAvg = 0; // initialize grandAvg

	for(i = 0; i < rows; i++) // read every row
    grandAvg += studentAvgDrop(scores, i); // call studentAvgDrop function and place the result in grandAvg
	 grandAvg = grandAvg / (double)rows; // calculate grandAvg
	
	return grandAvg;
}


/*
    This function excludes the lowest and highest scores for each quiz and finds the 
    average of the remaining grades.
    This function will use the insertionSort function as a pointer.
    Precondition: all the elements of the array have been filled; elements must be 
    sorted.
    Post condition: the average of these elements is computed and returned
*/

double quizAvgDrop(int scores[][columns], int c)
{
   double avg;
   double sum = 0;
   int *tmp = new int[rows]; // initializing tmp of size rows in memory 
 
        for (int j = 0; j < rows; j++)
        {
		      tmp[j] = scores[j][c];  // Insert row into temp array
        }

	 tmp = insertionSort(tmp, rows); // Sort array
	 
        sum = 0;
        for (int i = 1; i < rows - 1; i++) // Find avg by skipping the first and last element
        {
            sum += tmp[i];
        }
        avg = (double)sum / (rows - 2); // calculate the average
		
   delete tmp;
   return avg;
}


/*
   This function calculates the grand average of all the quizzes (columns) after 
   dropping the highest and lowest scores. (The average of all the averages)
   Precondition: all the averages of quizAvgDrop are computed and pass to this 
   function.
   Post condition: the average of these elements is computed and returned
*/

double grandAvgDropCols(int scores[][columns])
{
    int i;
    double grandAvg = 0; // initialize grandAvg

	for(i = 0; i < columns; i++)  // read every column
	  grandAvg += quizAvgDrop(scores, i); // call quizAvgDrop function and place the result in grandAvg
	  grandAvg = grandAvg / (double)columns; // calculate grandAvg
	
	return grandAvg;
}


/*
   This function prints out all numbers in the array as well as all the computed 
   averages. (it is final print; prints all calculations)
   Precondition: all the elements of the array have been filled.
   All functions have to be called
   Post Condition:  all averages and calculations are printed
*/

void printArray(int scores[][columns])
{
    int i, j;
    for(i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
			     cout << scores[i][j] << "\t";
    	 cout << setprecision(2) << fixed << avgRows(grades, i) << "\t";
    	 cout << setprecision(2) << fixed << studentAvgDrop(grades, i) << endl;
    }

    for(int i = 0; i < columns; i++)
		cout << "\t";
    cout << setprecision(2) << fixed << grandAvgRows(grades) << "\t";
    cout << setprecision(2) << fixed << grandAvgDropRows(grades) << endl << endl;

    for(int j = 0; j < columns; j++)
		cout << avgCol (grades, j) << "\t";
    cout << setprecision(2) << fixed << grandAvgCol(grades) << endl;
    
    for(int j = 0; j < columns; j++)
		cout << quizAvgDrop(grades, j) << "\t";
    cout << setprecision(2) << fixed << grandAvgDropCols(grades) << endl;

}