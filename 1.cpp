#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <time.h>
//#include <logN.h>

int __tab_num = 0;

#define debug_asm(reg) __asm__ __volatile__("mov " #reg ", " #reg "\n\t" ::: "memory")
#define debug_var(var) __asm__ __volatile__("mov %[" #var "], %[" #var "] \n\t" ::[var]"r"(var): "memory")

static const int n = 8;

void print(char snake[n][n]);

int main()
{
	// adb shell
	// SP1="> "
	// while ((1)); do clear; /data/local/tmp/res; done

	char snake[n][n];
	enum direrction {right = 3, down = 2, left = 1, up = 0};
	direrction side = up;//0 - right; 1 - down; 2 - left; 3 - up
	// int side = 0;

	int x2 = n-1;
	int x1 = 0;
	int y2 = n-1;
	int y1 = 0;

	int jr0 = y2;
	int jr1 = x2;
	int jr2 = y1;
	int jr3 = x1;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			snake[i][j] = '0';
		}
	}

	for (int i = 0; i < n*n; )
	{
		if (side == up)
		{
			if( jr0 > y1-1)
			{
				//snake[jr0][x2] = '^';
				__asm __volatile__(
					"strb %[symbol], [%[snake_jr0_x2]] \n\t"
					:
					:[snake_jr0_x2] "r" (&snake[jr0][x2]), [symbol] "r" ('^')
					:"memory", "cc");
					
				//i++;
				__asm __volatile__(
					"add	%[i], %[i], #1	\n\t"
					:[i] "+r" (i)
					:
					: "memory", "cc");
					
				//jr0--;
				__asm __volatile__(
					"sub	%[jr0], %[jr0], #1	\n\t"
					:[jr0] "+r" (jr0)
					:
					:"memory", "cc");
			}

			if (!(jr0 > y1 - 1))
			{
				//x2--;
				__asm __volatile__(
							"sub	%[x2], %[x2], #1	\n\t"
							:[x2] "+r" (x2)
							:
							:"memory", "cc");
							
				//side = left;
				__asm __volatile__(
							"mov	%[side], %[left]	\n\t"
							:[side] "+r" (side)
							:[left] "r" (left)
							:"memory", "cc");
							
				//jr1 = x2;
				__asm __volatile__(
							"mov	%[jr1], %[x2]	\n\t"
							:[jr1] "+r" (jr1)
							:[x2] "r" (x2)
							:"memory", "cc");
				
			}
		}
		else if(side == left)
		{
			if(jr1 > x1-1)
			{
				//snake[y1][jr1] = '<';
				__asm __volatile__(
							"strb	%[mark], [%[snake_y1_jr1]]	\n\t"
							://] "+r" (
							:[snake_y1_jr1] "r" (&snake[y1][jr1])
							,[mark]			"r" ('<')
							:"memory", "cc");
				//i++;
				__asm __volatile__(
							"add	%[i], %[i], #1	\n\t"
							:[i] "+r" (i)
							:
							:"memory", "cc");
				//jr1--;
				__asm __volatile__(
							"sub	%[jr1], %[jr1], #1	\n\t"
							:[jr1] "+r" (jr1)
							:
							:"memory", "cc");
			}

			if (!(jr1 > x1 - 1))
			{
				//y1++;
				__asm __volatile__(
							"add	%[y1], %[y1], #1	\n\t"
							:[y1] "+r" (y1)
							:
							:"memory", "cc");
				//side = down;
				__asm __volatile__(
							"mov	%[side], %[down]	\n\t"
							:[side] "+r" (side)
							:[down] "r" (down)
							:"memory", "cc");
				//jr2 = y1;
				__asm __volatile__(
							"mov	%[jr2], %[y1]	\n\t"
							:[jr2] "+r" (jr2)
							:[y1] "r" (y1)
							:"memory", "cc");
			}
		}
		else if (side == down)
		{
			if (jr2 < y2+1)
			{
				//snake[jr2][x1] = 'v';
				__asm __volatile__(
							"strb	%[mark], [%[snake_jr2_x1]]	\n\t"
							://] "+r" (
							:[snake_jr2_x1] "r" (&snake[jr2][x1] )
							,[mark]			"r" ('v')
							:"memory", "cc");
							
				//i++;
				__asm __volatile__(
							"add	%[i], %[i], #1	\n\t"
							:[i] "+r" (i)
							:
							:"memory", "cc");
				//jr2++;
				__asm __volatile__(
							"add	%[jr2], %[jr2], #1	\n\t"
							:[jr2] "+r" (jr2)
							:
							:"memory", "cc");
				
			}
			if (!(jr2 < y2 + 1))
			{
				//x1++;
				__asm __volatile__(
							"add	%[x1], %[x1], #1	\n\t"
							:[x1] "+r" (x1)
							:
							:"memory", "cc");
							
				//side = right;
				__asm __volatile__(
							"mov	%[side], %[right]	\n\t"
							:[side] "+r" (side)
							:[right] "r" (right)
							:"memory", "cc");
							
				//jr3 = x1;
				__asm __volatile__(
							"mov	%[jr3], %[x1]	\n\t"
							:[jr3] "+r" (jr3)
							:[x1] "r" (x1)
							:"memory", "cc");

			}
		}
		else if (side == right)
		{
			if(jr3 < x2 + 1)
			{
				//snake[y2][jr3] = '>';
				__asm __volatile__(
							"strb	%[mark], [%[snake_y2_jr3]]	\n\t"
							://] "+r" (
							:[snake_y2_jr3] "r" (&snake[y2][jr3] )
							,[mark]			"r" ('>')
							:"memory", "cc");
				//i++;
				__asm __volatile__(
							"add	%[i], %[i], #1	\n\t"
							:[i] "+r" (i)
							:
							:"memory", "cc");
							
				//jr3++;
				__asm __volatile__(
							"add	%[jr3], %[jr3], #1	\n\t"
							:[jr3] "+r" (jr3)
							:
							:"memory", "cc");
			}

			if(!(jr3 < x2+1))
			{
				//y2--;
				__asm __volatile__(
					"sub %[y2], %[y2], #1"
					:[y2] "+r" (y2)
					:
					:"memory", "cc");
					
				//side = up;
				__asm __volatile__(
					"mov %[side], %[up]"
					:[side] "+r" (side)
					:[up]"r"(up)
					:"memory", "cc");
				
				//jr0 = y2;
				__asm __volatile__(
					"mov %[jr0], %[y2]"
					:[jr0]"+r"(jr0)
					:[y2]"r"(y2)
					:"memory", "cc");
			}
		}
		print(snake);
	}

	return 0;
}

