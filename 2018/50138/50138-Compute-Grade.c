#include "computeGrade.h"
#include <stdio.h>

void computeGrade(Classes classes[2]){
    for(int test = 0; test < 18; test++){
        double sum1 = 0;
        for(int i = 0; i < classes[0].numStudent; i++)
            sum1 += classes[0].student[i].score[test].rawScore;
        sum1 /= classes[0].numStudent;

        double sum2 = 0;
        for(int i = 0; i < classes[1].numStudent; i++)
            sum2 += classes[1].student[i].score[test].rawScore;
        sum2 /= classes[1].numStudent;

        double ratio = (sum1 > sum2 ? sum1 / sum2 : sum2 / sum1);

        for(int i = 0; i < classes[0].numStudent; i++){
            classes[0].student[i].score[test].scaledScore = classes[0].student[i].score[test].rawScore *\
                (sum1 > sum2 ? 1 : ratio);
            if(classes[0].student[i].score[test].scaledScore > 100)
                classes[0].student[i].score[test].scaledScore = 100;
        }
        for(int i = 0; i < classes[1].numStudent; i++){
            classes[1].student[i].score[test].scaledScore = classes[1].student[i].score[test].rawScore *\
                (sum2 > sum1 ? 1 : ratio);
            if(classes[1].student[i].score[test].scaledScore > 100)
                classes[1].student[i].score[test].scaledScore = 100;
        }
    }

    //get final
    for(int class = 0; class < 2; class++){
        for(int student = 0; student < classes[class].numStudent; student++){
            double sum = 0;
            for(int test = 0; test < 18; test++)
                sum += classes[class].student[student].score[test].scaledScore;
            classes[class].student[student].finalScore = (sum * 0.06 > 100 ? 100 : sum * 0.06);

            printf("%s %f\n", classes[class].student[student].id, classes[class].student[student].finalScore);
        }

    }

}
