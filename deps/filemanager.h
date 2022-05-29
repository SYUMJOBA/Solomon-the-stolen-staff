char GAME_FILENAME[32] = "";

void standardizeFileName(char * filename){ //bsaically makes sure the "save" extension is included in the file name
    int i = 0;
    while ((unsigned)i < strlen(filename) && filename[i] != '.')
    {
        i++;
    }
    if ((unsigned)i <= strlen(filename))
    {
        filename[i] = '.';
        filename[i+1] = 's';
        filename[i+2] = 'a';
        filename[i+3] = 'v';
        filename[i+4] = 'e';
        filename[i+5] = '\0';
    }
}

BOOL loadFileInGame(char * filename){
    standardizeFileName( filename );
    FILE * filepointer = fopen(filename, "rb");
    if (NULL != filepointer)
    {
        fclose(filepointer);
        return TRUE;
    }
    return FALSE;
}


BOOL writeFileFromGame( char * filename){
    standardizeFileName(filename);
    FILE * filepointer = fopen(filename, "wb");
    if (NULL != filepointer)
    {
        
        fclose(filepointer);
        return TRUE;
    }
    return FALSE;
}

void deleteFile(char* filename)
{
    standardizeFileName(filename);
    FILE* filepointer = fopen(filename, "wb");
    fclose(filepointer);
}