#include <stdlib.h>
#include <stdio.h>

#define MINSCORE 0
#define MAXSCORE 10
#define MINDEGDIF 1
#define MAXDEGDIF 5
#define NUMDIVESPERCOMPETITOR 8
#define NUMJUDGES 8
  
float promptDegDif() {
  printf("degree of difficulty: ");
  float degDif;
  scanf("%f", &degDif);

  if (degDif < MINDEGDIF || degDif > MAXDEGDIF){
    printf("Error: degree of difficulty must be between 1 and 5\n");
    return 1;
  }
  return degDif;
}

float promptJudges(int i){
  printf("enter score from judge %d: ", i+1);
  float judgeScore;
  scanf("%f", &judgeScore);

  if (judgeScore < MINSCORE || judgeScore > MAXSCORE){
    printf("Error: scores must be between 0 and 10\n");
    judgeScore = 0;
  }
  return judgeScore;
}

float calcSum(float judgeScores[]){
  float lowestScore = judgeScores[0];
  float secondLowest = judgeScores[1];
  int lowestPos = 0;
  int nextLowestPos = 1;
  int i;

  for (i = 0; i < NUMJUDGES; ++i){
    if (judgeScores[i] < lowestScore){
      secondLowest = lowestScore;
      nextLowestPos = lowestPos;
      lowestScore = judgeScores[i];
      lowestPos = i;
    }
    if (judgeScores[i] < secondLowest && i != lowestPos){
      secondLowest = judgeScores[i];
      nextLowestPos = i;
    }
  }

  for (i = lowestPos; i < NUMJUDGES - 1; ++i){
    judgeScores[i] = judgeScores[i+1];
  }

  if (lowestPos < nextLowestPos)
    nextLowestPos = nextLowestPos - 1;
  
  for (i = nextLowestPos; i < NUMJUDGES - 2; ++i){
    judgeScores[i] = judgeScores[i+1];
  }

  float highestScore = judgeScores[0];
  float secondHighest = judgeScores[1];
  int highestPos = 0;
  int nextHighestPos = 1;

  for (i = 0; i < NUMJUDGES - 2; ++i){
    if (judgeScores[i] > highestScore){
      secondHighest = highestScore;
      nextHighestPos = highestPos;
      highestScore = judgeScores[i];
      highestPos = i;
    }
    if (judgeScores[i] > secondHighest && i != highestPos){
      secondHighest = judgeScores[i];
      nextHighestPos = i;
    }
  }

  for (i = highestPos; i < NUMJUDGES - 3; ++i){
    judgeScores[i] = judgeScores[i+1];
  }

  if (highestPos < nextHighestPos)
    nextHighestPos = nextHighestPos - 1;
  
  for(i = nextHighestPos; i < NUMJUDGES - 4; ++i){
    judgeScores[i] = judgeScores[i+1];
  }

  float sum = 0;
  for (i = 0; i < NUMJUDGES - 4; ++i){
    sum = sum + judgeScores[i];
  }
  return sum;
}

float calcTotalScore(float degDif, float sum){
  float diveTotal = sum * degDif;
  return diveTotal;
}


float main() {
  float degDif = promptDegDif();

  float judgeScores[NUMJUDGES];
  int i;
  for (i = 0; i < NUMJUDGES; ++i){
    judgeScores[i] = promptJudges(i);
  }

  float middleFourSum = calcSum(judgeScores);
  float diveTotalScore = calcTotalScore(degDif, middleFourSum);
  printf("Score for this dive is %.2f\n", diveTotalScore);
}
