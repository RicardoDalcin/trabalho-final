#include <bits/stdc++.h>

#ifndef sorting_h
#define sorting_h

using namespace std;

// Funcoes basicas para um quicksort de inteiros
// usado para a funcao de interseccao de vetores

void copyArray(int source[], int destination[], int size)
{
  int i;

  for (i = 0; i < size; i++)
  {
    destination[i] = source[i];
  }
}

int partition(int arr[], int low, int high)
{
  int key = arr[low];
  bool left = true;

  int index;

  int low_cp = low;
  int high_cp = high;

  while (low_cp < high_cp)
  {
    if (left)
    {
      if (key >= arr[high_cp])
      {
        arr[low_cp] = arr[high_cp];
        low_cp = low_cp + 1;
        left = false;
      }
      else
      {
        high_cp = high_cp - 1;
      }
    }
    else
    {
      if (key < arr[low_cp])
      {
        arr[high_cp] = arr[low_cp];
        high_cp = high_cp - 1;
        left = true;
      }
      else
      {
        low_cp = low_cp + 1;
      }
    }
  }

  index = low_cp;
  arr[index] = key;

  return index;
}

int medianPartition(int arr[], int low, int high)
{
  int half_index = floor((low + high) / 2);

  int median_index;

  if (arr[half_index] < arr[high])
  {
    swap(arr[half_index], arr[high]);
  }

  if (arr[low] < arr[high])
  {
    swap(arr[low], arr[high]);
  }

  if (arr[half_index] < arr[low])
  {
    swap(arr[half_index], arr[low]);
  }

  return partition(arr, low, high);
}

void innerBasicQuicksort(int arr[], int low, int high)
{
  if (low < high)
  {
    int pi = medianPartition(arr, low, high);

    innerBasicQuicksort(arr, low, pi - 1);
    innerBasicQuicksort(arr, pi + 1, high);
  }
}

void basicQuicksort(int arr[], int size)
{
  innerBasicQuicksort(arr, 0, size - 1);
}

#endif