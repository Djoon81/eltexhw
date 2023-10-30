#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 11
#define BUFFMAX 3
#define COUNTFUNC 9 // количество функций -1, то есть 4 (т.к. [0] используется для заверщения работы)
double sum(double x,double y){
    double o;
    o = x + y;
    return o;
}
double diff(double x,double y){
    double o;
    o = x - y;
    return o;
}
double divi(double x,double y){
    double o;
    o = x / y;
    return o;
}
double mult(double x,double y){
    double o;
    o = x * y;
    return o;
}
double powXY(double x,double y){
    double o;
    o = pow(x,y);
    return o;
}
double root(double x,double y){
    double o;
    o = pow(x,1/y);
    return o;
}
int main() {
    double x;
    double y;
    double o;
    char buf[MAX];
    double (*func[COUNTFUNC])(double,double) = {NULL,sum, diff,divi,mult, powXY, root,NULL,NULL};
    int i = 1;
    char F[BUFFMAX];
    printf("Простой калькулятор на 4 функции (+-/*)\n Максимальная длинна чисел 10 (учитывая точку)\n");
    printf("Введите первое число (x)\n");
    fgets(buf,MAX,stdin);
    x = atof(buf);
    fflush(stdin);
    printf("Введите второе число (y)\n");
    fgets(buf,MAX,stdin);
    y = atof(buf);
    fflush(stdin);
    while (i != 0){
        printf("Введите номер действия, которое нужно совершить над этими числами\n"
               " 1 - '+'\n 2 - '-'\n 3 - '/'\n 4 - '*'\n"
               " 5 - 'x в степени y'\n 6 - 'корень y степени из x'"
               "Если хотите закончить работу - введите 0\n");
        fgets(F,BUFFMAX,stdin);
        i = atoi(F);
        if (i >= COUNTFUNC){
            printf("Введён неправильный символ!\n");
        }
        if (i != 0 && *func[i] != NULL){
            o = func[i](x,y);
            printf("\nОтвет: %f\n",o);
        }
    }
}
