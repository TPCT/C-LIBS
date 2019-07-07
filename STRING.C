#include "Strings.h"


char** Split (const char *String, const char *Splitter, unsigned long long Count) {
    unsigned long long Max_Word_Size     = Max_WordSize,
                       Max_Splitted_Size = Max_SplittedSize,
                       Splitter_Length   = 0,
                       Splitted_Word_Index   = 0,
                       Splitted_Array_Index  = 0,
                       Match_Index = 0;

    char *Splitted_Word,
         *Temp_Match_Word,
         **Splitted;

    while(*(Splitter + Splitter_Length)) Splitter_Length++;                                                     //Getting Splitter Length

    Splitted_Word    = (char*)  calloc(Max_Word_Size, sizeof(char));                                            //Collected Word To Be Sent
    Splitted         = (char**) calloc(Max_Splitted_Size, sizeof(char));                                        //Splitted Words -> Will be returned.
    Temp_Match_Word  = (char*)  calloc(Splitter_Length, sizeof(char));                                          //Matching with Splitter.

    void Save_Data(){
        for(int i = 0; i < Splitter_Length; *(Temp_Match_Word + i++) = '\0');                                   //Clear Temp_Match_Word
        if (Splitted_Array_Index == Max_Splitted_Size - 2){
            Max_Splitted_Size += Max_SplittedSize;
            char** Temp_Array = (char**) calloc(Max_Splitted_Size, sizeof(char*));
            for(int i = 0; i < Splitted_Array_Index; *(Temp_Array + i) = *(Splitted + i), i++);                 //Copy The Content of Splitted To Temp Array To Increase It's Size
            free(Splitted);
            Splitted = Temp_Array;
        }
        if(*Splitted_Word)
            Splitted[Splitted_Array_Index++] = Splitted_Word;
        Max_Word_Size = Max_WordSize;
        Splitted_Word = (char*) calloc(Max_Word_Size, sizeof(char));
        Splitted_Word_Index = 0;
        Match_Index = 0;
    }

    while(*String && Splitter_Length < Count){
        if (Splitted_Word_Index == Max_Word_Size - 1){
            Max_Word_Size += Max_WordSize;
            char* Temp_Splitted_Word = (char*) calloc(Max_Word_Size + 1, sizeof(char*));
            for(int i = 0; i < Splitted_Word_Index; *(Temp_Splitted_Word + i) = *(Splitted_Word + i), i++);
            free(Splitted_Word);
            Splitted_Word = Temp_Splitted_Word;
        }
        if(Match_Index < Splitter_Length && *String == *(Splitter + Match_Index)){
            *(Temp_Match_Word + Match_Index++) = *String;                                                       //Inline Increment to Skip \0
            if (Match_Index == Splitter_Length){
                Save_Data();
            }
        }
        else{
            if (Match_Index){
                char* Temp_Splitted_word = (char*) calloc(Splitted_Word_Index + Match_Index + 2, sizeof(char));
                for(int i = 0; i < Splitted_Word_Index; *(Temp_Splitted_word + i) = *(Splitted_Word + i), i++);
                for(int i = 0; i < Match_Index; *(Temp_Splitted_word + i) = *(Temp_Match_Word + i), i++, Splitted_Word_Index++);
                free(Splitted_Word);
                Splitted_Word = Temp_Splitted_word;
                Match_Index = 0;
            }
            Splitted_Word[Splitted_Word_Index++] = *String;
        }
        String++;
        if (*Splitted_Word && !*String){Save_Data();}
    }
    free(Temp_Match_Word);
    return Splitted;
}
