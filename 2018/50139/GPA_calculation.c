#include "GPA_calculation.h"
#include <stdio.h>
#include <stdlib.h>

double GPA_to_score(char GPA[3]){
    switch(GPA[0]){
        case 'A':
            if(GPA[1] == '+')
                return 4.3;
            else if(GPA[1] == '-')
                return 3.7;
            else
                return 4.0;
        case 'B':
            if(GPA[1] == '+')
                return 3.3;
            else if(GPA[1] == '-')
                return 2.7;
            else
                return 3.0;
        case 'C':
            if(GPA[1] == '+')
                return 2.3;
            else if(GPA[1] == '-')
                return 1.7;
            else
                return 2.0;
        default:
            return 0;
    }
}

int compare(const void *a, const void *b){
    struct Student *data1 = (struct Student *)a;
    struct Student *data2 = (struct Student *)b;

    if(data1->GPA > data2->GPA)
        return -1;
    else
        return 1;
}

void GPA_calculation(struct Student all_student[], int N){
    for(int student = 0; student < N; student++){
        double sum = 0;
        all_student[student].N_credit = 0;
        for(int class = 0; class < all_student[student].N_class; class++){
            sum += GPA_to_score(all_student[student].all_class[class].score) *\
                all_student[student].all_class[class].academic_credit;
            all_student[student].N_credit += all_student[student].all_class[class].academic_credit;
        }
        all_student[student].GPA = sum / all_student[student].N_credit;
    }

    qsort(all_student, N, sizeof(struct Student), compare);

    int count = N / 20 + (N % 20 != 0 ? 1 : 0);
    int student = 0;

    while(student < N && count > 0){
        if(all_student[student].GPA < 3.38)
            break;
        else if(all_student[student].N_credit < 15){
            student++;
            count--;
            continue;
        }

        printf("%d %s %f\n", student + 1, all_student[student].name, all_student[student].GPA);
        
        student++;
        count--;
    }
}