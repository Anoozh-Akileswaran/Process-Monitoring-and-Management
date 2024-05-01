#ifndef PLOT_TOOL_H
#define PLOT_TOOL_H


long total_cpu;
long total_ram;
double total_Mem;

//Gets the total cpu
void* total_cpu();

//Gets the total RAM
void* total_RAM();

//Gets the total memmory
void* total_Mem();

void getTotal();


unsigned long long getusedMemory();

long readTotalRAM();

long readFreeRAM();

double getTotalCpuUsage();

unsigned long long getusedMemory();  







#endif
