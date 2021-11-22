#include<stdio.h>
#include "../src/player.hpp"

// Quicksort to sort Players
void swapPlayers(Player* a, Player* b)
{
    Player t = *a;
    *a = *b;
    *b = t;
}
 
float partitionPlayers (Player* arr[], int low, int high)
{
    Player* pivotPlayer = arr[high];
    float pivot = pivotPlayer->globalRating();    // pivot
    int i = (low - 1);  // Index of smaller element
 
    for (int j = low; j <= high- 1; j++)
    {
        Player* player = arr[j];
        if (player->globalRating() <= pivot)
        {
            i++;
            swapPlayers(arr[i], arr[j]);
        }
    }
    swapPlayers(arr[i + 1], arr[high]);
    return (i + 1);
}
 
void quickSortPlayers(Player* arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partitionPlayers(arr, low, high);
        quickSortPlayers(arr, low, pi - 1);
        quickSortPlayers(arr, pi + 1, high);
    }
}