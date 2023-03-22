#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated

void merge(int pData[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;
	int x, y , z;

	int *L = (int*) malloc(n1*sizeof(int));
	int *R = (int*) malloc(n2*sizeof(int));
	extraMemoryAllocated = n1*sizeof(int) + n2*sizeof(int);

	for (x = 0; x < n1; x++)
		L[x] = pData[l + x];
	for (int y = 0; y < n2; y++)
		R[y] = pData[m + 1 + y];

	x = 0;
	y = 0;
	z = l;	
		
	while (x < n1 && y < n2)
	{
		if (L[x] <= R[y])
		{
			pData[z] = L[x];
			x++;
		}
		else
		{
			pData[z] = R[y];
			y++;
		}
		z++;
	}

	while (x < n1)
	{
		pData[z] = L[x];
		x++;
		z++;
	}

	while (y < n2)
	{
		pData[z] = R[y];
		y++;
		z++;
	}

	free(L);
	free(R);
}

void mergeSort(int pData[], int l, int r)
{
	if (l < r)
	{
		int m = (r + l) / 2;

		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);

		merge(pData, l, m, r);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int x, y;
	for(x = 1; x < n; x++)
	{
		int selection = pData[x];
		for(y = x - 1; y >= 0; y--)
		{
			if(pData[y] > selection)
				pData[y + 1] = pData[y];
			else
				break;
		}
		pData[y + 1] = selection;
	}	
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
//function that swaps the elements at the passed indexes
void swap(int* x, int* y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;

}

void bubbleSort(int* pData, int n)
{   
    //outer loop swaps largest element to the end
    for(int x = 0; x < n-1; x++)
    {   
        //inner loop swaps adjacent elements while ignoring the elements that have "bubbled up"
        for(int y = 0; y < n - x - 1; y++)
        {
            //enter if-statement to determine if you swap
            if(pData[y] > pData[y+1])
            {
                //call swap function
                swap(&pData[y], &pData[y+1]);
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{	
	for(int x = 0; x < n - 1; x++)
	{
		int min = x;
		for(int y = x + 1; y < n; y++)
		{
			if(pData[y] < pData[min])
				min = y;
		}
		swap(&pData[x], &pData[min]);	
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		
		for(int x = 0; x < dataSz; x++)
		{
			fscanf(inFile, "%d", *ppData + x);
		}
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
}