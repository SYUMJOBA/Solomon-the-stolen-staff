
FILE * LOG_FILE = NULL;

void setupLog(){
    LOG_FILE = fopen("debug.txt", "w");
}

void addDebugLog(const char * logMessage){
    if (LOG_FILE != NULL)
    {
        fputs(logMessage, LOG_FILE);
    }
}

void addBinaryNumberToLog(unsigned int number){
    for (int i = 0; i < 32; i++)
    {
        if ((number << i ) >> 31)
        {
            addDebugLog("1");
        } else {
            addDebugLog("0");
        }
        
    }
    addDebugLog("\n");
}

void closeDebug(){
    fclose(LOG_FILE);
}