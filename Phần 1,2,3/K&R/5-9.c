/*
 * Exercise 5-9. Rewrite the routines day_of _year and month_day with
 * pointers instead of indexing.
 */

#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] = 
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
	int day, month, year, yearday;
	yearday = day_of_year(2019, 2, 30);
	if (yearday != -1)
		printf("Test 1: 30/2/2019 -> %d\n", yearday);
	else
		printf("Test 1: 30/2/2019 -> %s\n", "Invalid input");
	if(month_day(2020, 60, &month, &day) != -1)
		printf("Test 2: 60th/2020 -> %d/%d\n", day, month);
	else
		printf("Test 2: 60th/2020 -> %s\n", "Invalid input");
	if(month_day(2019, 60, &month, &day) != -1)
		printf("Test 3: 60th/2019 -> %d/%d\n", day, month);
	else
		printf("Test 3: 60th/2019 -> %s\n", "Invalid input");

	return 0;
}

int day_of_year(int year, int month, int day)
{
	if( year < 1752 )
		return -1; 

	int i, leap;
	leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

	if( !((month >= 1 && month <= 12) && (day >= 1 && day <= daytab[leap][month])) )
		return -1;

	for(i = 1; i < month; i++)
		day += *(*(daytab + leap) + i);
	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
	if( year < 1752 )
	{
		*pmonth = *pday = -1;
		return -1;
	}

	int i, leap;
	leap = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);

	if( !(yearday >= 1 && yearday <= (leap ? 366 : 365)))
	{
		*pmonth = *pday = -1;
		return -1;
	}

	for(i = 1; yearday > daytab[leap][i]; i++)
		yearday -= *(*(daytab + leap) + i);
	*pmonth = i;
	*pday = yearday;
	return 1;
}

//output
/*
quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ gcc 5-9.c -o 5-9
quanglvn@quanglvn:~/thuviec/Bai-tap-thuc-hanh/123$ ./5-9
Test 1: 30/2/2019 -> Invalid input
Test 2: 60th/2020 -> 29/2
Test 3: 60th/2019 -> 1/3
*/