#include <bits/stdc++.h>
using namespace std;

int DEBINALIZE(int x) {
    return ((x)==-1 ? 0 : 1);
}
int BINALIZE(int x) {
    return ((x)== 0 ? -1 : 1);
}

const int NUMBER_OF_VECTORS = 4;
const int X = 11;
const int Y = 10;
const int AREA = X * Y;

typedef struct {
        int points;
        int* output;
        int* threshold;
        int** weight;
} net;
/* Input data for learning */
char x[NUMBER_OF_VECTORS][Y][X] = {
    {"  OOOOOO  ",
     " OOOOOOOO ",
     "OOO    OOO",
     "OO      OO",
     "OO      OO",
     "OO      OO",
     "OO      OO",
     "OOO    OOO",
     " OOOOOOOO ",
     "  OOOOOO  "
     },
	{"OOOOOO    ",
     "OOOOOO    ",
     "    OO    ",
     "    OO    ",
     "    OO    ",
     "    OO    ",
     "    OO    ",
     "    OO    ",
     "OOOOOOOOOO",
     "OOOOOOOOOO"},
	{"OOOOOOOO  ",
     "OOOOOOOOO ",
     "       OOO",
     "       OOO",
     "  OOOOOOO ",
     " OOOOOOO  ",
     "OOO       ",
     "OO        ",
     "OOOOOOOOOO",
     "OOOOOOOOOO"},
	{"OOOOOOOO  ",
    "OOOOOOOOO ",
     "       OOO",
     "       OOO",
     "    OOOOO ",
     "    OOOOO ",
     "       OOO",
     "       OOO",
     "OOOOOOOOO ",
     "OOOOOOOO  "},
    {"OO        ",
     "OO        ",
     "OO      OO",
     "OO      OO",
     "OOOOOOOOOO",
     "OOOOOOOOOO",
     "        OO",
     "        OO",
     "        OO",
     "        OO"},
    {"OOOOOOOOOO",
     "OOOOOOOOOO",
     "OO        ",
     "OO        ",
     "OOOOOOOO  ",
     "OOOOOOOOO ",
     "       OOO",
     "       OOO",
     "OOOOOOOOO ",
     "OOOOOOOO  "},
    {"  OOOOOOOO",
     " OOOOOOOOO",
     "OOO       ",
     "OO        ",
     "OOOOOOOO  ",
     "OOOOOOOOO ",
     "OO      OO",
     "OO      OO",
     " OOOOOOOO ",
     "  OOOOOO  "},
    {"OOOOOOOOOO",
     "OOOOOOOOOO",
     "        OO",
     "       OOO",
     "      OOO ",
     "     OOO  ",
     "    OOO   ",
     "   OOO    ",
     "  OOO     ",
     "  OO      "},
    {"  OOOOOO  ",
     " OOOOOOOO ",
     "OOO    OOO",
     "OOO    OOO",
     " OOOOOOOO ",
     " OOOOOOOO ",
     "OOO    OOO",
     "OOO    OOO",
     " OOOOOOOO ",
     "  OOOOOO  "},
     {"  OOOOOO  ",
     " OOOOOOOO ",
     "OOO    OOO",
     "OOO     OO",
     " OOOOOOOOO",
     "  OOOOOOOO",
     "        OO",
     "        OO",
     "        OO",
     "        OO"}
};
/* Input data for recognition */
char y[NUMBER_OF_VECTORS][Y][X] = {{
     "    OO    ",
	 "    OO    ",
	 "   OOOO   ",
	 "   O  OO  ",
	 "  OO  OOO ",
	 "  O    OO ",
	 " OOOOOOOO ",
	 " OOOOOOOO ",
	 "OO      OO",
	 "OO      OO"},
	{"OOOOOOO   ",
	 "OOOOOOOOO ",
	 "OO   OOOO ",
	 "OOOOOOOOO ",
	 "OOOOOOO   ",
	 "OO   OOO  ",
	 "OO    OO  ",
	 "OO   OOO  ",
	 "OOOOOOO   ",
	 "OOOOOOOO  "},
	{"OOOOOOOOOO",
	 "OOOOOOOOOO",
	 "OO      OO",
	 "OO        ",
	 "OOOOOO    ",
	 "OO    OOO ",
	 "OO        ",
	 "OO      OO",
	 "OOOOOOOOOO",
	 "OOOOOOOOOO"},
	{"OO      OO",
	 "OO      OO",
	 "OO OOOO OO",
	 "OO      OO",
	 "OOOOOOOOOO",
	 "OOOOOOOOOO",
	 "OO      OO",
	 "OO OOOO OO",
	 "OO      OO",
	 "OO      OO"}};
