//Mert MUSLU 150120027
//Gülsüm Ece GÜNAY 150121539
//Erkut DÖNMEZ 150120051

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    int id;
    int x;
    int y;
} City;

void merge_sort_x(City* city,int left,int right)  {
    if(left<right) {
        int med = left + (right - left) /2;
        merge_sort_x(city,left,med);
        merge_sort_x(city,med+1,right);
        merge_x(city,left,med,right);
    }
}

void merge_sort_y(City* city, int left, int right) {
    if(left<right) {
        int med = left + (right - left) /2;
        merge_sort_y(city,left,med);
        merge_sort_y(city,med+1,right);
        merge_y(city,left,med,right);
    }

}

void merge_x(City* city, int left, int med, int right){
    int i, j, k;
    int n1 = med - left + 1;
    int n2 = right - med;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = city[left + i].x;
    for (j = 0; j < n2; j++)
        R[j] = city[med + 1 + j].x;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            city[k].x = L[i];
            i++;
        }
        else{
            city[k].x = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        city[k].x = L[i];
        i++;
        k++;
    }
    while (j < n2){
        city[k].x = R[j];
        j++;
        k++;
    }
}

void merge_y(City* city, int left, int med, int right) {
    int i, j, k;
    int n1 = med - left + 1;
    int n2 = right - med;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = city[left + i].y;
    for (j = 0; j < n2; j++)
        R[j] = city[med + 1 + j].y;
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            city[k].y = L[i];
            i++;
        }
        else{
            city[k].y= R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        city[k].y = L[i];
        i++;
        k++;
    }
    while (j < n2){
        city[k].y = R[j];
        j++;
        k++;
    }

}

    int main() {
        FILE* output = fopen("test-output-4.txt","w");
        FILE* file = fopen("input.txt", "r");
        int cityCount = 0;
        int size = 2;
        City* cities;
        cities = malloc(sizeof(City) * size);


        while (!feof(file)) {
            fscanf(file, "%d %d %d", &(cities[cityCount].id), &(cities[cityCount].x), &(cities[cityCount].y));
            cityCount++;
            if(cityCount == size) {
                size *= 2;
                cities = realloc(cities, sizeof((*cities)) * size);
            }
        }
        int sizearray = cityCount;
        int **distance;
        distance = (int **)malloc(sizearray * sizeof(int *));
        for (int i = 0; i < sizearray; i++) {
            distance[i] = (int *)malloc(sizearray * sizeof(int));
        }


        FILE* temp_file = fopen("input.txt", "r");
        int temp_cityCount = 0;
        int temp_size = 2;
        City* temp_cities;
        temp_cities = malloc(sizeof(City) * temp_size );

        while (!feof(temp_file)) {
            fscanf(temp_file, "%d %d %d", &(temp_cities[temp_cityCount].id), &(temp_cities[temp_cityCount].x), &(temp_cities[temp_cityCount].y));
            temp_cityCount++;
            if(temp_cityCount == temp_size ) {
                temp_size  *= 2;
                temp_cities = realloc(temp_cities, sizeof((*temp_cities)) * temp_size );
            }
        }

        merge_sort_x(temp_cities,0,temp_cityCount-1); //Theta(n)
        merge_sort_y(temp_cities,0,temp_cityCount-1); //Theta(n)

        //ordering according to the projectile on x-axis
        int morting_x = cities[0].id;
        int Mx[cityCount];
        for(int i = 0; i <=cityCount; i++) {
            for(int j = 0; j <=cityCount; j++) {
                if(temp_cities[i].x == cities[j].x) {
                    if(Mx[j] != morting_x -1) {
                        Mx[j] = morting_x;
                        morting_x++;
                    }
                }
            }
        }
        //ordering according to the projectile on y-axis
        int morting_y = cities[0].id;
        int My[cityCount];
        for(int i = 0; i <=cityCount; i++) {
            for(int j = 0; j <=cityCount; j++) {
                if(temp_cities[i].y == cities[j].y) {
                    if(My[j] != morting_y -1) {
                        My[j] = morting_y;
                        morting_y++;
                    }
                }
            }
        }
        free(temp_cities);
        fclose(temp_file);
        int divide = 0;
        int temp_count = cityCount;

        if(temp_count >100) {
            for(int i = 0; i < 20; i++) {
                temp_count  /= 2;
                divide++;
                if(temp_count  == 0) {
                    break;
                }
            }
            divide--;
        }
        else  {
            divide = 2;
        }

        int breakerss = 0;
        int mina = 999999999;
        int min_i;
        int min_j;
        int aa = 0;
        int bb = 0;
        int breakers = 0;
        //calculating distances between cities
        for(int i = 0; i < cityCount; i++){
                for(int j = i; j < cityCount;j++){
                    if(i == j) {
                        distance[i][j] = 999999999;
                        j++;
                    }
                    breakerss = 0;
                    if((abs(Mx[i] - Mx[j]) > cityCount/divide) && (abs(My[i] - My[j]) > cityCount/divide)) {
                        distance[i][j] = 999999999;
                        breakerss = 1;
                    }

                    if(breakerss != 1) {
                        distance[i][j] = (abs(pow((cities[i].x - cities[j].x),2) + pow((cities[i].y - cities[j].y),2)));
                        if(distance[i][j] < mina) {
                            mina = distance[i][j];
                            min_i = i;
                            min_j = j;
                        }
                    }
            }
        }

        // decreasing the time complexity for simetrical distances, e.g. distance[3][5] = distance[5][3]
        for(int i = 0;i <cityCount;i++) {
            for(int j = i+1; j < cityCount ; j++) {
                if(distance[i][j] != 999999999 || distance[j][i] != 999999999)  {
                    distance[j][i] = distance[i][j];
                }
            }
        }

        int holdCityId[cityCount];
        int increaseCount = 0;
        float path_1;
        int visited[cityCount];
        int count = 0;
        int temp = 0;
        int min = 999999999;
        int breaker = 0;
        int breakerssss = 0;
        int k = 0;
        for(int i = min_i; count < ceil(cityCount/2.0) ; count++, i = temp){
            visited[i] = i;
            min = 999999999;
                if (count == ceil(cityCount/2.0)-1) {
                    distance[i][min_i] = (abs(pow((cities[i].x - cities[min_i].x),2) + pow((cities[i].y - cities[min_i].y),2)));
                    min = distance[i][min_i];
                    holdCityId[increaseCount] = cities[i].id;
                    breakerssss = 1;
                }
                if(breakerssss != 1) {
                    for(int j = 0; j < cityCount;j++){
                        breaker = 0;
                        if(((abs(Mx[i] - Mx[j]) > cityCount/divide) && (abs(My[i] - My[j]) > cityCount/divide))|| visited[j] == j){
                            breaker = 1;
                        }
                        if(breaker != 1) {
                            if(distance[i][j] < min){
                                min = distance[i][j];
                                temp = j;
                            }
                        }
                    }
                holdCityId[increaseCount] = cities[i].id;
                increaseCount++;
                }
            path_1 += round(sqrt(min));
        }
        fprintf(output,"%.0f\n",path_1);
        for(int mz = 0; mz < ceil(cityCount/2.0);mz++) {
            fprintf(output,"%d\n",holdCityId[mz]);
        }
        sizearray = cityCount;
        for(int fre = 0; fre < sizearray; fre++) {
            free(distance[fre]);
        }
        fprintf(output,"\n");
        free(distance);
        free(cities);
        fclose(file);
        fclose(output);
        return 0;
}
