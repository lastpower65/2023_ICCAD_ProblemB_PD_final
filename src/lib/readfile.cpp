#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "readfile.h"
#include <vector>
#include <assert.h>
#include <iostream>
#define BUFFER_SIZE 25

void read_one_blank_line(FILE *input)
{
    assert(input);
    fgetc(input);
}

void readTechnologyInfo(FILE *input, int *NumTechnologies, vector<Tech_menu> &TechMenu)
{
    assert(input);

    // read number of technologies
    fscanf(input, "%*s %d", &(*NumTechnologies));

    for (int i = 0; i < *NumTechnologies; i++)
    {
        Tech_menu temp;
        int cell_and_macro_num;
        fscanf(input, "%*s %s %d", temp.tech, &cell_and_macro_num);

        vector<Libcell> temp_libcell;

        for (int j = 0; j < cell_and_macro_num; j++)
        {
            char isMacro[2];
            fscanf(input, "%*s %s", isMacro);
            // is cell
            Libcell tempcell;
            if (strcmp(isMacro, "N") == 0)
            {

                tempcell.isMacro = false;
                fscanf(input, " %s %d %d %d", tempcell.libCellName, &(tempcell.libCellSizeX), &(tempcell.libCellSizeY), &(tempcell.pinCount));

                // read pinarray pinarray_count time
                vector<Pin> temp_pinarray(tempcell.pinCount);
                for (int k = 0; k < tempcell.pinCount; k++)
                {

                    fscanf(input, "%*s %s %d %d", temp_pinarray[k].pinName, &(temp_pinarray[k].pinLocationX), &(temp_pinarray[k].pinLocationY));
                }
                tempcell.pinarray = temp_pinarray;
                temp_libcell.push_back(tempcell);
                // cell_num++;
            }
            else
            { // is Macro
                tempcell.isMacro = true;
                fscanf(input, " %s %d %d %d", tempcell.libCellName, &(tempcell.libCellSizeX), &(tempcell.libCellSizeY), &(tempcell.pinCount));
                // read pinarray pinarray_count time
                vector<Pin> temp_pinarray(tempcell.pinCount);
                for (int k = 0; k < tempcell.pinCount; k++)
                {

                    fscanf(input, "%*s %s %d %d", temp_pinarray[k].pinName, &(temp_pinarray[k].pinLocationX), &(temp_pinarray[k].pinLocationY));
                }
                tempcell.pinarray = temp_pinarray;
                temp_libcell.push_back(tempcell);
            }
        }
        temp.libcell_count = temp_libcell.size();
        temp.libcell = temp_libcell;
        TechMenu.emplace_back(temp);
    }

    read_one_blank_line(input);
}

void printTechnologyInfo(int NumTechnologies, vector<Tech_menu> TechMenu)
{
    cout << "T1 number:" << TechMenu[0].libcell_count << endl;
    cout << "T1 number:" << TechMenu[0].libcell_count << endl;
    printf("\nNumTechnologies <technologyCount>: %d\n\n", NumTechnologies);
    for (int i = 0; i < NumTechnologies; i++)
    {
        printf("Tech <techName> <libCellCount>: %s %d:\n", TechMenu[i].tech, TechMenu[i].libcell_count);
        for (int j = 0; j < TechMenu[i].libcell_count; j++)
        {
            printf("\tLibCell <isMacro>  <libCellName> <libCellSizeX> <libCellSizeY> <pinCount>: %d %s %d %d %d\n", TechMenu[i].libcell[j].isMacro, TechMenu[i].libcell[j].libCellName, TechMenu[i].libcell[j].libCellSizeX, TechMenu[i].libcell[j].libCellSizeY, TechMenu[i].libcell[j].pinCount);
            for (int k = 0; k < TechMenu[i].libcell[j].pinCount; k++)
            {
                printf("\t\tPin <pinName> <pinLocationX> <pinLocationY>: %s %d %d\n", TechMenu[i].libcell[j].pinarray[k].pinName, TechMenu[i].libcell[j].pinarray[k].pinLocationX, TechMenu[i].libcell[j].pinarray[k].pinLocationY);
            }
            printf("\n");
        }
        // for (int j = 0; j < TechMenu[i].macro_count; j++)
        // {
        //     printf("\tMacro <MacroName> <MacroSizeX> <MacroSizeY> <pinCount>: %s %d %d %d\n", TechMenu[i].macro[j].MacroName, TechMenu[i].macro[j].MacroSizeX, TechMenu[i].macro[j].MacroSizeY, TechMenu[i].macro[j].pinCount);
        //     for (int k = 0; k < TechMenu[i].macro[j].pinCount; k++)
        //     {
        //         printf("\t\tPin <pinName> <pinLocationX> <pinLocationY>: %s %d %d\n", TechMenu[i].macro[j].pinarray[k].pinName, TechMenu[i].macro[j].pinarray[k].pinLocationX, TechMenu[i].macro[j].pinarray[k].pinLocationY);
        //     }
        //     printf("\n");
        // }
        printf("\n\n");
    }
    printf("\n");
}

