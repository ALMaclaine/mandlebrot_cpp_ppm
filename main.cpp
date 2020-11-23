#include <fstream>
#include <iostream>
using namespace std;

double mapToReal(int x, int imageWidth, double minR, double maxR) {
  double range = maxR - minR;
  return x * (range / imageWidth) + minR;
}

double mapToImaginary(int y, int imageHeight, double minI, double maxI) {
  double range = maxI - minI;
  return y * (range / imageHeight) + minI;
}

int findMandelbrot(double cr, double ci, int max_iterations) {
  int i = 0;
  double zr = 0.0;
  double zi = 0.0;
  while(i < max_iterations && zr * zr + zi * zi < 4.0) {
    double temp = zr * zr - zi * zi + cr;
    zi = 2.00 * zr * zi + ci;
    zr = temp;
    i++;
  }
  return i;
}

int main() {
  ifstream fin("input.txt");
  int imageWidth, imageHeight, maxN;
  double minR, maxR, minI, maxI;
  if(!fin) {
    cout << "Could not open file!" << endl;
    cin.ignore();
    return 0;
  } 
  fin >> imageWidth >> imageHeight >> maxN;
  fin >> minR >> maxR >> minI >> maxI;
  fin.close();

  ofstream fout("output_image.ppm");

  fout << "P3" << endl;
  fout << imageWidth << " " << imageHeight << endl;
  fout << "256" << endl;

  for(int y = 0; y < imageHeight; y++) {
    for(int x = 0; x < imageWidth; x++) {
      double cr = mapToReal(x, imageWidth, minR, maxR);
      double ci = mapToImaginary(y, imageHeight, minI, maxI);
      int n = findMandelbrot(cr, ci, maxN);
      int r = n % 256;
      int g = n % 256;
      int b = n % 256;

      fout << r << " " << g << " " << b << " ";
    }
    fout << endl;
  }
  fout.close();
  cout << "Finished!" << endl;
  return 0;
}
