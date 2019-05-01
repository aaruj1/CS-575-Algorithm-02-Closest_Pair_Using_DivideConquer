#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

struct position {
    float x;
    float y;
    float z;
    long long id;
};

void merge(struct position *array, long long lt, long long mid, long long rt) {
    long long i, j, k;
    long long lSize = (mid - lt + 1);
    long long rSize = (rt - (mid + 1) + 1);
    
    struct position *lArray = (struct position *) malloc(sizeof(struct position) * lSize);
    struct position *rArray = (struct position *) malloc(sizeof(struct position) * rSize);
    
    for (i = 0; i < lSize; i++) {
        lArray[i].x = array[lt + i].x;
        lArray[i].y = array[lt + i].y;
        lArray[i].z = array[lt + i].z;
        lArray[i].id = array[lt + i].id;
    }
    for (j = 0; j < rSize; j++) {
        rArray[j].x = array[mid + 1 + j].x;
        rArray[j].y = array[mid + 1 + j].y;
        rArray[j].z = array[mid + 1 + j].z;
        rArray[j].id = array[mid + 1 + j].id;
    }
    
    i = 0;
    j = 0;
    k = lt;
    while (i < lSize && j < rSize) {
        if (lArray[i].x <= rArray[j].x) {
            array[k].x = lArray[i].x;
            array[k].y = lArray[i].y;
            array[k].z = lArray[i].z;
            array[k].id = lArray[i].id;
            i++;
        } else {
            array[k].x = rArray[j].x;
            array[k].y = rArray[j].y;
            array[k].z = rArray[j].z;
            array[k].id = rArray[j].id;
            j++;
        }
        k++;
    }
    
    /* Copy the remaining elements of L[], if there
     are any */
    while (i < lSize) {
        array[k].x = lArray[i].x;
        array[k].y = lArray[i].y;
        array[k].z = lArray[i].z;
        array[k].id = lArray[i].id;
        i++;
        k++;
    }
    
    /* Copy the remaining elements of R[], if there
     are any */
    while (j < rSize) {
        array[k].x = rArray[j].x;
        array[k].y = rArray[j].y;
        array[k].z = rArray[j].z;
        array[k].id = rArray[j].id;
        j++;
        k++;
    }
    free(lArray);
    free(rArray);
}


void mergeSort(struct position *array, long long lt, long long rt) {
    long long mid;
    if (rt > lt) {
        mid = (rt + lt) / 2;
        mergeSort(array, lt, mid);
        mergeSort(array, mid + 1, rt);
        merge(array, lt, mid, rt);
    }
}

double brute_force(struct position *array, long long lt, long long rt, struct position *p1, struct position *p2) {
    long long i, j;
    double dist = 1000000;
    long long ii = 0, jj = 0;
    for (i = lt; i < rt; i++) {
        for (j = i + 1; j < rt; j++) {
            double distance = sqrt(pow(array[i].x - array[j].x, 2) + pow(array[i].y - array[j].y, 2) +
                                   pow(array[i].z - array[j].z, 2));
            if (dist >= distance) {
                dist = distance;
                ii = i;
                jj = j;
            }
        }
    }
    *p1 = array[ii];
    *p2 = array[jj];
    return dist;
}

double min(double val1, double val2) {
    if (val1 >= val2) {
        return val2;
    } else {
        return val1;
    }
}


double minDistPair(struct position *array, long long lt, long long rt, struct position *p10, struct position *p20) {
    
    double minDistLR, minDistBand;
    long long i, j;
    struct position band[rt - lt];
    struct position p1, p2, p3, p4, p5, p6;
    
    if (rt - lt <= 3) {
        double baseDist = brute_force(array, lt, rt, &p1, &p2);
        *p10 = p1;
        *p20 = p2;
        
        return baseDist;
    } else {
        
        long long mid = (lt + rt) / 2;
        double minDistLeft = minDistPair(array, lt, mid, &p1, &p2);
        double minDistRight = minDistPair(array, mid, rt, &p3, &p4);
        
        //double delta = min(minDistLeft, minDistRight);
        if (minDistLeft > minDistRight) {
            minDistLR = minDistRight;
            *p10 = p3;
            *p20 = p4;
        } else {
            minDistLR = minDistLeft;
            *p10 = p1;
            *p20 = p2;
        }
        
        j = 0;
        for (i = lt; i < rt; i++) {
            double distance = sqrt(pow(array[i].x - array[mid].x, 2));
            if (distance <= minDistLR) {
                band[j] = array[i];
                j++;
            }
        }
        
        long long numPointBand = j;
        
        if (numPointBand > 1) {
            minDistBand = brute_force(band, 0, numPointBand, &p5, &p6);
            
            if (minDistLR > minDistBand) {
                *p10 = p5;
                *p20 = p6;
                return minDistBand;
            } else {
                return minDistLR;
            }
        } else {
            return minDistLR;
        }
    }
}


double divide_and_conquer(struct position *array, long long lt, long long rt, struct position *p1, struct position *p2) {
    long long i, j;
    mergeSort(array, lt, rt - 1);
    return minDistPair(array, lt, rt, p1, p2);
}

int main(int argc, char *argv[]) {
    long long i;
    clock_t start, end;
    double cpu_time_used;
    struct position p1, p2, p3, p4;
    long long num_position;
    
    FILE *srcFP, *destFP;
    char str[100];
    
    if (argc != 3) {
        printf("Please provide the input and output file name.\n");
        exit(0);
    }
    
    if ((srcFP = fopen(argv[1], "r")) == NULL) {
        perror("Error while opening input file");
        exit(1);
    }
    
    fgets(str, 100, srcFP);
    sscanf(str, "%lld", &num_position);
    
    printf("Number of positions : %lld \n", num_position);
    
    struct position *pos = (struct position *) malloc(sizeof(struct position) * num_position);
    
    for (i = 0; i < num_position; i++) {
        fgets(str, 100, srcFP);
        sscanf(str, "%f %f %f", &pos[i].x, &pos[i].y, &pos[i].z);
    }
    for (i = 0; i < num_position; i++) {
        pos[i].id = i;
    }
    
    for (i = 0; i < num_position; i++) {
        printf("%lld %f %f %f \n", pos[i].id, pos[i].x, pos[i].y, pos[i].z);
    }
    
    if ((destFP = fopen(argv[2], "w")) == NULL) {
        perror("Error while opening output file");
        exit(1);
    }
    
    start = clock();
    
    double distance = divide_and_conquer(pos, 0, num_position, &p3, &p4);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    fprintf(destFP, "Divide and Conquer Algorithm: \n");
    fprintf(destFP, "%lld %lld %f \n", p3.id, p4.id, distance);
    fprintf(destFP, "Execution time: %f seconds\n", cpu_time_used);
    
    fprintf(destFP, "############################################# \n");
    
    start = clock();
    
    distance = brute_force(pos, 0, num_position, &p1, &p2);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by BF: %f\n", cpu_time_used);
    
    fprintf(destFP, "Brute Force Algorithm: \n");
    fprintf(destFP, "%lld %lld %f \n", p1.id, p2.id, distance);
    fprintf(destFP, "Execution time: %f seconds\n", cpu_time_used);
    
    fclose(srcFP);
    fclose(destFP);
    free(pos);
    
    return 0;
}

