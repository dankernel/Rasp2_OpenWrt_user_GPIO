#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* Time */
#include <sys/time.h>
#include <time.h>

#define GPIO_OUTPUT 0
#define GPIO_INPUT 1
#define GPIO_HIGH  1
#define GPIO_LOW  0

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64

int gpio_get_val(unsigned int gpio)
{
     int fd, len;
     char buf[MAX_BUF];
 
     len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
     fd = open(buf, O_RDONLY);
 
     if (fd < 0) {
         fprintf(stderr, "Can't get GPIO %d pin value: %s\n", gpio, strerror(errno));
         return fd;
     }
 
     read(fd, buf, 1);
     close(fd);
 
     if (*buf != '0')
	return 1;
     else
     	return 0;
}

int gpio_set_val(unsigned int gpio, unsigned int val)
{
     int fd, len;
     char buf[MAX_BUF];
 
     len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
     fd = open(buf, O_WRONLY);
 
     if (fd < 0) {
         fprintf(stderr, "Can't set GPIO %d pin value: %s\n", gpio, strerror(errno));
         return fd;
     }
 
     if (val == GPIO_HIGH)
         write(fd, "1", 2);
     else
         write(fd, "0", 2);
 
     close(fd);
 
     return 0;
}

int main(int argc, char argv[])
{
	struct timespec start_point, end_point;
	int i = 500;

	clock_gettime(CLOCK_MONOTONIC, &start_point);
	while (i--) {
//		gpio_set_val(4, gpio_get_val(17));
		if (gpio_get_val(17))
			printf("!! \n");
	}
	clock_gettime(CLOCK_MONOTONIC, &end_point);
	printf("Time : %lf sec \n", (double)end_point.tv_sec - start_point.tv_sec
		+ (double)(end_point.tv_nsec - start_point.tv_nsec) / 1000 / 1000 / 1000);

	printf(".. %f nano sec \n", (double)(end_point.tv_nsec - start_point.tv_nsec));
	return 0;
}
