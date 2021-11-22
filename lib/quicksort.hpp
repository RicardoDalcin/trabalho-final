#include <stdio.h>
#include "../src/player.hpp"
#include "../src/users.hpp"

#ifndef quicksort_h
#define quicksort_h

// Quicksort to sort Players
void swapPlayers(Player *a, Player *b)
{
    Player t = *a;
    *a = *b;
    *b = t;
}

float partitionPlayers(Player arr[], int low, int high)
{
    Player pivotPlayer = arr[high];
    float pivot = pivotPlayer.globalRating(); // pivot
    int i = (low - 1);                        // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        Player player = arr[j];
        if (player.globalRating() <= pivot)
        {
            i++;
            swapPlayers(&arr[i], &arr[j]);
        }
    }
    swapPlayers(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortPlayers(Player arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partitionPlayers(arr, low, high);
        quickSortPlayers(arr, low, pi - 1);
        quickSortPlayers(arr, pi + 1, high);
    }
}

// Quicksort to sort User Ratings
void swapRatings(Rating *a, Rating *b)
{
    Rating t = *a;
    *a = *b;
    *b = t;
}

float partitionRatings(Rating arr[], int low, int high)
{
    Rating pivotRating = arr[high];
    float pivot = pivotRating.rate(); // pivot
    int i = (low - 1);                // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        Rating Rating = arr[j];
        if (Rating.rate() <= pivot)
        {
            i++;
            swapRatings(&arr[i], &arr[j]);
        }
    }
    swapRatings(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortRatings(Rating arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partitionRatings(arr, low, high);
        quickSortRatings(arr, low, pi - 1);
        quickSortRatings(arr, pi + 1, high);
    }
}

#endif