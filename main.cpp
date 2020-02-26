#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

// Generates a random Gaussian using the Box-Muller transform (whatever that
// means, this just implements the equations from the assignment pdf)
double genGaussian()
{
  double a = (double)rand() / RAND_MAX;
  // cout << "a: " << a << endl;
  double b = (double)rand() / RAND_MAX;
  // cout << "b: " << b << endl;
  return sqrt(-2 * log(a)) * cos(2 * M_PI * b);
}

// Generate a random length for a DNA string, given a mean and standard
// deviation. Truncates the length. May want to add one to avoid a length of 0
int randLen(int mean, double stddev)
{
  return (stddev * genGaussian() + 1.0) + mean;
}

// Returns a random DNA string of a specified length
string randString(int len, double probA, double probC, double probT,
                  double probG)
{
  string result;
  for (int i = 0; i < len; ++i) {
    double prob = (double)rand() / RAND_MAX;
    if (prob < probA) {
      result += 'A';
    }
    else if (prob < probA + probC) {
      result += 'C';
    }
    else if (prob < probA + probC + probT) {
      result += 'T';
    }
    else { // Must be between probA + probC + probT and 1.00
      result += 'G';
    }
  }

  return result;
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    cerr << "Error: Only one argument can be passed to this program." << endl;
    return 1;
  }

  bool appendOutput = false;
  string inputName = argv[1];
  while (true) {
    ifstream inputFile{inputName};

    if (!inputFile.is_open()) {
      cerr << "Error: Could not open file." << endl;
      return 2;
    }

    ofstream outputFile;
    if (appendOutput) {
      outputFile.open("chris.out", ios::app);
    }
    else {
      outputFile.open("chris.out");
      outputFile << "Christopher Chang" << endl;
      outputFile << "2344338" << endl;
      outputFile << "CPSC 350" << endl;
    }
    outputFile << inputName << "\n---------------------\n";

    // Make first pass to calculate mean and count, count nucleotide
    // and bigram occurrences

    int countA = 0;
    int countC = 0;
    int countT = 0;
    int countG = 0;

    int countAA = 0;
    int countAC = 0;
    int countAT = 0;
    int countAG = 0;
    int countCA = 0;
    int countCC = 0;
    int countCT = 0;
    int countCG = 0;
    int countTA = 0;
    int countTC = 0;
    int countTT = 0;
    int countTG = 0;
    int countGA = 0;
    int countGC = 0;
    int countGT = 0;
    int countGG = 0;

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
          inputFile.close();
          return 3;
        }
      }

      // Count bigrams
      for (size_t /* Used b/c of compiler warning */ i = 0;
           i < dnaString.size() - 2; i += 2) {
        string twochars = dnaString.substr(i, 2);
        // cout << twochars << endl;
        string twocharsUpper;
        twocharsUpper += toupper(twochars.at(0));
        twocharsUpper += toupper(twochars.at(1));
        if (twochars == "AA") {
          ++countAA;
        }
        else if (twochars == "AC") {
          ++countAC;
        }
        else if (twochars == "AT") {
          ++countAT;
        }
        else if (twochars == "AG") {
          ++countAG;
        }
        else if (twochars == "CA") {
          ++countCA;
        }
        else if (twochars == "CC") {
          ++countCC;
        }
        else if (twochars == "CT") {
          ++countCT;
        }
        else if (twochars == "CG") {
          ++countCG;
        }
        else if (twochars == "TA") {
          ++countTA;
        }
        else if (twochars == "TC") {
          ++countTC;
        }
        else if (twochars == "TT") {
          ++countTT;
        }
        else if (twochars == "TG") {
          ++countTG;
        }
        else if (twochars == "GA") {
          ++countGA;
        }
        else if (twochars == "GC") {
          ++countGC;
        }
        else if (twochars == "GT") {
          ++countGT;
        }
        else if (twochars == "GG") {
          ++countGG;
        }
      }
    }
    // Make calculations based off of what has been counted
    double mean = (double)sum / count;
    double probA = (double)countA / sum;
    double probC = (double)countC / sum;
    double probT = (double)countT / sum;
    double probG = (double)countG / sum;

    // Print out the probability of each nucleotid eoccurring
    outputFile << "Probability of A: " << probA << endl;
    outputFile << "Probability of C: " << probC << endl;
    outputFile << "Probability of T: " << probT << endl;
    outputFile << "Probability of G: " << probG << endl;

    // Calculate the probabilities of each bigram occurring
    int sumBigram = countAA + countAC + countAT + countAG + countCA + countCC +
                    countCT + countCG + countTA + countTC + countTT + countTG +
                    countGA + countGC + countGT + countGG;
    double probAA = (double)countAA / sumBigram;
    double probAC = (double)countAC / sumBigram;
    double probAT = (double)countAT / sumBigram;
    double probAG = (double)countAG / sumBigram;
    double probCA = (double)countCA / sumBigram;
    double probCC = (double)countCC / sumBigram;
    double probCT = (double)countCT / sumBigram;
    double probCG = (double)countCG / sumBigram;
    double probTA = (double)countTA / sumBigram;
    double probTC = (double)countTC / sumBigram;
    double probTT = (double)countTT / sumBigram;
    double probTG = (double)countTG / sumBigram;
    double probGA = (double)countGA / sumBigram;
    double probGC = (double)countGC / sumBigram;
    double probGT = (double)countGT / sumBigram;
    double probGG = (double)countGG / sumBigram;

    // Print out the probability of bigrams
    outputFile << "Probability of bigram AA: " << probAA << endl;
    outputFile << "Probability of bigram AC: " << probAC << endl;
    outputFile << "Probability of bigram AT: " << probAT << endl;
    outputFile << "Probability of bigram AG: " << probAG << endl;
    outputFile << "Probability of bigram CA: " << probCA << endl;
    outputFile << "Probability of bigram CC: " << probCC << endl;
    outputFile << "Probability of bigram CT: " << probCT << endl;
    outputFile << "Probability of bigram CG: " << probCG << endl;
    outputFile << "Probability of bigram TA: " << probTA << endl;
    outputFile << "Probability of bigram TC: " << probTC << endl;
    outputFile << "Probability of bigram TT: " << probTT << endl;
    outputFile << "Probability of bigram TG: " << probTG << endl;
    outputFile << "Probability of bigram GA: " << probGA << endl;
    outputFile << "Probability of bigram GC: " << probGC << endl;
    outputFile << "Probability of bigram GT: " << probGT << endl;
    outputFile << "Probability of bigram GG: " << probGG << endl;

    outputFile << "sum: " << sum << endl;
    outputFile << "mean: " << mean << endl;
    inputFile.close();

    // Now that we have the mean, make the second pass to calculate variance and
    // standard deviation
    inputFile.open(inputName);
    double squareSum = 0.0;
    while (inputFile >> dnaString) {
      double square = (mean - dnaString.size()) * (mean - dnaString.size());
      squareSum += square;
    }
    double variance = squareSum / count;
    double stddev = sqrt(variance);

    outputFile << "variance: " << variance << endl;
    outputFile << "standard deviation: " << stddev << endl;
    inputFile.close();

    // Generate 1000 DNA strings whose lengths follow a "Gaussian distribution"
    // with the same mean and variance that have been previous calculated
    srand(time(NULL));
    for (int i = 0; i < 1000; ++i) {
      int len = randLen(mean, stddev);
      // if (len < 1) {
      //   cout << i << ": length of: " << len << endl;
      // }
      outputFile << randString(len, probA, probC, probT, probG) << endl;
    }
    outputFile.close();

    // Set up the loop for processing another list, if the user chooses to
    cout << "Do you want to process another list? (yes/no) ";
    string choice;
    cin >> choice;
    if (choice == "yes" || choice == "y") {
      appendOutput = true;

      cout << "Enter name of file: ";
      cin >> inputName;
    }
    else {
      break;
    }
  }

  return 0;
}