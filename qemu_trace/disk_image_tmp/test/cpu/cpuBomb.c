/*
 * ** PI.C - Computes Pi to an arbitrary number of digits
 * **
 * ** Uses far arrays so may be compiled in any memory model
 * */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

long secstart, usecstart;
long kf, ks;
long *mf, *ms;
long cnt, n, temp, nd;
long i;
long col, col1;
long loc, stor[40];

void shift(long *l1, long *l2, long lp, long lmod)
{
	long k;

	k = ((*l2) > 0 ? (*l2) / lmod: -(-(*l2) / lmod) - 1);
	*l2 -= k * lmod;
	*l1 += k * lp;
}

void yprint(long m)
{
	if (cnt<n)
	{
		if (++col == 11)
		{
			col = 1;
			if (++col1 == 6)
			{
				col1 = 0;
				printf("\n");
				printf("%4ld",m%10);
			}
			else printf("%3ld",m%10);
		}
		else printf("%ld",m);
		cnt++;
	}
}

void xprint(long m)
{
	long ii, wk, wk1;

	if (m < 8)
	{
		for (ii = 1; ii <= loc; )
			yprint(stor[(int)(ii++)]);
		loc = 0;
	}
	else
	{
		if (m > 9)
		{
			wk = m / 10;
			m %= 10;
			for (wk1 = loc; wk1 >= 1; wk1--)
			{
				wk += stor[(int)wk1];
				stor[(int)wk1] = wk % 10;
				wk /= 10;
			}
		}
	}
	stor[(int)(++loc)] = m;
}

void memerr(int errno)
{
	printf("\a\nOut of memory error #%d\n", errno);
	if (2 == errno)
		free(mf);
	_exit(2);
}

int main(int argc, char *argv[])
{
	int i=0;
	char *endp;

	stor[i++] = 0;
	if (argc < 2)
	{
		puts("\aUsage: PI <number_of_digits>");
		return(1);
	}
	n = strtol(argv[1], &endp, 10);
	mf = malloc((size_t)(n + 3L)*(size_t)sizeof(long));
	if (!mf)
		memerr(1);
	ms = malloc((size_t)(n + 3L)*(size_t)sizeof(long));
	if (!ms)
		memerr(2);
	printf("\nApproximation of PI to %ld digits\n", (long)n);

	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	secstart=tv.tv_sec;
	usecstart=tv.tv_usec;
	cnt = 0;
	kf = 25;
	ks = 57121L;
	mf[1] = 1L;
	for (i = 2; i <= (int)n; i += 2)
	{
		mf[i] = -16L;
		mf[i+1] = 16L;
	}
	for (i = 1; i <= (int)n; i += 2)
	{
		ms[i] = -4L;
		ms[i+1] = 4L;
	}
	printf("\n 3.");
	while (cnt < n)
	{
		for (i = 0; ++i <= (int)n - (int)cnt; )
		{
			mf[i] *= 10L;
			ms[i] *= 10L;
		}
		for (i =(int)(n - cnt + 1); --i >= 2; )
		{
			temp = 2 * i - 1;
			shift(&mf[i - 1], &mf[i], temp - 2, temp * kf);
			shift(&ms[i - 1], &ms[i], temp - 2, temp * ks);
		}
		nd = 0;
		shift((long *)&nd, &mf[1], 1L, 5L);
		shift((long *)&nd, &ms[1], 1L, 239L);
		xprint(nd);
	}
	printf("\n\nCalculations Completed!\n");
	gettimeofday(&tv, &tz);
	printf("Time: %ld seconds\n",tv.tv_sec-secstart);
	free(ms);
	free(mf);
	return(0);
}
