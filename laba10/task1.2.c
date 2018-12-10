#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

/* обработчик для SIGINT */
static void signal_handler(int signo) {
if (signo == SIGINT)
printf("Захвачен сигнал SIGINT!\n");
else if (signo == SIGTERM)
printf("Захвачен сигнал SIGTERM!\n");
else if (signo == SIGUSR1)
printf("Захвачен сигнал SIGUSR1\n");
else {
/* это никогда не должно случаться */
fprintf(stderr, "Неожиданный сигнал!\n");
exit(EXIT_FAILURE);
}
exit(EXIT_SUCCESS);
}
int main(void){
			printf("%d\n", getpid());

	sigset_t mask;
	sigemptyset(&mask);
	sigaddset(&mask, SIGPROF);
	sigaddset(&mask, SIGHUP);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	struct sigaction new_sa;
	new_sa.sa_handler = signal_handler;//SIG_DFL,SIG_IGN
	new_sa.sa_mask = mask;
	new_sa.sa_flags = 0;

	if(sigaction(SIGINT, &new_sa, NULL)){
		fprintf(stderr, "\ncan't catch SIGINT\n");
		exit(EXIT_FAILURE);
	}

	if(sigaction(SIGTERM, &new_sa, NULL)){
		fprintf(stderr, "\ncan't catch SIGTERM\n");
		exit(EXIT_FAILURE);
	}

	for (;;)
		pause();

	return 0;
}