#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/system_info.h"

const char *g_distro_color = "";

#define COLOR g_distro_color
#define RESET "\033[0m"

void packetManagerDefinder();

void get_names() {
    char userBuffer[64];
    FILE *userName = popen("whoami", "r");
    if (userName == NULL) return;
    if (fgets(userBuffer, sizeof(userBuffer), userName) != NULL)
        userBuffer[strcspn(userBuffer, "\n")] = 0;
    pclose(userName);

    char hostNameBuffer[64];
    FILE *hostName = popen("hostname", "r");
    if (hostName == NULL) return;
    if (fgets(hostNameBuffer, sizeof(hostNameBuffer), hostName) != NULL)
        hostNameBuffer[strcspn(hostNameBuffer, "\n")] = 0;
    pclose(hostName);

    printf("%s%s@%s" RESET "\n", COLOR, userBuffer, hostNameBuffer);
}

void get_distro() {
    char bufferDistro[64];
    FILE *distro = popen("lsb_release -si", "r");
    if (distro == NULL) return;
    if (fgets(bufferDistro, sizeof(bufferDistro), distro) != NULL)
        bufferDistro[strcspn(bufferDistro, "\n")] = 0;
    pclose(distro);
    printf("%sDistro: " RESET "%s\n", COLOR, bufferDistro);
}

void get_kernel() {
    char kernelBuffer[64];
    FILE *kernel = popen("uname -r", "r");
    if (kernel == NULL) return;
    if (fgets(kernelBuffer, sizeof(kernelBuffer), kernel) != NULL)
        kernelBuffer[strcspn(kernelBuffer, "\n")] = 0;
    pclose(kernel);
    printf("%sKernel: " RESET "%s\n", COLOR, kernelBuffer);
}

void get_desktop() {
    char desktopBuffer[64];
    FILE *desktop = popen("echo $XDG_CURRENT_DESKTOP", "r");
    if (desktop == NULL) return;
    if (fgets(desktopBuffer, sizeof(desktopBuffer), desktop) != NULL)
        desktopBuffer[strcspn(desktopBuffer, "\n")] = 0;
    pclose(desktop);
    printf("%sDesktop: " RESET "%s\n", COLOR, desktopBuffer);
}

void get_session() {
    char sessionBuffer[64];
    FILE *session = popen("echo $XDG_SESSION_TYPE", "r");
    if (session == NULL) return;
    if (fgets(sessionBuffer, sizeof(sessionBuffer), session) != NULL)
        sessionBuffer[strcspn(sessionBuffer, "\n")] = 0;
    pclose(session);
    printf("%sSession: " RESET "%s\n", COLOR, sessionBuffer);
}

void get_init_system() {
    char initBuffer[64];
    FILE *init = popen("basename $(readlink -f /sbin/init)", "r");
    if (init == NULL) return;
    if (fgets(initBuffer, sizeof(initBuffer), init) != NULL)
        initBuffer[strcspn(initBuffer, "\n")] = 0;
    pclose(init);
    printf("%sInit system: " RESET "%s\n", COLOR, initBuffer);
}

void get_system_age() {
    char oldSystemBuffer[64];
    FILE *oldSystem = popen("bash -c 'birth=$(stat -c %W /); now=$(date +%s); echo $(( (now - birth) / 86400 )) days'", "r");
    if (oldSystem == NULL) return;
    if (fgets(oldSystemBuffer, sizeof(oldSystemBuffer), oldSystem) != NULL)
        oldSystemBuffer[strcspn(oldSystemBuffer, "\n")] = 0;
    pclose(oldSystem);
    printf("%sSystem age: " RESET "%s\n", COLOR, oldSystemBuffer);
}

void get_uptime() {
    char upTimBuffer[64];
    FILE *upTime = popen("uptime -p | sed 's/up //'", "r");
    if (upTime == NULL) return;
    if (fgets(upTimBuffer, sizeof(upTimBuffer), upTime) != NULL)
        upTimBuffer[strcspn(upTimBuffer, "\n")] = 0;
    pclose(upTime);
    printf("%sUptime: " RESET "%s\n", COLOR, upTimBuffer);
}

void get_ram() {
    char ramBuffer[64];
    FILE *ram = popen("free -m | awk 'NR==2{printf \"%.2fgb / %.2fgb \\n\", $3/1024, $2/1024}'", "r");
    if (ram == NULL) return;
    if (fgets(ramBuffer, sizeof(ramBuffer), ram) != NULL)
        ramBuffer[strcspn(ramBuffer, "\n")] = 0;
    pclose(ram);
    printf("%sRAM: " RESET "%s\n", COLOR, ramBuffer);
}

void get_gpu() {
    char gpuBuffer[64];
    FILE *gpu = popen("glxinfo | grep \"OpenGL renderer string\" | sed 's/.*: //; s/[/(].*//' | xargs", "r");
    if (gpu == NULL) return;
    if (fgets(gpuBuffer, sizeof(gpuBuffer), gpu) != NULL)
        gpuBuffer[strcspn(gpuBuffer, "\n")] = 0;
    pclose(gpu);
    printf("%sGPU: " RESET "%s\n", COLOR, gpuBuffer);
}

void get_cpu() {
    char cpuBuffer[64];
    FILE *cpu = popen("cat /proc/cpuinfo | grep 'model name' | uniq | cut -d: -f2 | xargs", "r");
    if (cpu == NULL) return;
    if (fgets(cpuBuffer, sizeof(cpuBuffer), cpu) != NULL)
        cpuBuffer[strcspn(cpuBuffer, "\n")] = 0;
    pclose(cpu);
    printf("%sCPU: " RESET "%s\n", COLOR, cpuBuffer);
}

void get_space() {
    char spaceBuffer[64];
    FILE *space = popen("df -k / | awk 'NR==2{printf \"%.2fgb / %.2fgb \\n\", $3/1048576, $2/1048576}'", "r");
    if (space == NULL) return;
    if (fgets(spaceBuffer, sizeof(spaceBuffer), space) != NULL)
        spaceBuffer[strcspn(spaceBuffer, "\n")] = 0;
    pclose(space);
    printf("%sDisk: " RESET "%s\n", COLOR, spaceBuffer);
}
