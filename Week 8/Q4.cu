#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cuda_runtime.h>

__global__ void countWord(char *s, char *w, int slen, int wlen, int *count)
{
    int i=blockIdx.x * blockDim.x + threadIdx.x;
    if(i<=slen - wlen)
    {
        if(i!=0 && s[i - 1]!=' ')
            return;
        for(int j=0; j<wlen; j++)
        {
            if(s[i + j]!=w[j])
                return;
        }
        if(i + wlen<slen && s[i + wlen]!=' ')
            return;
        atomicAdd(count, 1);
    }
}

int main()
{
    char sentence[1024], word[100];
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")]='\0';
    printf("Enter the word to count: ");
    scanf("%s", word);

    int slen=strlen(sentence);
    int wlen=strlen(word);
    int count=0;

    char *d_s, *d_w;
    int *d_count;
    cudaMalloc((void**)&d_s, slen + 1);
    cudaMalloc((void**)&d_w, wlen + 1);
    cudaMalloc((void**)&d_count, sizeof(int));

    cudaMemcpy(d_s, sentence, slen + 1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_w, word, wlen + 1, cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &count, sizeof(int), cudaMemcpyHostToDevice);

    int threads=256;
    int blocks=(slen + threads - 1) / threads;
    countWord<<<blocks, threads>>>(d_s, d_w, slen, wlen, d_count);

    cudaMemcpy(&count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("The word '%s' appears %d time(s)\n", word, count);

    cudaFree(d_s);
    cudaFree(d_w);
    cudaFree(d_count);

    printf("\nTanish Kuvar, 240962540\n");
    return 0;
}
