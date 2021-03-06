#pragma once
#include "common.h"

static const int MAX_CWD_LENGTH = 1024;
static const int MAX_USERNAME_LENGTH = 1024;
static const int MAX_HOSTNAME_LENGTH = 1024;
static const int MAX_HOMEDIR_LENGTH = 1024;
static const int MAX_PNAME_LENGTH = 4096;

struct Command;

typedef struct Process {
    pid_t pid;
    struct Process *next;
    char pname[MAX_PNAME_LENGTH];
    boolean done;

    //id given to the process inside the shell
    int jobid;
} Process;

typedef struct  {
    char cwd[MAX_CWD_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char hostname[MAX_HOSTNAME_LENGTH];
    char homedir[MAX_HOMEDIR_LENGTH];
    boolean should_quit;
    boolean debug_mode;
    struct Process *background_jobs;
    struct Process *foreground_jobs;
    struct Process *stopped_jobs;

    int next_jobid;
} Context;

Context *context_new();
void context_update(Context *context);
boolean context_should_quit(const Context *ctx);
void context_add_background_job(Context *context, Process *p);
void context_add_foreground_job(Context *context, Process *p);
void context_add_stopped_job(Context *context, Process *p);

give char *context_tildefy_directory(const Context *ctx, const char *dirpath);

/* *** Process *** */
give Process *process_new(pid_t pid, int jobid, const struct Command *command);
void process_delete(take Process *p);
