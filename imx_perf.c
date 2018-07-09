#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#define PERF_PATH "/sys/bus/event_source/devices/"

int perf_fd;
sig_atomic_t volatile done = 0;

static void sig_handler(int signo)
{
	long long count;

	if (signo == SIGINT) {
		printf("received SIGINT\n");

		ioctl(perf_fd, PERF_EVENT_IOC_DISABLE, 0);
		read(perf_fd, &count, sizeof(long long));

		printf("Used %lld cycles\n", count);

		close(perf_fd);

		done = 1;
	}
}

static long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
		int cpu, int group_fd, unsigned long flags)
{
	int ret;

	ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
			group_fd, flags);
	if (ret < 0)
		fprintf(stderr, "%d: %s\n", errno, strerror(errno));
	return ret;
}

int
main(int argc, char **argv)
{
	struct perf_event_attr pe;
	char path[100] = "", buffer[10] = "";
	int fd, type, config;

	if (argc < 3) {
		printf("use imx_perf type config\n");
		exit(EXIT_FAILURE);
	}

	if (signal(SIGINT, sig_handler) == SIG_ERR) {
		printf("can't catch SIGINT\n");
		exit(EXIT_FAILURE);
	}

	/* get the PERF TYPE, config */
	strcpy(path, PERF_PATH);
	strcat(path, argv[1]);
	strcat(path, "/type");
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		printf("open %s failed: %s\n", path, strerror(errno));
		close(fd);
		exit(EXIT_FAILURE);
	} else {
		read(fd, buffer, sizeof(buffer));
		type = atoi(buffer);
	}
	config = atoi(argv[2]);

	memset(&pe, 0, sizeof(struct perf_event_attr));
	pe.type = type;
	pe.size = sizeof(struct perf_event_attr);
	pe.config = config;
	pe.disabled = 1;
	/* not allowed for ddr-perf */
	/*
	pe.exclude_kernel = 1;
	pe.exclude_hv = 1;
	*/

	perf_fd = perf_event_open(&pe, -1, 0, -1, 0);
	if (perf_fd == -1) {
		fprintf(stderr, "Error opening leader %llx\n", pe.config);
		exit(EXIT_FAILURE);
	}

	ioctl(perf_fd, PERF_EVENT_IOC_RESET, 0);
	ioctl(perf_fd, PERF_EVENT_IOC_ENABLE, 0);

	while (!done)
		sleep(1);

	close(fd);
	return 0;
}

