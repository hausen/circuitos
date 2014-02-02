#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int boolArrayToInt(int n, const bool q[]) {
  int ret = 0;
  for(int i=0; i<n; ++i) {
    ret += (q[i] != 0) ? pow(2,i) : 0;
  }
  return ret;
}

void intToBoolArray(int value, int n, bool q[]) {
  for(int i=0; i<n; ++i) {
    q[i] = ((value % 2) == 1);
    value /= 2;
  }
}

bool interactive = false;
bool color = false;
int n = 0;

void printUsageAndExit(void) {
  cerr << "Usage: jkcounter [--interactive] [--color] n" << endl;
  cerr << "       where n is the number of flip-flops to use" << endl;
  exit(1);
}

class LineTokenizer {
public:
  LineTokenizer(string &line) : ln(line), linepos(0) { }

  string *getNextToken() {
    static string ret;
    while (linepos < ln.size() && ln[linepos] != '0' &&
           ln[linepos] != '1' && ln[linepos] != 'd') {
      ++linepos;
    }
    if (linepos >= ln.size()) {
      return NULL;
    }
    if (ln[linepos] == 'd') {
      ret = "delete";
      linepos = ln.size();
    } else if (ln[linepos] == '0') {
      ret = "0";
    } else {
      ret = "1";
    }
    ++linepos;
    return &ret;
  }
private:
  string &ln;
  int linepos;
};

int main(int argc, char *argv[]) {
  for(int i=1; argv[i] != NULL; ++i) {
    if (strcmp(argv[i], "--interactive") == 0) {
      interactive = true;
    } else if (strcmp(argv[i], "--color") == 0) {
      color = true;
    } else if(isdigit(argv[i][0])) {
      n = atoi(argv[i]);
    } else {
      printUsageAndExit();
    }
  }

  if(n == 0) {
    printUsageAndExit();
  }

  if (interactive) {
    cerr << "inputs: Qi, outputs: Yi" << endl;
    for(int i=n-1; i>=0; --i) {
      cerr << "Q" << i << "\t";
    }
    for(int i=n-1; i>=0; --i) {
      cerr << "Y" << i << "\t";
    }
    cerr << endl;
  }

  bool *nextstate[(size_t)pow(2,n)];
  memset(nextstate, 0, (size_t)pow(2,n)*sizeof(bool *));

  string line;
  while(getline(cin, line, '\n')) {
    if (line[0] == '#') {
      continue;
    }

    LineTokenizer tokenizer(line);
    int i=n-1;
    bool q[n];
    string *token;
    for (int i=n-1; i >= 0; --i) {
      token = tokenizer.getNextToken();
      if (token == NULL) {
        break;
      }
      if ((*token) == "delete") {
        ++i;
        continue;
      }
      q[i] = ((*token) == "0" ? false : true);
    }
    if (token == NULL) {
      break;
    }

    bool *y = new bool[n]();
    if (nextstate[boolArrayToInt(n,q)] != NULL) {
      delete nextstate[boolArrayToInt(n,q)];
    }
    nextstate[boolArrayToInt(n,q)] = y;

    bool deleteState = false;
    for (int i=n-1; i >= 0; --i) {
      token = tokenizer.getNextToken();
      if (token == NULL) {
        break;
      }
      if ((*token) == "delete") {
        deleteState = true;
        break;
      }
      y[i] = ((*token) == "0" ? false : true);
    }

    if (deleteState) {
      delete nextstate[boolArrayToInt(n,q)];
      nextstate[boolArrayToInt(n,q)] = NULL;
    }
  }

  if (interactive) {
    cerr << endl << "read:" << endl;
    for(int i=0; i<pow(2,n); ++i) {
      bool q[n];
      bool *y = nextstate[i];
      if (y != NULL) {
        intToBoolArray(i, n, q);
        for (int j=n-1; j>=0; --j) {
          cout << (q[j] ? 1 : 0) << '\t';
        }
        for (int j=n-1; j>=0; --j) {
          cout << (y[j] ? 1 : 0) << '\t';
        }
        cout << endl;
      }
    }

    cerr << endl << "===============" << endl << endl;
  }

  if (color) {
    cout << "\x1b[;1m";
  }

  for(int i=n-1; i>=0; --i) {
    cout << "Q" << i << "\t";
  }

  if (color) {
    cout << "\x1b[31;1m";
  }

  for(int i=n-1; i>=0; --i) {
    cout << "J" << i << "\t" << "K" << i << "\t";
  }
  cout << endl;

  if (color) {
    cout << "\x1b[0m";
  }

  for(int i=0; i<pow(2,n); ++i) {
    bool q[n];
    intToBoolArray(i, n, q);
    for (int j=n-1; j>=0; --j) {
      cout << (q[j] ? 1 : 0) << '\t';
    }

    if (color) {
      cout << "\x1b[31m";
    }

    bool *y = nextstate[i];
    for (int j=n-1; j>=0; --j) {
      if (y != NULL) {
        if (q[j] == false && y[j] == false) {
          cout << "0\tx\t";
        } else if (q[j] == false && y[j] == true) {
          cout << "1\tx\t";
        } else if (q[j] == true && y[j] == false) {
          cout << "x\t1\t";
        } else {
          cout << "x\t0\t";
        }
      } else {
        cout << "x\tx\t";
      }
    }

    cout << endl;
    if (color) {
      cout << "\x1b[0m";
    }
  }

}


