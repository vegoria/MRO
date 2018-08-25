#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

#include "Ttiming.h"
#include "TPGM.h"


TTiming tt;//klasa do mierzenia czasu wykonywania siê poszczególnych funkcji

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}



int main(int argc, char **argv)
{
	int rows, cols;           
	int max_color;
	int hpos, i,j;		

	std::string infname = "maly.pgm";

	if ( (hpos = readPGMB_header(infname.c_str(), &rows, &cols, &max_color)) <= 0 )	   exit(1);

	unsigned char **a = new unsigned char* [rows];
	a[0] = new unsigned char [rows*cols];
	for(int i = 1; i < rows; i++)
		a[i] = a[i-1] + cols;

	if( readPGMB_data(a[0], infname.c_str(), hpos, rows, cols, max_color) == 0 )	   exit(1);

	//przygotowanie czarno-bialej tablicy wyjsciowej

	unsigned char **b = new unsigned char* [rows];
	b[0] = new unsigned char [rows*cols];
	for(int i = 1; i < rows; i++)
		b[i] = b[i-1] + cols;
	
	tt.Begin();		//start to measure the time

	for (i=0; i< rows; ++i){
		for (j=0; j< cols; ++j){

			b[i][j] = (a[i][j] > 128 ) ?  255 : 0;

		}
	}

	double elapsed = tt.End();	//stop and read elapsed time in ms (miliseconds)

	std::string outfname = infname;
	replace(outfname, ".pgm", "_simple.pgm");

	if( writePGMB_image(outfname.c_str(), b[0], rows, cols, 255) == 0)	   exit(1);

	delete[] a[0]; delete[] a;
	delete[] b[0]; delete[] b;

   printf("czas binaryzacji : %f ms", elapsed);
   getchar ();

   return 0;
}

