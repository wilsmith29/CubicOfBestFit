#include "FPToolkit.c"

double swidth, sheight ;

int main(int argc, char **argv)
{
  int boolean ;
  FILE *f ;
  int n,s ;
  char q ;
  double p[2],u,v ;
  double x[1000], y[1000] ;
  int i ;
	double sum3 = 0;
	double sum4 = 0;
	double sum5 = 0;
	double sum2 = 0;
	double sum6 = 0;
	double sum1 = 0;
	double sum_ones = 0;
	double sumy = 0;
	double sumyx = 0;
	double sumyx2 = 0;
	double sumyx3 = 0;
	double matrix[4][5];

  if ((argc != 3) && (argc != 4))  {
    printf("Usage : \n") ;
    printf("   For clicked data :\n") ;
    printf("pgm  screen_width  screen_height\n") ;
    printf("   OR if you have data from a file,  \n") ;
    printf("pgm   screen_width  screen_height  filename\n") ;
    exit(0) ;
  }



  swidth = atoi(argv[1]) ;
  sheight = atoi(argv[2]) ;
  G_init_graphics(swidth, sheight) ;
  G_rgb (0,0,0) ;
  G_clear() ;
  G_rgb(1,1,0) ;
  
  
  if (argc == 4) {

    // input from file
    
    f = fopen(argv[3],"r") ;
    if (f == NULL) {
      printf("can't open file, %s\n",argv[3]) ;
      exit(0) ;
    }
  
    fscanf(f,"%d",&n) ;
    for (i = 0 ; i < n ; i++) {
      fscanf(f,"%lf %lf\n",&x[i],&y[i]) ;
      G_fill_rectangle(x[i]-2.0,y[i]-2.0, 5.0,5.0) ;
    }

    
  }  else {

    // input by clicking 

    G_rgb (0.8, 0.8, 0.8) ;
    G_fill_rectangle (0, sheight-20,  swidth,20) ;
    G_rgb(0,0,0) ;
    G_draw_string("click up here to terminate input",30,sheight-17) ;
    G_rgb (1,1,1) ;
    n = 0 ;
    G_wait_click(p) ;  u = p[0] ; v = p[1] ;
    while (v < sheight - 20) {
      G_fill_rectangle(u-2.0,v-2.0, 5.0,5.0) ;
      x[n] = u ; y[n] = v ; n++ ;
      G_wait_click(p) ;  u = p[0] ; v = p[1] ;
    }

  }


  printf("\n") ;
  printf("%d\n",n) ;
  for (i = 0 ; i < n ; i++) {
    printf("%8.2lf  %8.2lf\n",x[i],y[i]) ;
  }

	//Calculate the sums for the matrix
	for (int i = 0; i < n; i++) {
		sum_ones += 1;
		sumy += y[i];
		sumyx += (y[i] * x[i]);
		sumyx2 += (y[i] * pow(x[i], 2));
		sumyx3 += (y[i] * pow(x[i], 3));
		sum1 += x[i];
		sum2 += pow(x[i], 2);
		sum3 += pow(x[i], 3);
		sum4 += pow(x[i], 4);
		sum5 += pow(x[i], 5);
		sum6 += pow(x[i], 6);
	}

	double first[5] = {sum3, sum2, sum1, sum_ones, sumy};
	double second[5] = {sum4, sum3, sum2, sum1, sumyx};
	double third[5] = {sum5, sum4, sum3, sum2, sumyx2};
	double fourth[5] = {sum6, sum5, sum4, sum3, sumyx3};

	for (int i = 0; i < 5; ++i) {
		matrix[0][i] = first[i];
	}

	for (int i = 0; i < 5; ++i) {
		matrix[1][i] = second[i];
	}

	for (int i = 0; i < 5; ++i) {
		matrix[2][i] = third[i];
	}

	for (int i = 0; i < 5; ++i) {
		matrix[3][i] = fourth[i];
	}

	//System solver
  for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			double factor = matrix[j][i] / matrix[i][i];
			for (int k = i; k <= 4; ++k) {
				matrix[j][k] -= factor * matrix[i][k];
			}
		}
	}

  for (int i = 3; i >= 0; --i) {
		for (int j = i + 1; j < 4; ++j) {
			matrix[i][4] -= matrix[i][j] * matrix[j][4];
		}
		matrix[i][4] /= matrix[i][i];
	}

	//Save results
	double a = matrix[0][4];
	double b = matrix[1][4];
	double c = matrix[2][4];
	double d = matrix[3][4];

	//Print resulting matrix
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 5; ++j) {
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}

	//Plot the line
	G_rgb(0, 0, 1);
	for (double x = 0; x <= swidth; x += 0.1) {
		double y = a * pow(x, 3) + b * pow(x, 2) + c * x + d;
		G_point(x, y);
	}

	G_wait_key();

	G_close();

	return 0;
	
}
