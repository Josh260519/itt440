#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

int num_child;
int pipefd[10][2];

void interrupt_handler ();
void create_child_processes();
void parent_process();
void child_process(int child_id);

void create_child_processes() {
    for (int i = 0; i < num_child; i++) {
        if (pipe(pipefd[i]) == -1) {
            perror("pipe");
            exit(1);
        }

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(1);
        }

        if (pid == 0) {
            child_process(i);
            exit(0);
        }
    }
}

void parent_process() {
    printf("Enter message to send to children: ");
    char str [60];
    fgets(str, 60, stdin);

    // read the message again to skip the newline character
    fgets(str, 60, stdin);

    for (int i = 0; i < num_child; i++) {
        close(pipefd[i][0]);
        ssize_t message_write = write(pipefd[i][1], str, strlen(str));
        if (message_write  == -1) {
            perror("write");
            exit(1);
        }
    }

    for (int i = 0; i < num_child; i++) {
        wait(NULL);
    }
}

void child_process(int child_id) {
    char str [60];
    close(pipefd[child_id][1]); // close write end of pipe
    ssize_t message_read = read(pipefd[child_id][0], str, 60);
    if (message_read == -1) {
        perror("read");
        exit(1);
    }
    printf("Child process %d received message: %s\n", child_id + 1, str);
}

void interrupt_handler (int sig){
	printf("\nInterrupt is detected. Exiting program.\n");
	exit (0);
}

int main() {
    signal(SIGINT, interrupt_handler);
    printf("Enter the number of child processes to create: ");
    scanf("%d", &num_child);

    create_child_processes();
    parent_process();

    return 0;
}