void readDieInfo(FILE *input, Die *top_die, Die *bottom_die)
{
    assert(input);

    // read DieSize of the top die and the bottom size
    fscanf(input, "%*s %d %d %d %d", &(top_die->lowerLeftX), &(top_die->lowerLeftY), &(top_die->upperRightX), &(top_die->upperRightY));
    bottom_die->lowerLeftX = top_die->lowerLeftX;
    bottom_die->lowerLeftY = top_die->lowerLeftY;
    bottom_die->upperRightX = top_die->upperRightX;
    bottom_die->upperRightY = top_die->upperRightY;
    read_one_blank_line(input);

    // read maximum Utilization of the top die and the bottom die
    fscanf(input, "%*s %d", &(top_die->MaxUtil));
    fscanf(input, "%*s %d", &(bottom_die->MaxUtil));
    read_one_blank_line(input);

    // read DieRows Information
    fscanf(input, "%*s %d %d %d %d %d", &(top_die->startX), &(top_die->startY), &(top_die->rowLength), &(top_die->rowHeight), &(top_die->repeatCount));
    fscanf(input, "%*s %d %d %d %d %d", &(bottom_die->startX), &(bottom_die->startY), &(bottom_die->rowLength), &(bottom_die->rowHeight), &(bottom_die->repeatCount));
    read_one_blank_line(input);

    // read DieTech
    fscanf(input, "%*s %s", top_die->tech);
    fscanf(input, "%*s %s", bottom_die->tech);
    read_one_blank_line(input);
}

// print the detail die information
void printDieInfo(Die top_die, Die bottom_die)
{
    printf("\nTop Die Information:\n");
    printf("DieSize <lowerLeftX> <lowerLeftY> <upperRightX> <upperRightY>: %d %d %d %d\n", top_die.lowerLeftX, top_die.lowerLeftY, top_die.upperRightX, top_die.upperRightY);
    printf("TopDieMaxUtil: %d\n", top_die.MaxUtil);
    printf("TopDieRows <startX> <startY> <rowLength> <rowHeight> <repeatCount>:");
    printf("%d %d %d %d %d\n", top_die.startX, top_die.startY, top_die.rowLength, top_die.rowHeight, top_die.repeatCount);
    printf("TopDieTech <TechName>: %s\n\n", top_die.tech);

    printf("\nBottom Die Information:\n");
    printf("DieSize <lowerLeftX> <lowerLeftY> <upperRightX> <upperRightY>: %d %d %d %d\n", bottom_die.lowerLeftX, bottom_die.lowerLeftY, bottom_die.upperRightX, bottom_die.upperRightY);
    printf("BottomDieMaxUtil: %d\n", bottom_die.MaxUtil);
    printf("BottomDieRows <startX> <startY> <rowLength> <rowHeight> <repeatCount>:");
    printf("%d %d %d %d %d\n", bottom_die.startX, bottom_die.startY, bottom_die.rowLength, bottom_die.rowHeight, bottom_die.repeatCount);
    printf("BottomDieTech <TechName>: %s\n\n", bottom_die.tech);
}

void readHybridTerminalInfo(FILE *input, Hybrid_terminal *terminal)
{
    assert(input);

    // read terminal size & spacing
    fscanf(input, "%*s %d %d", &(terminal->sizeX), &(terminal->sizeY));
    fscanf(input, "%*s %d", &(terminal->spacing));
    fscanf(input, "%*s %d", &(terminal->val));
    read_one_blank_line(input);
}

void printHybridTerminalInfo(Hybrid_terminal terminal)
{
    printf("\nHybrid Terminal Information:\n");
    printf("TerminalSize <sizeX> <sizeY>: %d %d\n", terminal.sizeX, terminal.sizeY);
    printf("TerminalSpacing <spacing>: %d\n", terminal.spacing);
    printf("TerminalSpacing <value>: %d\n\n", terminal.val);
}

void readInstanceInfo(FILE *input, int *NumInstances, vector<Instance> &InstanceArray)
{
    assert(input);

    fscanf(input, "%*s %d", &(*NumInstances));

    for (int i = 0; i < *NumInstances; i++)
    {
        Instance temp;
        fscanf(input, "%*s %s %s", temp.instName, temp.libCellName);
        InstanceArray.emplace_back(temp);
    }
    read_one_blank_line(input);
}

void printInstanceInfo(int NumInstances, vector<Instance> InstanceArray)
{
    printf("NumInstances <instanceCount>: %d\n", NumInstances);
    for (int i = 0; i < NumInstances; i++)
    {
        printf("\tInst <instName> <libCellName>: %s %s\n", InstanceArray[i].instName, InstanceArray[i].libCellName);
    }
    printf("\n");
}

void readNetInfo(FILE *input, int *NumNets, vector<RawNet> &rawnet)
{
    assert(input);

    fscanf(input, "%*s %d", &(*NumNets));
    for (int i = 0; i < *NumNets; i++)
    {
        RawNet temp;
        fscanf(input, "%*s %s %d", temp.netName, &temp.numPins);

        // allocate memory for the detail connection in the net
        vector<NetConnection> temp_connection(temp.numPins);

        for (int j = 0; j < temp.numPins; j++)
        {
            char buffer[BUFFER_SIZE];
            memset(buffer, '\0', BUFFER_SIZE);
            fscanf(input, "%*s %s", buffer);
            // divide the string by using delimiter "/"
            char *token = strtok(buffer, "/");
            strcpy(temp_connection[j].instName, token);
            token = strtok(NULL, " ");
            strcpy(temp_connection[j].libPinName, token);
        }
        temp.Connection = temp_connection;
        rawnet.emplace_back(temp);
    }
    fclose(input);
}

void printNetInfo(int NumNets, vector<RawNet> rawnet)
{
    printf("\nNumNets <netCount>: %d\n", NumNets);
    for (int i = 0; i < NumNets; i++)
    {
        printf("\tNet <netName> <numPins>: %s %d\n", rawnet[i].netName, rawnet[i].numPins);
        for (int j = 0; j < rawnet[i].numPins; j++)
        {
            printf("\t\tPin <instName>/<libPinName>: %s / %s\n", rawnet[i].Connection[j].instName, rawnet[i].Connection[j].libPinName);
        }
        printf("\n");
    }
    printf("\n");
}