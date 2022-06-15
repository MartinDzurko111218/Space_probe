#include <stdio.h>

double volnyPad(double H, double T, double m, double g){ //vlastna funkcia na vypocet df
    double A,df;
    A=T/m;
    df=(A-g)*H/A;
    return df;
}
int motor(double vsoft, double v){                      //funkcia na ON/OFF switch motora
    if (v<vsoft){return 1;}
    else {return 0;}
}

                        ///2500 18000 0 6000 0.62 -4 0.1 -skusobne input hodnoty
int main() {
    double m,T,v0,H,g,vsoft,dt,A,a,de,s=0,t=0;
    int sm; //stav motora
    scanf("%lf %lf %lf %lf %lf %lf %lf",&m,&T,&v0,&H,&g,&vsoft,&dt);
    printf("m=%.3lf\nT=%.3lf\nv0=%.3lf\nH=%.3lf\ng=%.3lf\nvsoft=%.3lf\ndt=%.3lf\n",m,T,v0,H,g,vsoft,dt);
    printf("df=%.3lf\n",volnyPad(H,T,m,g)); //vypis df

    A=T/m; de=H-volnyPad(H,T,m,g);       //vzorce potrebne na nasledujuci vypocet, de=hladina odkedy zacina motorom riadeny pad
    while (H>0){                         //cely cyklus pristavania od uplneho zaciatku az po "tesne nad povrchom telesa"
        if (motor(vsoft,v0)==1 && H<=de) {
            sm=1;
            s=s+dt;
            a=A-g;}
        else {a=-g;sm=0;}
        printf("t=%.3lf h=%.3lf v=%.3lf s=%d\n",t,H,v0,sm);
        H=H+v0*dt+(a*dt*dt/2);
        v0=v0+a*dt;
        t=t+dt;
    }

    printf("t=%.3lf h=%.3lf v=%.3lf\n",t,H,v0);
    printf("total=%0.3lf",s);       //vypis konecnej hodnoty casu zapnuteho motora
    return 0;
}