/* Input data for learning */
int input[NUMBER_OF_VECTORS][AREA];
/* Input data for recognition */
int notcorrect[NUMBER_OF_VECTORS][AREA];
/* Print the result */
void printNet(net* network)
{
	int i,j;
	for (i=0; i<Y; i++) {
		for (j=0; j<X; j++) {
			printf("%c", DEBINALIZE(network->output[i*X+j]) ? 'O' : ' ');
		}
		printf("\n");
	}
	printf("\n");
}
/* Create the net */
void createNet(net* network)
{
	int i;
	network->points = AREA; /* Number of points = net area */
	network->output = (int*)calloc(AREA, sizeof(int));
	network->threshold = (int*)calloc(AREA, sizeof(int));
	network->weight = (int**)calloc(AREA, sizeof(int*));
	/* Fill thresholds with zeros and allocating memory for weight matrix */
	for (i=0; i<AREA; i++) {
		network->threshold[i] = 0;
		network->weight[i] = (int*)calloc(AREA, sizeof(int));
	}
}
/* Convert points of 'O' to the BINALIZE -1 or +1 */
void pointstoBINALIZE(net* network)
{
	int n,i,j;
	for (n=0; n<NUMBER_OF_VECTORS; n++) {
		for (i=0; i<Y; i++) {
			for (j=0; j<X; j++) {
				/* Make points BINALIZE and convert 3d matrix to 2d */
				input[n][i*X+j] = BINALIZE(x[n][i][j] == 'O');
				notcorrect[n][i*X+j] = BINALIZE(y[n][i][j] == 'O');
			}
		}
	}
}
/* Calculate the weight matrix = learning */
void calculateWeights(net* network)
{
	int i,j,n;
	int weight;
	for (i=0; i<network->points; i++) {
		for (j=0; j<network->points; j++) {
			weight = 0;
			if (i!=j) {
				for (n=0; n<NUMBER_OF_VECTORS; n++) {
					/* Main formula for calculating weight matrix */
					weight += input[n][i] * input[n][j];
				}
			}
			/* Fill the weight matrix */
			network->weight[i][j] = weight;
		}
	}
}
/* Set the input vector to the Net->output */
void setInput(net* network, int* input)
{
	int i;
	for (i=0; i<network->points; i++) {
		network->output[i] = input[i];
	}
	printNet(network);
}
/* Set the Net->output to the output vector */
void getOutput(net* network, int* output)
{
	int i;
	for (i=0; i<network->points; i++) {
		output[i] = network->output[i];
	}
	printNet(network);
	printf("----------\n\n");
}
/* Next iteration to find the local minimum = recognized pattern */
int nextIteration(net* network, int i)
{
	int  j;
	int  sum, out;
	int changed;
	changed = 0;
	sum = 0;
	for (j=0; j<network->points; j++) {
		sum += network->weight[i][j] * network->output[j];
	}
	if (sum != network->threshold[i]) {
		if (sum < network->threshold[i]) out = -1;
		if (sum > network->threshold[i]) out = 1;
		if (out != network->output[i]) {
		  changed = 1;
		  network->output[i] = out;
		}
	}
	return changed;
}
/* Asynchronous correction */
void asynCor(net* network)
{
	int iteration;
	int iterationofLastChange;
	iteration = 0;
	iterationofLastChange = 0;
	do {
		iteration++;
		/* Every time take random element for the correction */
		if (nextIteration(network, rand() % (network->points)))
			iterationofLastChange = iteration;
	} while (iteration-iterationofLastChange < 10*network->points);
}
/* Find the local minimum = recognizing the pattern */
void findLocalMinimum(net* network, int* input)
{
	int output[AREA];
	/* Print not correct input for recognizing */
	setInput(network, input);
	/* Asynchronous correction */
	asynCor(network);
	/* Print recognized output */
	getOutput(network, output);
}
int main()
{
	net network;
	int n;
	/* Allocate memory and create the net */
	createNet(&network);
	/* Make the points matrix BINALIZE */
	pointstoBINALIZE(&network);
	/* Calculate the weight matrix */
	calculateWeights(&network);
	/* Find the local minimum = recognizing the pattern */
	for (n=0; n<NUMBER_OF_VECTORS; n++) {
		findLocalMinimum(&network, notcorrect[n]);
	}
    return 0;
}