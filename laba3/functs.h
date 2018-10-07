
#ifndef _FUNCTS_H_

#define _FUNCTS_H_ 

extern char *value;
extern char *assigned;

void help(char* );
void infovar(const char* );
int set_env_var(char* , char * );
void setvar(char* );
void infovar(const char*);
void set_a(char*);
void set_v(char*);
void assign_value();
int deletevar(const char * );
int clearenvr(void);
void usage(char *);


#endif