void print(char snake[n][n])
{
#if 1
	int sleepTime = 59999;
	usleep(sleepTime);
#else
	int sleepTime = 100;
	Sleep(sleepTime);
#endif

#ifdef WINDOWS
	std::system("cls");
#else
	printf("\n");
	int clear = 1;
	for (int i = 0; clear && i < n + 1; ++i) {
		fputs("\033[A\033[2K", stdout);
	}
#endif
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%c", snake[i][j]);
			if (j == n-1)
				printf("\n");
		}
	}
}











//sshpass -p 1 scp /home/robolin/tmp/repo3paty/tm_Cpp_project/main.cpp pi@192.168.1.106:/home/pi/1234;
//sshpass -p 1 ssh pi@192.168.1.106 "cd /home/pi/1234; arm-linux-gnueabihf-g++ main.cpp -O3 -std=c++11 -o res && ./res"

//rm -f res; arm-linux-gnueabihf-g++ main.cpp -static -o res  && adb push res /data/local/tmp
//rm -f res; arm-linux-gnueabihf-g++ main.cpp -static -o res  && adb push res /data/local/tmp && adb shell "/data/local/tmp/res 7 5"

//export PATH=$PATH:<PATH_TO_NDK>/toolchains/llvm/prebuilt/linux-x86_64/bin
//export PATH=$PATH:/home/user/Android/ndk/android-ndk-r21e-linux-x86_64/android-ndk-r21e/toolchains/llvm/prebuilt/linux-x86_64/bin

/*
 * generate a list file:
	arm-linux-gnueabihf-g++ -Wa,-adhln -g  main.cpp > res.s

 * generate a assembly file:
	arm-linux-gnueabihf-g++  -fPIE -pie -static -o res main.cpp  && arm-linux-gnueabihf-objdump -drwC res > res.txt && subl res.txt
*/

// run using cross clang++:
//rm -f res; armv7a-linux-androideabi30-clang++ main.cpp  -fPIE -pie -static -o res  && adb push res /data/local/tmp
// run using cross g++:
//rm -f res; arm-linux-gnueabihf-g++            main.cpp  -fPIE -pie -static -o res  && adb push res /data/local/tmp

// run on android terminal
// host_PC  > adb root; adb shell
// adb_shell> while ((1)); do clear; /data/local/tmp/res 7 5; done
