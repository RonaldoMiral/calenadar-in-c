#include <stdio.h>
#include <time.h>

#define TRUE  1
#define FALSE 0
#define TOTAL_MONTHS 12

typedef enum MONTHS {
  JAN = 0, FEB = 1, MAR = 2, APR = 3,
  MAY = 4, JUN = 5, JUL = 6, AUG = 7,
  SEP = 8, OCT = 9, NOV = 10, DEZ = 11
} MONTH;

int isBissextile(int year);
int getMonthLength(int month, int year);
void printCalendar(int monthLength, int month_day, int week_day);
int findWeekDayOfFirstMonthDay(int monthLength, int month_day, int week_day);


int main()
{
  time_t rawtime;
  struct tm *pTimeInfo;
  time(&rawtime);
  pTimeInfo = localtime(&rawtime);
  
  int year = pTimeInfo->tm_year + 1900;
  int month = pTimeInfo->tm_mon;
  int week_day = pTimeInfo->tm_wday;
  int month_day = pTimeInfo->tm_mday;
  int monthLength = getMonthLength(month, year);
  
  printCalendar(29, 27, 2);


  return 0;
}

void printCalendar(int monthLength, int month_day, int week_day) {
  // HEARDER
  /*
  printf("___________________________________________\n");
  printf("|  S  |  M  |  T  |  W  |  T  |  F  |  S  |\n");
  printf("¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n");
  */
  int wd;
  int wd_of_first_month_day = 
    findWeekDayOfFirstMonthDay(monthLength, month_day, week_day);
  
  for(int wd_counter = 0; wd_counter < 7; wd_counter++) {
    if(wd_counter < wd_of_first_month_day) {
      printf("%2c   ", 'x');
      wd = wd_counter + 1;
    } else if(wd_counter == wd_of_first_month_day) {
      for(int i = 1; i <= monthLength; i++) {
        printf("%2d   ", i);
        
        if(wd == 6) {
          printf("\n");
          wd = 0;
        } else wd++;
      }
      
      break;
    }
  }  
  printf("\n");
}

int isBissextile(int year) {
  if(
    year % 400 == 0 ||
    (year % 4 == 0 && year % 100 != 0)
  ) return TRUE;
  
  return FALSE;
}

int getMonthLength(int month, int year) {
  if(
    (month < AUG && month % 2 == 0) ||
    (month >= AUG && month % 2 != 0)
  ) {
    return 31;
  }
  else {
    if(month == FEB) {
      if(isBissextile(year)) return 29;
      else return 28;
    } else return 30;
  }
}

int findWeekDayOfFirstMonthDay(int monthLength, int month_day, int week_day)
{
  while(month_day > 1) {
    week_day--;
    if(week_day == -1) week_day = 6;
    
    month_day--;
  }

  return week_day;
}