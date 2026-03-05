#include <stdio.h>
#include <string.h>

void draw_logo(char *buffer) {
    FILE *distro = popen("lsb_release -si | tr '[:upper:]' '[:lower:]'", "r");
    //lsb_release -si | tr '[:upper:]' '[:lower:]'
    //lsb_release -si = выводим названия дистра
    //'[:upper:]' '[:lower:]' = переводим upper в lower

    if (distro == NULL) {
        perror("Ошибка при выполнении popen");
        strncpy(buffer, "unknown", 64); //копируем до последнего символа
        return;
    }

    if (fgets(buffer,64, distro) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
    pclose(distro); //закрываем что бы больше ниче не поменять
}