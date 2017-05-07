#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[])
{
	unsigned char *p_map;
	int myfile;
	int i;

	//open proc file
	myfile = open("/proc/mydir/myinfo", O_RDWR);
	//map p_map to the proc file and grant read/write priv
	p_map = (unsigned char *)mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, myfile, 0);
	//design test case to read from and write to p_map
	for(i = 0; i < 12; i++)
	{
		printf("p_map contains: %d\n", p_map[i]);
	}
	//unmap p_map from the proc file
	munmap(p_map, PAGE_SIZE);	

	return 0;
}
