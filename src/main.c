#include "../inc/system_info.h"
#include "../inc/distro_arts.h"

void draw_logo(char *buffer);
void packetManagerDefinder();

#define INFO_LINES 7

int main(void)
{
    char userDistro[64];
    draw_logo(userDistro);
    const DistroArt *art = distro_art_find(userDistro);

    void (*funcs[])() = {
        get_names,
        get_distro,
        get_kernel,
        get_desktop,
        get_init_system,
        packetManagerDefinder,
        get_uptime,

        //others info,
        get_ram,
        get_gpu,
        get_cpu,
        get_space,
        get_session
    };


    if (art) {
        g_distro_color = art->color;
        for (int i = 0; i < DISTRO_LINES; i++){
            printf("%s%-4s" R, art->color, art->lines[i]);
            funcs[i]();
        }

        //if you want more than 7 lines (others info)

        // int total = sizeof(funcs) / sizeof(funcs[0]);
        // if (total > DISTRO_LINES) {
        //     for (int i = DISTRO_LINES; i < total; i++) {
        //         printf("%-15s", ""); // change -15s if it doesn't match with your logo
        //         funcs[i]();
        //     }
        // }
    }
}