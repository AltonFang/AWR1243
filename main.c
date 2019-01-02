#include <fftw3.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <assert.h>
#include <string.h>

using namespace std;

// Macros for real and imaginary parts
#define REAL 0
#define IMAG 1

int main() {
  // Define the length of the complex arrays
  int n0 = 256;
  int n1 = 8;
  int n2 = 4;
  int n = n0*n1*n2;
  // Input array
  short int si_x[n][2];
  fftw_complex x[n];  // This is equivalent to: double x[n][2];
  // Output array
  short int si_y[n][2];
  fftw_complex y[n];  // This is equivalent to: double x[n][2];
  
  char filename[20];
  FILE *fp;
  int frame = 1;
  
  strcpy(filename, "adc_data02.bin");
  
  fp = fopen(filename, "rb");
  assert(fp != NULL);
  
  while (frame <= 32) {
    // Fill the first array with some data
    for (int i = 0 ; i < n ; i++) {
      fread(&(si_x[i][REAL]), sizeof(short int), 1, fp);
      fread(&(si_x[i][IMAG]), sizeof(short int), 1, fp);
      si_x[i][REAL] ^= (1 << 15);
      si_x[i][IMAG] ^= (1 << 15);
      x[i][REAL] = si_x[i][REAL];
      x[i][IMAG] = si_x[i][IMAG];
      //x[i][REAL] = i + 1;
      //x[i][IMAG] = 0;
    }
    // Plant the FFT and execute it
    //fftw_plan plan = fftw_plan_dft_1d(n, x, y, FFTW_FORWARD, FFTW_ESTIMATE);
    //fftw_plan plan = fftw_plan fftw_plan_dft_2d(n0, n1, x, y, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_plan plan = fftw_plan_dft_3d(n0, n1, n2, x, y, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    // Do some cleaning
    fftw_destroy_plan(plan);
    fftw_cleanup();
    frame++;
  }
  
  // Display the results
  cout << "FFT = " << endl;
  for (int i = 0 ; i < n ; i++) {
    if (y[i][IMAG] < 0) {
      cout << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i, ";
    } else {
      cout << y[i][REAL] << " + " << y[i][IMAG] << "i, ";
    }
    if ((i+1) % 4 == 0) {
      printf("\n");
    }
  }

  return 0;
}
