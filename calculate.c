#include <stdio.h>
#include <math.h>

#define PI M_PI

void x_calculate();
void x_inequality();
void ue_cal();

int main(void) {
  printf("1 for X calculated values\n2 for X inequality\n");
  printf("3 for calculating ue\n");
  printf("Input: ");
  int i;
  scanf("%d", &i);
  if(i == 1) {
    x_calculate();
  } else if (i == 2) {
    x_inequality();
  } else if(i == 3) {
    ue_cal();
  }
  return 0;
}



void x_calculate() {
    
    double ue;
    printf("ue = ");
    scanf("%lf", &ue);
    printf("wn (rad/s) = ");
    double wn;
    scanf("%lf", &wn);
    double ratio;
    printf("ratio = ");
    scanf("%lf", &ratio);
    printf("start at ? (rpm) = ");
    double start;
    scanf("%lf", &start);
    printf("end at in rpm = ");
    double end;
    scanf("%lf", &end);
    printf("Increments of (in rpm) = ");
    double incre;
    scanf("%lf", &incre);
    printf("this will print all values of amplitude for\n");
    printf("%lf < w < %lf, in steps of %lf\n", start, end, incre);
    double k = 1 / (pow(wn, 2) * 350000);
    for(double i = start; i <= end; i = i + incre) {
        double w = 2 * PI * i / 60;
        double top = ue * pow(w,2) * k;
        double bottom = pow(1-pow(w/wn, 2), 2);
        bottom = bottom + pow(2 * ratio * w / wn, 2);
        double square = sqrt(bottom);
        double final = top / square;
        printf("%lf\n", final * 1000);
    }
}

void x_inequality() {
    
    double ue;
    printf("ue = ");
    scanf("%lf", &ue);
    printf("wn (rad/s) = ");
    double wn;
    scanf("%lf", &wn);
    double ratio;
    printf("ratio = ");
    scanf("%lf", &ratio);
    double max;
    printf("what is max amplitude (mm) :");
    scanf("%lf", &max);
    double k = 1 / (pow(wn, 2) * 350000);
    int j = 0;
    double prev = 0;
    for(double i = 1; i <= 30; i = i + 0.1) {
        double w = 2 * PI * i / 60;
        double top = ue * pow(w,2) * k;
        double bottom = pow(1-pow(w/wn, 2), 2);
        bottom = bottom + pow(2 * ratio * w / wn, 2);
        double square = sqrt(bottom);
        double final = top / square;
        final = final * 1000;
        if(j == 0 && final > max && prev < max) {
          printf("w < %lf\n", i);
          j++;
        } else if(j == 1 && prev > max && final < max) {
          printf("w > %lf\n", i);
          j++;
          break;
        }
        prev = final;
    }
}

void ue_cal() {
  
  printf("wn (rad/s) = ");
  double wn;
  scanf("%lf", &wn);
  double ratio;
  printf("ratio = ");
  scanf("%lf", &ratio);
  

  double mass = 350000;
  double k = wn * wn * mass;
  char y = 'y';
  while(y == 'y' || y == 'Y') {
    double ampli;
    printf("amplitude (m) = ");
    scanf("%lf", &ampli);
    double w;
    printf("w (rpm) = ");
    scanf("%lf", &w);

    double w_rad = w * 2 * PI / 60;
    double front = ampli * k  / (w * w);
    double back = pow(1 - pow(w/wn, 2), 2);
    back = back + pow(2*ratio*w/wn, 2);
    double square = sqrt(back);
    double f = square * front;
    printf("ue = %lf\n", f);
    printf("Continue for different amplitude and velocity?\n y or n: ");
    scanf(" %c", &y);
  }

}
