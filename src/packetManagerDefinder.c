#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/system_info.h"

#define COLOR g_distro_color
#define RESET "\033[0m"

int exists(const char *fname){
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void packetManagerDefinder()
{
    if (exists("/usr/bin/dpkg")) {
    char packetManagerBuffet[64];
    FILE *packetManager = popen("dpkg-query -f '${binary:Package}\n' -W | wc -l", "r");
    if (packetManager == NULL) {
        return;
    }
    if (fgets(packetManagerBuffet, sizeof(packetManagerBuffet), packetManager) != NULL) {
        packetManagerBuffet[strcspn(packetManagerBuffet, "\n")] = 0;
    }
    pclose(packetManager);
    printf("%spkgs: " RESET "%s (dpkg)\n", COLOR, packetManagerBuffet);
}

if (exists("/usr/bin/rpm")) {
    char packetManagerBuffet[64];
    FILE *packetManager = popen("rpm -qa | wc -l", "r");
    if (packetManager == NULL) {
        return;
    }
    if (fgets(packetManagerBuffet, sizeof(packetManagerBuffet), packetManager) != NULL) {
        packetManagerBuffet[strcspn(packetManagerBuffet, "\n")] = 0;
    }
    pclose(packetManager);
    printf("%spkgs: " RESET "%s (rpm)\n", COLOR, packetManagerBuffet);
}

if (exists("/usr/bin/pacman")) {
    char packetManagerBuffet[64];
    FILE *packetManager = popen("pacman -Q | wc -l", "r");
    if (packetManager == NULL) {
        return;
    }
    if (fgets(packetManagerBuffet, sizeof(packetManagerBuffet), packetManager) != NULL) {
        packetManagerBuffet[strcspn(packetManagerBuffet, "\n")] = 0;
    }
    pclose(packetManager);
    printf("%spkgs: " RESET "%s (pacman)\n", COLOR, packetManagerBuffet);
}

if (exists("/sbin/apk")) {
    char packetManagerBuffet[64];
    FILE *packetManager = popen("apk info | wc -l", "r");
    if (packetManager == NULL) {
        return;
    }
    if (fgets(packetManagerBuffet, sizeof(packetManagerBuffet), packetManager) != NULL) {
        packetManagerBuffet[strcspn(packetManagerBuffet, "\n")] = 0;
    }
    pclose(packetManager);
    printf("%spkgs: " RESET "%s (apk)\n", COLOR, packetManagerBuffet);
}

if (exists("/usr/bin/dnf")) {
    char packetManagerBuffet[64];
    FILE *packetManager = popen("dnf list installed | wc -l", "r");
    if (packetManager == NULL) {
        return;
    }
    if (fgets(packetManagerBuffet, sizeof(packetManagerBuffet), packetManager) != NULL) {
        packetManagerBuffet[strcspn(packetManagerBuffet, "\n")] = 0;
    }
    pclose(packetManager);
    printf("%spkgs: " RESET "%s (dnf)\n", COLOR, packetManagerBuffet);
}

if (exists("/usr/bin/emerge")) {
    char packetManagerBuffet[64];
    FILE *packetManager = popen("qlist -I | wc -l", "r");
    if (packetManager == NULL) {
        return;
    }
    if (fgets(packetManagerBuffet, sizeof(packetManagerBuffet), packetManager) != NULL) {
        packetManagerBuffet[strcspn(packetManagerBuffet, "\n")] = 0;
    }
    pclose(packetManager);
    printf("%spkgs: " RESET "%s (emerge)\n", COLOR, packetManagerBuffet);
}

if (exists("/usr/bin/zypper")) {
    char packetManagerBuffet[64];
    FILE *packetManager = popen("zypper se --installed-only | wc -l", "r");
    if (packetManager == NULL) {
        return;
    }
    if (fgets(packetManagerBuffet, sizeof(packetManagerBuffet), packetManager) != NULL) {
        packetManagerBuffet[strcspn(packetManagerBuffet, "\n")] = 0;
    }
    pclose(packetManager);
    printf("%spkgs: " RESET "%s (zypper)\n", COLOR, packetManagerBuffet);
}

if (exists("/usr/bin/xbps-query")) {
    char packetManagerBuffet[64];
    FILE *packetManager = popen("xbps-query -l | wc -l", "r");
    if (packetManager == NULL) {
        return;
    }
    if (fgets(packetManagerBuffet, sizeof(packetManagerBuffet), packetManager) != NULL) {
        packetManagerBuffet[strcspn(packetManagerBuffet, "\n")] = 0;
    }
    pclose(packetManager);
    printf("%spkgs: " RESET "%s (xbps-query)\n", COLOR, packetManagerBuffet);
}
}
