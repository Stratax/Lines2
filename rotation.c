#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PI 3.14159265
void generateLine(unsigned char raster[1921][1081][3], int *p1, int *p2);
void printGraphics(unsigned char raster[1921][1081][3]);

int main(int argc, char const *argv[]) {

    FILE * obj;
    char chain[100];
    unsigned char raster[1921][1081][3];
    int vertex[15000][2],polygon[15000][3];
    int scale,nVertex=0,nPolygon=0,v=0,p=0,angle=90;
    scale = atoi(argv[1]);
    obj = fopen(argv[2],"r");
	double radians = (angle * PI)/180;
	
    while(fgets(chain,100,obj)){
        if(chain[0] == 'v'){
			float x = atof(strtok(chain+2," "))+7.0;
			float y = atof(strtok(chain+11," "))+1.3;
			
			//vertex[v][0] = (int)(x*scale)+500;
            //vertex[v][1] = (int)(y*scale)-200;

            vertex[v][0] = (int)((x*cos(radians)-y*sin(radians))*scale);
            vertex[v][1] = (int)((x*sin(radians)+y*cos(radians))*scale);
			
			//vertex[v][2] = (int)(atof(strtok(NULL,"\n"))*scale);
            nVertex++;
            v++;
        }
        if(chain[0] == 'f'){
            polygon[p][0] = atoi(strtok(chain+2," "));
            polygon[p][1] = atoi(strtok(NULL," "));
            polygon[p][2] = atoi(strtok(NULL,"\n"));
            nPolygon++;
            p++;
        }
    }
    fclose(obj);
    for(p = 0 ; p < nPolygon ; p++){
        int p1[2],p2[2];
        p1[0] = vertex[ polygon[p][0]-1 ][0];
        p1[1] = vertex[ polygon[p][0]-1 ][1];
        p2[0] = vertex[ polygon[p][1]-1 ][0];
        p2[1] = vertex[ polygon[p][1]-1 ][1];
        generateLine(raster,p1,p2);
        p1[0] = vertex[ polygon[p][1]-1 ][0];
        p1[1] = vertex[ polygon[p][1]-1 ][1];
        p2[0] = vertex[ polygon[p][2]-1 ][0];
        p2[1] = vertex[ polygon[p][2]-1 ][1];
        generateLine(raster,p1,p2);
        p1[0] = vertex[ polygon[p][2]-1 ][0];
        p1[1] = vertex[ polygon[p][2]-1 ][1];
        p2[0] = vertex[ polygon[p][0]-1 ][0];
        p2[1] = vertex[ polygon[p][0]-1 ][1];
        generateLine(raster,p1,p2);
    }

    /*printf("Vertex: %d\n",nVertex);
    for(v = 0 ; v < nVertex ; v++){
        printf("%d - %d\n",vertex[v][0],vertex[v][1]);
    }
    printf("\nPolygon: %d\n",nPolygon);
    for(v = 0 ; v < nPolygon ; v++){
        printf("%d - %d - %d\n",polygon[v][0],polygon[v][1],polygon[v][2]);
    }*/
    printGraphics(raster);
    return 0;
}

void  generateLine(unsigned char raster[1921][1081][3], int *p1, int *p2) {
    int j;
    int size_x,size_y;
    float slope;
    size_x = p2[0]-p1[0];
    size_y = p2[1]-p1[1];
    slope = (float)size_y/(float)size_x;
    //printf("(%d, %d)(%d, %d) -> \t%f \t %d/%d \n",p1[0],p1[1],p2[0],p2[1],slope,size_y,size_x);
    if(abs(size_x) > abs(size_y)){
        float delta = 0;
        if(size_x > 0){
            for(j = p1[0] ; j <= p2[0] ; j++){
                int y = round(p1[1]+delta);
                //printf("\t(%d, %d)\n",j,y);
                raster[j][y][0] = 150;
                raster[j][y][1] = 150;
                raster[j][y][2] = 150;
                delta+=slope;
            }
        }else{
            for(j = p1[0] ; j >= p2[0] ; j--){
                int y = round(p1[1]-delta);
                //printf("\t(%d, %d)\n",j,y);
                raster[j][y][0] = 150;
                raster[j][y][1] = 150;
                raster[j][y][2] = 150;
                delta+=slope;
            }
        }
    }else{
        float delta = 0;
        if(size_y > 0){
            for(j = p1[1] ; j <= p2[1] ; j++){
                int x = round(p1[0]+delta);
                //printf("\t(%d, %d)\n",x,j);
                raster[x][j][0] = 150;
                raster[x][j][1] = 150;
                raster[x][j][2] = 150;
                delta+=(1/slope);
            }
        }else{
            for(j = p1[1] ; j >= p2[1] ; j--){
                int x = round(p1[0]-delta);
                //printf("\t(%d, %d)\n",x,j);
                raster[x][j][0] = 150;
                raster[x][j][1] = 150;
                raster[x][j][2] = 150;
                delta+=(1/slope);
            }
        }
    }
}
void printGraphics(unsigned char raster[1921][1081][3]){
    int i,j;
    printf("P3\n1920 1080\n255\n");
    for(i = 0 ; i<1080 ; i++){
        for(j = 0 ; j<1920 ; j++){
            printf("%d %d %d\t",raster[j][i][0],raster[j][i][1],raster[j][i][2]);
        }
        printf("\n");
    }
}
