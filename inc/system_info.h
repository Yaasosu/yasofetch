#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

extern const char *g_distro_color;

void get_names();
void get_distro();
void get_kernel();
void get_desktop();
void get_session();
void get_init_system();
void get_system_age();
void get_uptime();
void get_ram();
void get_gpu();
void get_cpu();
void get_space();

#endif