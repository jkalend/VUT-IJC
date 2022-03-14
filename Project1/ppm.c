//
// Created by kalen on 2022-03-14.
//

#include "ppm.h"

struct ppm* ppm_read(const char* filename) {
    FILE* fp = fopen(filename, "rb");

    if (fp == NULL) {
        warning_msg("%s nelze otevrit\n", filename);
        return NULL;
    }

    struct ppm* PPM = malloc(sizeof(struct ppm));
    if (PPM == NULL) {
        fclose(fp);
        error_exit("Alokace selhala\n");
    }

    char format[16];
    fgets(format, sizeof(format), fp);
    if (format[0] != 'P' && format[1] != '6') {
        fclose(fp);
        ppm_free(PPM);
        warning_msg("Soubor %s ma neplatny format\n", filename);
        return NULL;
    }


    int check = fscanf(fp, "%d %d", &PPM->xsize, &PPM->ysize);
    if (check != 2) {
        fclose(fp);
        ppm_free(PPM);
        warning_msg("Soubor %s ma neplatny format\n", filename);
        return NULL;
    }

    if (PPM->xsize * PPM->ysize * 3 > MAX_SIZE) {
        warning_msg("Rozliseni obrazku je prilis velke\n");
        fclose(fp);
        ppm_free(PPM);
    }

    int bitrate;
    check = fscanf(fp, "%d", &bitrate);
    if (check != 1 || bitrate != 255) {
        fclose(fp);
        ppm_free(PPM);
        warning_msg("Soubor %s ma neplatny format\n", filename);
        return NULL;
    }

    //while (fgetc(fp) != '\n') ;
    //memory allocation for pixel data
    PPM->data = malloc(3 * PPM->xsize * PPM->ysize);

    if (PPM->data == NULL) {
        ppm_free(PPM);
        fclose(fp);
        error_exit("Alokace selhala\n");
    }

    //read pixel data from file
    if (fread(PPM->data, sizeof(char), (3* PPM->xsize * PPM->ysize), fp) != (3* PPM->xsize * PPM->ysize)) {
        warning_msg("Chyba pri cteni souboru %s\n", filename);
        ppm_free(PPM);
        fclose(fp);
        return NULL;
    }

    fclose(fp);

    return PPM;

}

void ppm_free(struct ppm *p) {
    if (p->data != NULL)
        free(p->data);
    free(p);
}
/*
int main (int argc, char **argv) {
    if (argc != 2) {
        warning_msg("Neplatne argumenty\n");
        return 1;
    }
    struct ppm *ppm_ptr = ppm_read(argv[1]);
    if(ppm_ptr == NULL) {
        error_exit("fail\n");
    }
    ppm_free(ppm_ptr);
    //printf("%s\n", ppm_ptr->data);
}
*/