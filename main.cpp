#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  if (argc != 2) {
    cerr << "Error: Only one argument can be passed to this program." << endl;
    return 1;
  }

  ifstream inputFile{argv[1]};
  if (!inputFile.is_open()) {
    cerr << "Error: Could not open file." << endl;
    return 2;
  }

  // Make first pass to calculate mean and count, count nucleotide occurrences
  int countA = 0;
  int countC = 0;
  int countT = 0;
  int countG = 0;
  int count = 0;
  int sum = 0;
  string dnaString;
  while (inputFile >> dnaString) {
    // Calculations for mean & count
    ++count;
    sum += dnaString.size();

    // Count ACTG nucleotides
    for (char c : dnaString) {
      c = tolower(c);
      if (c == 'a') {
        ++countA;
      }
      else if (c == 'c') {
        ++countC;
      }
      else if (c == 'g') {
        ++countG;
      }
      else if (c == 't') {
        ++countT;
      }
      else {
        cerr << "Error at line " << count << ": invalid character '" << c
             << '\'' << endl;
        return 3;
      }
    }
  }
  double mean = (double)sum / count;
  double probA = (double)countA / sum;
  double probC = (double)countC / sum;
  double probT = (double)countT / sum;
  double probG = (double)countG / sum;

  cout << "Probability of A: " << probA << endl;
  cout << "Probability of C: " << probC << endl;
  cout << "Probability of T: " << probT << endl;
  cout << "Probability of G: " << probG << endl;

  cout << "sum: " << sum << endl;
  cout << "mean: " << mean << endl;
  inputFile.close();

  // Now that we have the mean, make the second pass to calculate variance and
  // standard deviation
  inputFile.open(argv[1]);
  double squareSum = 0.0;
  while (inputFile >> dnaString) {
    double square = (mean - dnaString.size()) * (mean - dnaString.size());
    squareSum += square;
  }
  double variance = squareSum / count;
  double stddev = sqrt(variance);

  cout << "variance: " << variance << endl;
  cout << "standard deviation: " << stddev << endl;
  inputFile.close();

  return 0;
}